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

#ifndef id942A6B5AB2AF443C82D4321775BFC9E8
#define id942A6B5AB2AF443C82D4321775BFC9E8

#include "compatibility.h"
#include "sequence_bt.hpp"
#include "MaxSizedArray.hpp"
#include "sprout/math/log10.hpp"
#include "sprout/math/log2.hpp"
#include "sprout/math/pow.hpp"
#include "sprout/math/abs.hpp"
#include "sprout/limits.hpp"
#include <type_traits>
#include <utility>
#include <cstdint>
#include <algorithm>
#include <string>
#include <ciso646>
#include <climits>
#include <cstddef>
#include <iterator>

namespace dhandy {
	namespace customize {
		template<typename T>
		struct index_array_to_string;

		template<typename C, typename T>
		struct char_to_int;
	} //namespace customize

	namespace implem {
		template <typename T>
		typename std::make_unsigned<T>::type abs ( T parValue ) a_pure;

		template <typename T> int count_leading_zeroes ( typename std::enable_if<sprout::numeric_limits<T>::is_signed, T>::type parValue ) a_always_inline;
		template <typename T> int count_leading_zeroes ( typename std::enable_if<not sprout::numeric_limits<T>::is_signed, T>::type parValue ) a_always_inline;
		int count_leading_zeroes_overload ( unsigned char parValue ) a_always_inline;
		int count_leading_zeroes_overload ( unsigned short int parValue ) a_always_inline;
		int count_leading_zeroes_overload ( unsigned int parValue ) a_always_inline;
		int count_leading_zeroes_overload ( unsigned long parValue ) a_always_inline;
		int count_leading_zeroes_overload ( unsigned long long parValue ) a_always_inline;

		template <std::size_t Base, std::size_t Val>
		struct power {
			enum { value = Base * power<Base, Val - 1>::value };
		};
		template <std::size_t Base>
		struct power<Base, 0> {
			enum { value = 1 };
		};

		template <typename T, bool=sprout::numeric_limits<T>::is_signed>
		struct is_negative;
		template <typename T>
		struct is_negative<T, true> {
			static int check (T parValue) { return (parValue < 0 ? 1 : 0); }
		};
		template <typename T>
		struct is_negative<T, false> {
			static constexpr int check (T) { return 0; }
		};

		template <template <typename> class Tag, typename F>
		inline auto int_to_string (const F parFrom) -> MaxSizedArray<uint8_t, Tag<F>::count_digits_bt(sprout::numeric_limits<F>::max())> {
			using ArrayRetType = MaxSizedArray<uint8_t, Tag<F>::count_digits_bt(sprout::numeric_limits<F>::max())>;

			ArrayRetType retval;
			F div = 1;
			constexpr const std::size_t charset_offs = (Tag<F>::lower_case ? Tag<F>::base : 0);
			const auto sign_length = (is_negative<F>::check(parFrom) and Tag<F>::sign_allowed ? 1 : 0);
			for (std::size_t z = 0; z < Tag<F>::count_digits(parFrom) - sign_length; ++z) {
				retval.push_back(static_cast<uint8_t>(((parFrom / div) % Tag<F>::base) + charset_offs));
				div *= Tag<F>::base;
			}
			std::reverse(retval.begin(), retval.end());
			return retval;
		};

		template <template <typename> class Tag, typename T, typename F>
		inline T string_to_int (const F& parFrom) {
			T retval(0);
			T mul(1);
			const auto sgn = dhandy::customize::char_to_int<typename F::value_type, T>::sgn(parFrom);
			for (auto it = std::rbegin(parFrom), itEND = std::rend(parFrom); it + (sgn < 0 ? 1 : 0) != itEND; ++it) {
				auto chara = *it;
				retval += dhandy::customize::char_to_int<decltype(chara), T>::make(chara) * mul;
				mul *= Tag<T>::base;
			}
			return retval * sgn;
		};

		template <typename T, bool LowerCase>
		struct hex {
			enum {
				base = 16,
				sign_allowed = 0,
				lower_case = (LowerCase ? 1 : 0)
			};

			static std::size_t count_digits ( T parValue ) a_pure;
			static constexpr std::size_t count_digits_bt (T parNum) {
				return (parNum == 0 ? 0 : static_cast<std::size_t>(sprout::log10(sprout::abs(static_cast<long double>(parNum))) / sprout::log10(static_cast<double>(base)))) + 1;
			}
		};
	} //namespace implem

