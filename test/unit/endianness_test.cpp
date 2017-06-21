/* Copyright 2017, Michele Santullo
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

#include "catch.hpp"
#include "duckhandy/endianness.hpp"
#include <endian.h>

TEST_CASE ("Host to little-endian", "[htole][endianness]") {
	using dhandy::htole;
#if __BYTE_ORDER == __BIG_ENDIAN
	static_assert(htole<uint8_t>(0x12) == 0x12, "Wrong conversion");
	static_assert(htole<uint16_t>(0x1234) == 0x3412, "Wrong conversion");
	static_assert(htole<uint32_t>(0x12345678) == 0x78563412, "Wrong conversion");
	static_assert(htole<uint64_t>(0x123456789ABCDEF0) == 0xF0DEBC9A78563412, "Wrong conversion");
#elif __BYTE_ORDER == __LITTLE_ENDIAN
	static_assert(htole<uint8_t>(0x12) == 0x12, "Wrong conversion");
	static_assert(htole<uint16_t>(0x1234) == 0x1234, "Wrong conversion");
	static_assert(htole<uint32_t>(0x12345678) == 0x12345678, "Wrong conversion");
	static_assert(htole<uint64_t>(0x123456789ABCDEF0) == 0x123456789ABCDEF0, "Wrong conversion");
#endif

	CHECK(htole<uint8_t>(0x12) == 0x12);
	CHECK(htole<uint16_t>(0x1234) == htole16(0x1234));
	CHECK(htole<uint32_t>(0x12345678) == htole32(0x12345678));
	CHECK(htole<uint64_t>(0x123456789ABCDEF0) == htole64(0x123456789ABCDEF0));

	CHECK(htole<int8_t>(0xFE) == static_cast<int8_t>(0xFE));
	CHECK(htole<int16_t>(0xFEDC) == static_cast<int16_t>(htole16(0xFEDC)));
	CHECK(htole<int32_t>(0xFEDCBA09) == static_cast<int32_t>(htole32(0xFEDCBA09)));
	CHECK(htole<int64_t>(0xFEDCBA0987654321) == static_cast<int64_t>(htole64(0xFEDCBA0987654321)));
}

TEST_CASE ("Little-endian to host", "[letoh][endianness]") {
	using dhandy::letoh;
#if __BYTE_ORDER == __BIG_ENDIAN
	static_assert(letoh<uint8_t>(0x12) == 0x12, "Wrong conversion");
	static_assert(letoh<uint16_t>(0x1234) == 0x3412, "Wrong conversion");
	static_assert(letoh<uint32_t>(0x12345678) == 0x78563412, "Wrong conversion");
	static_assert(letoh<uint64_t>(0x123456789ABCDEF0) == 0xF0DEBC9A78563412, "Wrong conversion");
#elif __BYTE_ORDER == __LITTLE_ENDIAN
	static_assert(letoh<uint8_t>(0x12) == 0x12, "Wrong conversion");
	static_assert(letoh<uint16_t>(0x1234) == 0x1234, "Wrong conversion");
	static_assert(letoh<uint32_t>(0x12345678) == 0x12345678, "Wrong conversion");
	static_assert(letoh<uint64_t>(0x123456789ABCDEF0) == 0x123456789ABCDEF0, "Wrong conversion");
#endif

	CHECK(letoh<uint8_t>(0x12) == 0x12);
	CHECK(letoh<uint16_t>(0x1234) == le16toh(0x1234));
	CHECK(letoh<uint32_t>(0x12345678) == le32toh(0x12345678));
	CHECK(letoh<uint64_t>(0x123456789ABCDEF0) == le64toh(0x123456789ABCDEF0));

	CHECK(letoh<int8_t>(0xFE) == static_cast<int8_t>(0xFE));
	CHECK(letoh<int16_t>(0xFEDC) == static_cast<int16_t>(le16toh(0xFEDC)));
	CHECK(letoh<int32_t>(0xFEDCBA09) == static_cast<int32_t>(le32toh(0xFEDCBA09)));
	CHECK(letoh<int64_t>(0xFEDCBA0987654321) == static_cast<int64_t>(le64toh(0xFEDCBA0987654321)));
}

TEST_CASE ("Host to big-endian", "[htobe][endianness]") {
	using dhandy::htobe;
#if __BYTE_ORDER == __BIG_ENDIAN
	static_assert(htobe<uint8_t>(0x12) == 0x12, "Wrong conversion");
	static_assert(htobe<uint16_t>(0x1234) == 0x1234, "Wrong conversion");
	static_assert(htobe<uint32_t>(0x12345678) == 0x12345678, "Wrong conversion");
	static_assert(htobe<uint64_t>(0x123456789ABCDEF0) == 0x123456789ABCDEF0, "Wrong conversion");
#elif __BYTE_ORDER == __LITTLE_ENDIAN
	static_assert(htobe<uint8_t>(0x12) == 0x12, "Wrong conversion");
	static_assert(htobe<uint16_t>(0x1234) == 0x3412, "Wrong conversion");
	static_assert(htobe<uint32_t>(0x12345678) == 0x78563412, "Wrong conversion");
	static_assert(htobe<uint64_t>(0x123456789ABCDEF0) == 0xF0DEBC9A78563412, "Wrong conversion");
#endif

	CHECK(htobe<uint8_t>(0x12) == 0x12);
	CHECK(htobe<uint16_t>(0x1234) == htobe16(0x1234));
	CHECK(htobe<uint32_t>(0x12345678) == htobe32(0x12345678));
	CHECK(htobe<uint64_t>(0x123456789ABCDEF0) == htobe64(0x123456789ABCDEF0));

	CHECK(htobe<int8_t>(0xFE) == static_cast<int8_t>(0xFE));
	CHECK(htobe<int16_t>(0xFEDC) == static_cast<int16_t>(htobe16(0xFEDC)));
	CHECK(htobe<int32_t>(0xFEDCBA09) == static_cast<int32_t>(htobe32(0xFEDCBA09)));
	CHECK(htobe<int64_t>(0xFEDCBA0987654321) == static_cast<int64_t>(htobe64(0xFEDCBA0987654321)));
}

TEST_CASE ("Big-endian to host", "[betoh][endianness]") {
	using dhandy::betoh;
#if __BYTE_ORDER == __BIG_ENDIAN
	static_assert(betoh<uint8_t>(0x12) == 0x12, "Wrong conversion");
	static_assert(betoh<uint16_t>(0x1234) == 0x1234, "Wrong conversion");
	static_assert(betoh<uint32_t>(0x12345678) == 0x12345678, "Wrong conversion");
	static_assert(betoh<uint64_t>(0x123456789ABCDEF0) == 0x123456789ABCDEF0, "Wrong conversion");
#elif __BYTE_ORDER == __LITTLE_ENDIAN
	static_assert(betoh<uint8_t>(0x12) == 0x12, "Wrong conversion");
	static_assert(betoh<uint16_t>(0x1234) == 0x3412, "Wrong conversion");
	static_assert(betoh<uint32_t>(0x12345678) == 0x78563412, "Wrong conversion");
	static_assert(betoh<uint64_t>(0x123456789ABCDEF0) == 0xF0DEBC9A78563412, "Wrong conversion");
#endif

	CHECK(betoh<uint8_t>(0x12) == 0x12);
	CHECK(betoh<uint16_t>(0x1234) == be16toh(0x1234));
	CHECK(betoh<uint32_t>(0x12345678) == be32toh(0x12345678));
	CHECK(betoh<uint64_t>(0x123456789ABCDEF0) == be64toh(0x123456789ABCDEF0));

	CHECK(betoh<int8_t>(0xFE) == static_cast<int8_t>(0xFE));
	CHECK(betoh<int16_t>(0xFEDC) == static_cast<int16_t>(be16toh(0xFEDC)));
	CHECK(betoh<int32_t>(0xFEDCBA09) == static_cast<int32_t>(be32toh(0xFEDCBA09)));
	CHECK(betoh<int64_t>(0xFEDCBA0987654321) == static_cast<int64_t>(be64toh(0xFEDCBA0987654321)));
}
