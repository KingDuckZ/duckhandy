/* Copyright 2016-2018 Michele Santullo
 * This file is part of "duckhandy".
 *
 * "duckhandy" is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * "duckhandy" is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with "duckhandy".  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef id4754A95F12BE4ADEA65642A056A51907
#define id4754A95F12BE4ADEA65642A056A51907

#include "implem/reversed_sized_array_bt.hpp"
#include "sprout/math/log10.hpp"
#include "sprout/math/abs.hpp"
#include "sprout/math/ceil.hpp"
#include <cstddef>
#include <array>
#include <limits>
#if !defined(INT_CONV_WITHOUT_HELPERS)
#	include <string_view>
#endif
#include <emmintrin.h>
#if defined(__SSE4_1__)
#       include <smmintrin.h>
#endif

namespace dhandy {
	namespace implem {
		namespace {
			[[gnu::always_inline]]
			inline __m128i muly(const __m128i &a, const __m128i &b) {
#if defined(__SSE4_1__)  // modern CPU - use SSE 4.1
				return _mm_mullo_epi32(a, b);
#else               // old CPU - use SSE 2
				__m128i tmp1 = _mm_mul_epu32(a,b); /* mul 2,0*/
				__m128i tmp2 = _mm_mul_epu32( _mm_srli_si128(a,4), _mm_srli_si128(b,4)); /* mul 3,1 */
				return _mm_unpacklo_epi32(_mm_shuffle_epi32(tmp1, _MM_SHUFFLE (0,0,2,0)), _mm_shuffle_epi32(tmp2, _MM_SHUFFLE (0,0,2,0))); /* shuffle results to [63..0] and pack */