	namespace tags {
		template <typename T>
		struct dec {
			enum {
				base = 10,
				sign_allowed = 1,
				lower_case = 0
			};

			template <std::size_t... Powers, std::size_t... Digits>
			static std::size_t count_digits_implem (T parValue, dhandy::bt::index_seq<Powers...>, dhandy::bt::index_seq<Digits...>) a_pure;

			static std::size_t count_digits (T parValue) a_pure;

			static constexpr std::size_t count_digits_bt (T parNum) {
				return (parNum == 0 ? 0 : static_cast<std::size_t>(sprout::log10(sprout::abs(static_cast<long double>(parNum))))) + 1 + (sprout::numeric_limits<T>::is_signed ? 1 : 0);
			}
		};

		template <typename T>
		using hex = dhandy::implem::hex<T, false>;
		template <typename T>
		using hexl = dhandy::implem::hex<T, true>;

		template <typename T>
		struct bin {
			enum {
				base = 2,
				sign_allowed = 0,
				lower_case = 0
			};

			static std::size_t count_digits ( T parValue ) a_pure;
			static constexpr std::size_t count_digits_bt (T parNum) {
				return (parNum == 0 ? 0 : static_cast<std::size_t>(sprout::log2(sprout::abs(static_cast<long double>(parNum))))) + 1;
			}
		};

		//See: http://stackoverflow.com/questions/9721042/count-number-of-digits-which-method-is-most-efficient#9721113
		template <typename T>
		template <std::size_t... Powers, std::size_t... Digits>
		std::size_t dec<T>::count_digits_implem (T parValue, dhandy::bt::index_seq<Powers...>, dhandy::bt::index_seq<Digits...>) {
			static_assert(sizeof...(Digits) == CHAR_BIT * sizeof(T) + 1, "Too many values for Digits");
			typedef typename std::make_unsigned<T>::type UT;
			static constexpr UT powers[] = { 0, static_cast<UT>(dhandy::implem::power<10, Powers + 1>::value)... };
			//the maxdigits table is [len(str(pow(2,b))) for b in range(0,MAX_BITS)]
			static constexpr std::size_t maxdigits[] = { static_cast<std::size_t>(static_cast<double>(Digits) / sprout::log2(10.0)) + 1 ... };
			static_assert(maxdigits[sizeof(maxdigits) / sizeof(maxdigits[0]) - 1] <= sprout::numeric_limits<T>::max(), "Last item in maxdigits overflows T");
			const auto bits = sizeof(parValue) * CHAR_BIT - dhandy::implem::count_leading_zeroes<T>(dhandy::implem::abs(parValue));
			static_assert(std::is_same<UT, decltype(dhandy::implem::abs(parValue))>::value, "Unexpected type");
			assert(bits < sizeof(maxdigits) / sizeof(maxdigits[0]));
			return (dhandy::implem::abs(parValue) < powers[maxdigits[bits] - 1] ? maxdigits[bits] - 1 : maxdigits[bits]) + dhandy::implem::is_negative<T>::check(parValue);
		}

		template <typename T>
		std::size_t dec<T>::count_digits (T parValue) {
			return count_digits_implem(
				parValue,
				dhandy::bt::index_range<0, count_digits_bt(sprout::numeric_limits<T>::max()) - (sprout::numeric_limits<T>::is_signed ? 1 : 0) - 1>(),
				dhandy::bt::index_range<0, CHAR_BIT * sizeof(T) + 1>()
			);
		}

		template <typename T>
		std::size_t bin<T>::count_digits (T parValue) {
			return std::max<std::size_t>((sizeof(parValue) * CHAR_BIT - dhandy::implem::count_leading_zeroes<T>(parValue)), 1);
		}
	} //namespace tags

	namespace implem {
		template <template <typename> class Tag>
		struct lexical_cast {
			template <typename T, typename F>
			static T convert ( const typename std::enable_if<std::is_integral<F>::value, F>::type& parFrom ) {
				const auto indices = int_to_string<Tag, F>(parFrom);
				return dhandy::customize::index_array_to_string<T>::make(indices, is_negative<F>::check(parFrom) bitand Tag<F>::sign_allowed);
			}

