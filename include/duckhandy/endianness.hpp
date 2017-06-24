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

#ifndef id1A975372553B45BC8C4E42CDBDD97497
#define id1A975372553B45BC8C4E42CDBDD97497

#include "ducktypes.hpp"
#include "int_types.hpp"
#include <cstdint>
#include <endian.h>
#include <type_traits>

namespace dhandy {
	template <typename T> constexpr typename std::enable_if<std::is_integral<T>::value, T>::type htobe (T parV);
	template <typename T> constexpr typename std::enable_if<std::is_integral<T>::value, T>::type htole (T parV);
	template <typename T> constexpr T betoh (T parV);
	template <typename T> constexpr T letoh (T parV);

	namespace implem {
		template <unsigned int S> constexpr
		typename int_t<S, false>::type bswap (typename int_t<S, false>::type parV);

		template <>
		[[gnu::pure]] inline constexpr
		u8 bswap<1> (u8 parV) { return parV; }

		template <>
		[[gnu::pure]] inline constexpr
		u16 bswap<2> (u16 parV) { return __builtin_bswap16(parV); }

		template <>
		[[gnu::pure]] inline constexpr
		u32 bswap<4> (u32 parV) { return __builtin_bswap32(parV); }

		template <>
		[[gnu::pure]] inline constexpr
		u64 bswap<8> (u64 parV) { return __builtin_bswap64(parV); }
	} //namespace implem

	template <typename T>
	[[gnu::pure]] inline constexpr
	auto htobe (T parV) -> typename std::enable_if<std::is_integral<T>::value, T>::type {
#if __BYTE_ORDER == __BIG_ENDIAN
		return parV;
#elif __BYTE_ORDER == __LITTLE_ENDIAN
		return static_cast<T>(implem::bswap<sizeof(T)>(static_cast<typename int_t<sizeof(T), false>::type>(parV)));
#else
#	error "Unsupported endianness"
#endif
	}

	template <typename T>
	[[gnu::pure]] inline constexpr
	auto htole (T parV) -> typename std::enable_if<std::is_integral<T>::value, T>::type {
#if __BYTE_ORDER == __BIG_ENDIAN
		return static_cast<T>(implem::bswap<sizeof(T)>(static_cast<typename int_t<sizeof(T), false>::type>(parV)));
#elif __BYTE_ORDER == __LITTLE_ENDIAN
		return parV;
#else
#	error "Unsupported endianness"
#endif
	}

	template <typename T>
	[[gnu::pure]] inline constexpr T betoh (T parV) {
		return htobe<T>(parV);
	}

	template <typename T>
	[[gnu::pure]] inline constexpr T letoh (T parV) {
		return htole<T>(parV);
	}
} //namespace dhandy

#endif
