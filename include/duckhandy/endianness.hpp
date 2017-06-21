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

#include <cstdint>
#include <endian.h>

namespace dhandy {
	template <typename T> constexpr T htobe (T parV);
	template <typename T> constexpr T htole (T parV);
	template <typename T> constexpr T betoh (T parV);
	template <typename T> constexpr T letoh (T parV);

	template <>
	[[gnu::pure]] inline constexpr uint8_t htobe (uint8_t parV) {
		return parV;
	}
	template <>
	[[gnu::pure]] inline constexpr uint16_t htobe (uint16_t parV) {
#if __BYTE_ORDER == __BIG_ENDIAN
		return parV;
#elif __BYTE_ORDER == __LITTLE_ENDIAN
		return __builtin_bswap16(parV);
#else
#	error "Unsupported endianness"
#endif
	}
	template <>
	[[gnu::pure]] inline constexpr uint32_t htobe (uint32_t parV) {
#if __BYTE_ORDER == __BIG_ENDIAN
		return parV;
#elif __BYTE_ORDER == __LITTLE_ENDIAN
		return __builtin_bswap32(parV);
#else
#	error "Unsupported endianness"
#endif
	}
	template <>
	[[gnu::pure]] inline constexpr uint64_t htobe (uint64_t parV) {
#if __BYTE_ORDER == __BIG_ENDIAN
		return parV;
#elif __BYTE_ORDER == __LITTLE_ENDIAN
		return __builtin_bswap64(parV);
#else
#	error "Unsupported endianness"
#endif
	}
	template <>
	[[gnu::pure]] inline constexpr int8_t htobe (int8_t parV) {
		return parV;
	}
	template <>
	[[gnu::pure]] inline constexpr int16_t htobe (int16_t parV) {
#if __BYTE_ORDER == __BIG_ENDIAN
		return parV;
#elif __BYTE_ORDER == __LITTLE_ENDIAN
		return static_cast<int16_t>(__builtin_bswap16(static_cast<uint16_t>(parV)));
#else
#	error "Unsupported endianness"
#endif
	}
	template <>
	[[gnu::pure]] inline constexpr int32_t htobe (int32_t parV) {
#if __BYTE_ORDER == __BIG_ENDIAN
		return parV;
#elif __BYTE_ORDER == __LITTLE_ENDIAN
		return static_cast<int32_t>(__builtin_bswap32(static_cast<uint32_t>(parV)));
#else
#	error "Unsupported endianness"
#endif
	}
	template <>
	[[gnu::pure]] inline constexpr int64_t htobe (int64_t parV) {
#if __BYTE_ORDER == __BIG_ENDIAN
		return parV;
#elif __BYTE_ORDER == __LITTLE_ENDIAN
		return static_cast<int64_t>(__builtin_bswap64(static_cast<uint64_t>(parV)));
#else
#	error "Unsupported endianness"
#endif
	}
	template <>
	[[gnu::pure]] inline constexpr long long int htobe (long long int parV) {
		static_assert(sizeof(long long int) == sizeof(uint64_t), "Size mismatch");
#if __BYTE_ORDER == __BIG_ENDIAN
		return parV;
#elif __BYTE_ORDER == __LITTLE_ENDIAN
		return static_cast<long long int>(__builtin_bswap64(static_cast<uint64_t>(parV)));
#else
#	error "Unsupported endianness"
#endif
	}
	template <>
	[[gnu::pure]] inline constexpr unsigned long long int htobe (unsigned long long int parV) {
		static_assert(sizeof(unsigned long long int) == sizeof(uint64_t), "Size mismatch");
#if __BYTE_ORDER == __BIG_ENDIAN
		return parV;
#elif __BYTE_ORDER == __LITTLE_ENDIAN
		return static_cast<unsigned long long int>(__builtin_bswap64(static_cast<uint64_t>(parV)));
#else
#	error "Unsupported endianness"
#endif
	}

	template <>
	[[gnu::pure]] inline constexpr uint8_t htole (uint8_t parV) {
		return parV;
	}
	template <>
	[[gnu::pure]] inline constexpr uint16_t htole (uint16_t parV) {
#if __BYTE_ORDER == __BIG_ENDIAN
		return __builtin_bswap16(parV);
#elif __BYTE_ORDER == __LITTLE_ENDIAN
		return parV;
#else
#	error "Unsupported endianness"
#endif
	}
	template <>
	[[gnu::pure]] inline constexpr uint32_t htole (uint32_t parV) {
#if __BYTE_ORDER == __BIG_ENDIAN
		return __builtin_bswap32(parV);
#elif __BYTE_ORDER == __LITTLE_ENDIAN
		return parV;
#else
#	error "Unsupported endianness"
#endif
	}
	template <>
	[[gnu::pure]] inline constexpr uint64_t htole (uint64_t parV) {
#if __BYTE_ORDER == __BIG_ENDIAN
		return __builtin_bswap64(parV);
#elif __BYTE_ORDER == __LITTLE_ENDIAN
		return parV;
#else
#	error "Unsupported endianness"
#endif
	}
	template <>
	[[gnu::pure]] inline constexpr int8_t htole (int8_t parV) {
		return parV;
	}
	template <>
	[[gnu::pure]] inline constexpr int16_t htole (int16_t parV) {
#if __BYTE_ORDER == __BIG_ENDIAN
		return static_cast<int16_t>(__builtin_bswap16(static_cast<uint16_t>(parV)));
#elif __BYTE_ORDER == __LITTLE_ENDIAN
		return parV;
#else
#	error "Unsupported endianness"
#endif
	}
	template <>
	[[gnu::pure]] inline constexpr int32_t htole (int32_t parV) {
#if __BYTE_ORDER == __BIG_ENDIAN
		return static_cast<int32_t>(__builtin_bswap32(static_cast<uint32_t>(parV)));
#elif __BYTE_ORDER == __LITTLE_ENDIAN
		return parV;
#else
#	error "Unsupported endianness"
#endif
	}
	template <>
	[[gnu::pure]] inline constexpr int64_t htole (int64_t parV) {
#if __BYTE_ORDER == __BIG_ENDIAN
		return static_cast<int64_t>(__builtin_bswap64(static_cast<uint64_t>(parV)));
#elif __BYTE_ORDER == __LITTLE_ENDIAN
		return parV;
#else
#	error "Unsupported endianness"
#endif
	}
	template <>
	[[gnu::pure]] inline constexpr long long int htole (long long int parV) {
		static_assert(sizeof(long long int) == sizeof(uint64_t), "Size mismatch");
#if __BYTE_ORDER == __BIG_ENDIAN
		return static_cast<long long int>(__builtin_bswap64(static_cast<uint64_t>(parV)));
#elif __BYTE_ORDER == __LITTLE_ENDIAN
		return parV;
#else
#	error "Unsupported endianness"
#endif
	}
	template <>
	[[gnu::pure]] inline constexpr unsigned long long int htole (unsigned long long int parV) {
		static_assert(sizeof(unsigned long long int) == sizeof(uint64_t), "Size mismatch");
#if __BYTE_ORDER == __BIG_ENDIAN
		return static_cast<unsigned long long int>(__builtin_bswap64(static_cast<uint64_t>(parV)));
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