#endif
			}
		} //unnamed namespace

		template <typename T, typename C, unsigned int Base, typename Tr>
		T to_integer_sse (const C* s, std::size_t l);

		template <typename I, std::size_t Base>
		constexpr std::size_t max_digit_count = static_cast<std::size_t>(
			sprout::ceil(
				sprout::log10(sprout::abs(static_cast<long double>(std::numeric_limits<I>::max()))) /
				sprout::log10(static_cast<long double>(Base))
			)
		);

		template <typename I, unsigned int Base>
		struct int_info {
			static_assert(Base > 1, "Invalid base");
			static const constexpr bool always_unsigned = (Base == 16 or Base == 2 or Base == 36);
			static const constexpr bool is_signed = std::numeric_limits<I>::is_signed and not always_unsigned;
			static const constexpr std::size_t max_len = max_digit_count<typename std::conditional<always_unsigned, std::make_unsigned_t<I>, I>::type, Base> + is_signed;
		};

		template <typename I, unsigned int Base, bool Signed=int_info<I, Base>::is_signed>
		struct IsNegative { static constexpr bool check (I) { return false; } };
		template <typename I, unsigned int Base>
		struct IsNegative<I, Base, true> { static constexpr bool check (I in) { return in < I(0); } };

		template <typename I, unsigned int Base>
		constexpr bool is_negative (I in) {
			return IsNegative<I, Base>::check(in);
		}

		template <
			typename I,
			std::size_t Base,
			bool IsSigned=std::numeric_limits<I>::is_signed,
			bool ForceUnsigned=int_info<I, Base>::always_unsigned
		> struct NumberAdaptation {
			static const constexpr bool BecomesUnsigned = IsSigned and ForceUnsigned;
			using UnsignedType = typename std::make_unsigned<I>::type;
			using CastedType = typename std::conditional<BecomesUnsigned, UnsignedType, I>::type;

			template <typename L>
			[[gnu::pure,gnu::always_inline]]
			static constexpr L abs(L in) { return (not BecomesUnsigned and std::numeric_limits<L>::is_signed and in < L(0) ? -in : in); }
			[[gnu::pure,gnu::always_inline]]
			static constexpr CastedType cast (I in) { return static_cast<CastedType>(in); }
		};

		template <typename I, unsigned int Base, typename Tr, typename=void>
		struct IntConversion {
			static constexpr ReversedSizedArray<std::decay_t<decltype(std::declval<Tr>().to_digit(1))>, implem::int_info<I, Base>::max_len + 1> to_ary (I in) {
				using RetType = ReversedSizedArray<std::decay_t<decltype(std::declval<Tr>().to_digit(1))>, implem::int_info<I, Base>::max_len + 1>;
				using Num = implem::NumberAdaptation<I, Base>;

				const bool was_negative = implem::is_negative<I, Base>(in);

				RetType arr;
				arr.push_front('\0');
				do {
					arr.push_front(Tr::to_digit(static_cast<int>(Num::abs(Num::cast(in)) % Base)));
					in = static_cast<I>(Num::cast(in) / static_cast<I>(Base));
				} while (in);
				if (was_negative)
					arr.push_front(Tr::Minus);
				return arr;
			}
		};

		template <unsigned int Base, typename Tr>
		struct IntConversion<bool, Base, Tr, void> {
			static constexpr ReversedSizedArray<std::decay_t<decltype(std::declval<Tr>().to_digit(1))>, 2> to_ary (bool in) {
				using RetType = ReversedSizedArray<std::decay_t<decltype(std::declval<Tr>().to_digit(1))>, 2>;

				RetType arr;
				arr.push_front('\0');
				arr.push_front(in ? Tr::to_digit(1) : Tr::to_digit(0));
				return arr;
			}
		};

		template <typename I, typename Tr>
		struct IntConversion<I, 10, Tr, typename std::enable_if<std::is_integral<I>::value and not std::is_same<I, bool>::value>::type> {
			static constexpr ReversedSizedArray<std::decay_t<decltype(std::declval<Tr>().to_digit(1))>, implem::int_info<I, 10>::max_len + 1> to_ary (I in) {
				using RetType = ReversedSizedArray<std::decay_t<decltype(std::declval<Tr>().to_digit(1))>, implem::int_info<I, 10>::max_len + 1>;
				using Num = implem::NumberAdaptation<I, 10>;

				const constexpr char lookup[201] = "000102030405060708091011121314"
					"1516171819202122232425262728293031323334353637383940414243"
					"4445464748495051525354555657585960616263646566676869707172"
					"737475767778798081828384858687888990919293949596979899";
				const bool was_negative = implem::is_negative<I, 10>(in);

				RetType arr;
				arr.push_front('\0');
				while (Num::abs(in) >= static_cast<I>(100)) {
					arr.push_front(Tr::to_digit(static_cast<int>(lookup[(Num::abs(in) % 100) * 2 + 1] - '0')));
					arr.push_front(Tr::to_digit(static_cast<int>(lookup[(Num::abs(in) % 100) * 2 + 0] - '0')));
					in = static_cast<I>(in / static_cast<I>(100));
				};
				if (Num::abs(in) < static_cast<I>(10)) {
					arr.push_front(Tr::to_digit(static_cast<int>(Num::abs(in))));
				}
				else {
					arr.push_front(Tr::to_digit(static_cast<int>(lookup[Num::abs(in) * 2 + 1] - '0')));
					arr.push_front(Tr::to_digit(static_cast<int>(lookup[Num::abs(in) * 2 + 0] - '0')));
				}
				if (was_negative)
					arr.push_front(Tr::Minus);
				return arr;
			}
		};

		template <typename I, unsigned int Base, typename Tr>
		struct AryConversion {
			template <typename C>
			static I from_ary (C* beg, C* end) {
				I retval = 0;
				I factor = 1;
				std::size_t i = end - beg;
				const bool was_negative = (i and *beg == Tr::Minus);
				if (i and (*beg == Tr::Minus or *beg == Tr::Plus)) {
					i--;
					beg++;
				}

				while (i--) {
					retval += Tr::from_digit(beg[i]) * factor;
					factor *= Base;
				}
				return retval;
			}
		};

		template <typename I, typename Tr, typename=typename std::enable_if<Tr::BehavesLikeASCII and std::is_integral<I>::value and not std::is_same<I, bool>::value and sizeof(I) <= sizeof(uint32_t)>::type>
		using SelectIForSSEToInt = I;

		template <typename I, unsigned int Base, typename Tr>
		struct AryConversion<SelectIForSSEToInt<I, Tr>, Base, Tr> {
			template <typename C> static I from_ary (C* beg, C* end) { return to_integer_sse<I, C, Base, Tr>(beg, end - beg); }
		};

		template <unsigned int Base, typename Tr>
		struct AryConversion<bool, Base, Tr> {
			template <typename C> static bool from_ary (C* beg, C* end) {
				if (end == beg)
					return false;
				return (Tr::from_digit(*beg) ? true : false);
			}
		};

		template <typename T>
		[[gnu::always_inline,gnu::pure]]
		inline T negated_ifn (T n, bool negate) {
			//return static_cast<int32_t>(((static_cast<unsigned int>(n) - (mask bitand 1)) xor mask) bitor ((mask bitand 1) << 31));
			return (negate ? -n : n);
		}

		template <typename T, typename C, unsigned int Base, typename Tr>
		[[gnu::pure]]
		T to_integer_sse (const C* s, std::size_t l) {
			static const constexpr int base1 = static_cast<int>(Base);
			static const constexpr int base2 = base1 * base1;
			static const constexpr int base3 = base1 * base1 * base1;
			static const constexpr int base4 = base2 * base2;
			__builtin_prefetch(s, 0);

			const bool was_negative = (l and *s == Tr::Minus);
			if (l and (*s == Tr::Minus or *s == Tr::Plus)) {
				l--;
				s++;
			}

			switch (l) {
			case 0:
				return 0;
			case 1:
				return negated_ifn(Tr::from_digit(*s), was_negative);
			case 2:
				return negated_ifn(Tr::from_digit(s[0]) * base1 + Tr::from_digit(s[1]), was_negative);
			case 3:
				return negated_ifn(Tr::from_digit(s[0]) * base2 + Tr::from_digit(s[1]) * base1 + Tr::from_digit(s[2]), was_negative);
			default:
				{
					__m128i factor = _mm_set_epi32(base3, base2, base1, 1);
					__m128i res = _mm_set1_epi32(0);
					const __m128i char_0 = _mm_set1_epi32(Tr::FirstDigit);
					const __m128i char_a = _mm_set1_epi32(Tr::FirstLetter);
					std::size_t idx = 0;
					const std::size_t cap = l bitand -4;
					do {
						const __m128i digits = _mm_set_epi32(s[cap - idx - 3 - 1], s[cap - idx - 2 - 1], s[cap - idx - 1 - 1], s[cap - idx - 0 - 1]);
						const __m128i mask = _mm_cmplt_epi32(digits, char_a);
						const __m128i addend = _mm_add_epi32(_mm_andnot_si128(mask, _mm_sub_epi32(char_a, _mm_set1_epi32(10))), _mm_and_si128(mask, char_0));
						res = _mm_add_epi32(res, muly(_mm_sub_epi32(digits, addend), factor));
						factor = muly(factor, _mm_set1_epi32(base4));
						idx += 4;
					} while (l - idx > 3);

					{
						res = _mm_add_epi32(res, _mm_srli_si128(res, 8));
						res = _mm_add_epi32(res, _mm_srli_si128(res, 4));
						const std::array<int, 4> scale {1, base1, base2, base3};
						return negated_ifn(to_integer_sse<T, C, Base, Tr>(s + idx, l - idx) + _mm_cvtsi128_si32(res) * scale[l - idx], was_negative);
					}
				}
			}
		}
	} //namespace implem

	template <typename C, C FDigit='0', C FLetter='a', C CPlus='+', C CMinus='-'>
	struct ASCIITranslator {
		static const constexpr bool BehavesLikeASCII = true;
		static const constexpr C FirstDigit = FDigit;
		static const constexpr C FirstLetter = FLetter;
		static const constexpr C Plus = CPlus;
		static const constexpr C Minus = CMinus;

		static constexpr C to_digit (unsigned int num) {
			return (num <= 9 ?
				static_cast<C>(num + FirstDigit) :
				static_cast<C>(num + FirstLetter - 10)
			);
		}

		static constexpr int from_digit (C dig) {
			return (dig < FirstLetter ?
				dig - FirstDigit :
				dig - FirstLetter + 10
			);
		}
	};
	template <typename C>
	using ASCIITranslatorUpcase = ASCIITranslator<C, 'A'>;

	template <typename I, unsigned int Base=10, typename Tr=ASCIITranslator<char>>
	constexpr inline auto int_to_ary (I in) {
		return implem::IntConversion<std::decay_t<I>, Base, Tr>::to_ary(in);
	}

	template <typename R, typename C, unsigned int Base=10, typename Tr=ASCIITranslator<C>>
	inline R ary_to_int (C* beg, C* end) {
		return implem::AryConversion<R, Base, Tr>::from_ary(beg, end);
	}

#if !defined(INT_CONV_WITHOUT_HELPERS)
	template <typename T, std::size_t S>
	std::basic_string_view<T> to_string_view (const ReversedSizedArray<T, S>& ary) {
		return std::basic_string_view<T>(ary.data(), ary.size() - 1);
	}
#endif
} //namespace dhandy

#endif
