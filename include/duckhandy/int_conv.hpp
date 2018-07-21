/* Copyright 2016, 2017 Michele Santullo
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

namespace dhandy {
	namespace implem {
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
			static const constexpr bool always_unsigned = (Base == 16 or Base == 2);
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
			static constexpr L abs(L in) { return (not BecomesUnsigned and std::numeric_limits<L>::is_signed and in < L(0) ? -in : in); }
			static constexpr CastedType cast (I in) { return static_cast<CastedType>(in); }
		};
	} //namespace implem

	template <typename C, C FirstLetter='a'>
	struct DefaultTranslator {
		static constexpr C to_digit (unsigned int num) {
			return (num <= 9 ?
				static_cast<C>(num + '0') :
				static_cast<C>(num + FirstLetter - 10)
			);
		}
		static constexpr C minus() { return '-'; }
	};

	template <typename I, unsigned int Base=10, typename Tr=DefaultTranslator<char>>
	constexpr inline ReversedSizedArray<std::decay_t<decltype(std::declval<Tr>().to_digit(1))>, implem::int_info<I, Base>::max_len + 1> int_to_ary (I in) {
		using RetType = ReversedSizedArray<std::decay_t<decltype(std::declval<Tr>().to_digit(1))>, implem::int_info<I, Base>::max_len + 1>;
		using Num = implem::NumberAdaptation<std::decay_t<I>, Base>;

		const bool was_negative = implem::is_negative<I, Base>(in);

		RetType arr;
		arr.push_front('\0');
		do {
			arr.push_front(Tr::to_digit(static_cast<int>(Num::abs(Num::cast(in)) % Base)));
			in = static_cast<I>(Num::cast(in) / static_cast<I>(Base));
		} while (in);
		if (was_negative)
			arr.push_front(Tr::minus());
		return arr;
	}

#if !defined(INT_CONV_WITHOUT_HELPERS)
	template <typename T, std::size_t S>
	std::basic_string_view<T> to_string_view (const ReversedSizedArray<T, S>& ary) {
		return std::basic_string_view<T>(ary.data(), ary.size() - 1);
	}
#endif
} //namespace dhandy

#endif