			template <typename T, typename F>
			static typename std::enable_if<std::is_integral<T>::value, T>::type convert ( const F& parFrom ) {
				return string_to_int<Tag, T, F>(parFrom);
			}
		};

		template <typename T>
		inline int count_leading_zeroes (typename std::enable_if<sprout::numeric_limits<T>::is_signed, T>::type parValue) {
			return count_leading_zeroes<decltype(dhandy::implem::abs(parValue))>(dhandy::implem::abs(parValue));
		}

		template <typename T>
		inline int count_leading_zeroes (typename std::enable_if<not sprout::numeric_limits<T>::is_signed, T>::type parValue) {
			return count_leading_zeroes_overload(parValue) + sizeof(T) * CHAR_BIT;
		}

		inline int count_leading_zeroes_overload (unsigned char parValue) {
			return __builtin_clz(parValue) - sizeof(unsigned int) * CHAR_BIT;
		}
		inline int count_leading_zeroes_overload (unsigned short int parValue) {
			return __builtin_clz(parValue) - sizeof(unsigned int) * CHAR_BIT;
		}
		inline int count_leading_zeroes_overload (unsigned int parValue) {
			return __builtin_clz(parValue) - sizeof(unsigned int) * CHAR_BIT;
		}
		inline int count_leading_zeroes_overload (unsigned long parValue) {
			return __builtin_clzl(parValue) - sizeof(unsigned long) * CHAR_BIT;
		}
		inline int count_leading_zeroes_overload (unsigned long long parValue) {
			return __builtin_clzll(parValue) - sizeof(unsigned long long) * CHAR_BIT;
		}

		//See: http://stackoverflow.com/questions/16101062/why-does-stdabs-return-signed-types
		template <typename T>
		typename std::make_unsigned<T>::type abs (T parValue) {
			//We need to cast before negating x to avoid the overflow.
			return (parValue < 0 ? -static_cast<typename std::make_unsigned<T>::type>(parValue) : parValue);
		}

		template <typename T, bool LowerCase>
		std::size_t hex<T, LowerCase>::count_digits (T parValue) {
			return std::max<std::size_t>(((sizeof(parValue) * CHAR_BIT - dhandy::implem::count_leading_zeroes<typename std::make_unsigned<T>::type>(make_unsigned(parValue))) + (CHAR_BIT / 2 - 1)) / (CHAR_BIT / 2), 1);
		}
	} //namespace implem

	template <typename T, template <typename> class Tag=tags::dec, typename F=void>
	inline T lexical_cast (const F& parFrom) {
		return dhandy::implem::lexical_cast<Tag>::template convert<T, F>(parFrom);
	}

	namespace customize {
		template<>
		struct index_array_to_string<std::string> {
			template<std::size_t N>
			static std::string make (const MaxSizedArray<uint8_t, N> &parIndices, int parNegative) {
				static const char symbols[] = {'0', '1', '2', '3', '4', '5',
											   '6', '7', '8', '9', 'A', 'B',
											   'C', 'D', 'E', 'F',
											   '0', '1', '2', '3', '4', '5',
											   '6', '7', '8', '9', 'a', 'b',
											   'c', 'd', 'e', 'f'
				};
				std::string retval(parIndices.size() + parNegative, '-');
				for (auto z = parNegative; z < static_cast<int>(parIndices.size()) + parNegative; ++z) {
					retval[z] = symbols[parIndices[z - parNegative]];
				}
				return retval;
			}
		};

		template<typename T>
		struct char_to_int<char, T> {
			static T make (char parChar) {
				if (parChar >= '0' and parChar <= '9')
					return parChar - '0';
				else if (parChar >= 'a' and parChar <= 'f')
					return 10 + parChar - 'a';
				else if (parChar >= 'A' and parChar <= 'F')
					return 10 + parChar - 'A';
				else if (parChar == '-')
					return 0;
				return 0;
			}

			template <typename Container>
			static T sgn (const Container& parString) {
				return static_cast<T>(sprout::numeric_limits<T>::is_signed and std::begin(parString) != std::end(parString) and *std::begin(parString) == '-' ? -1 : 1);
			}
		};
	} //namespace customize
} //namespace dhandy
#endif
