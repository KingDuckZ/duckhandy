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

#include "catch.hpp"
#include "duckhandy/int_conv.hpp"
#include "duckhandy/string_bt.hpp"
#include "sprout/cstring/strlen.hpp"
#include <cstdint>

template <typename T> using int_info_10 = dhandy::implem::int_info<T, 10>;
template <typename T> using int_info_16 = dhandy::implem::int_info<T, 16>;
template <typename T> using int_info_2 = dhandy::implem::int_info<T, 2>;

namespace {
	template <typename T, unsigned int Base>
	void AryConversionTestHelper (const std::string_view& s, T expected) {
		using AryConversion = dhandy::implem::AryConversion<T, Base, dhandy::ASCIITranslator<char>>;
		CHECK(AryConversion::from_ary(s.data(), s.data() + s.size()) == expected);
	}
} //unnamed namespace

TEST_CASE ("Check int to char array conversions", "[s2i][int_conv]") {
	using dhandy::int_to_ary;
	using dhandy::bt::string;
	using dhandy::bt::make_string;
	using sprout::strlen;

	CHECK(int_info_10<uint8_t>::max_len == 3);
	CHECK(int_info_10<uint16_t>::max_len == 5);
	CHECK(int_info_10<uint32_t>::max_len == 10);
	CHECK(int_info_10<int8_t>::max_len == 4);
	CHECK(int_info_10<int16_t>::max_len == 6);
	CHECK(int_info_10<int32_t>::max_len == 11);

	CHECK(int_info_16<uint8_t>::max_len == 2);
	CHECK(int_info_16<uint16_t>::max_len == 4);
	CHECK(int_info_16<uint32_t>::max_len == 8);
	CHECK(int_info_16<int8_t>::max_len == 2);
	CHECK(int_info_16<int16_t>::max_len == 4);
	CHECK(int_info_16<int32_t>::max_len == 8);

	CHECK(int_info_2<uint8_t>::max_len == 8);
	CHECK(int_info_2<uint16_t>::max_len == 16);
	CHECK(int_info_2<uint32_t>::max_len == 32);
	CHECK(int_info_2<int8_t>::max_len == 8);
	CHECK(int_info_2<int16_t>::max_len == 16);
	CHECK(int_info_2<int32_t>::max_len == 32);

	static_assert(int_to_ary(5)[0] == '5', "Algorithm error");
	static_assert(string<strlen(int_to_ary(10).data()) + 1>(int_to_ary(10).data()) == make_string("10"), "Algorithm error");
	static_assert(string<strlen(int_to_ary(101).data()) + 1>(int_to_ary(101).data()) == make_string("101"), "Algorithm error");
	static_assert(string<strlen(int_to_ary<uint16_t>(0xAB12).data()) + 1>(int_to_ary<uint16_t>(0xAB12).data()) == make_string("43794"), "Algorithm error");
	static_assert(int_info_10<int16_t>::is_signed == true, "Wrong sign detection");
	static_assert(string<strlen(int_to_ary<int16_t>(0xAB12).data()) + 1>(int_to_ary<int16_t>(0xAB12).data()) == make_string("-21742"), "Algorithm error");

	CHECK(to_string_view(int_to_ary<int64_t>(0x123456789A)) == "78187493530");
	CHECK(to_string_view(int_to_ary<int64_t>(-1)) == "-1");
	CHECK(to_string_view(int_to_ary<int64_t>(0x1000000000000000)) == "1152921504606846976");
	CHECK(to_string_view(int_to_ary<int64_t>(0xF000000000000000)) == "-1152921504606846976");

	CHECK(to_string_view(int_to_ary<uint16_t, 16>(0xFFFF)) == "ffff");
	CHECK(to_string_view(int_to_ary<uint16_t, 16>(0xCACA)) == "caca");
	CHECK(to_string_view(int_to_ary<uint16_t, 16>(0x10)) == "10");
	CHECK(to_string_view(int_to_ary<int16_t, 16>(0x10)) == "10");
	CHECK(to_string_view(int_to_ary<int16_t, 16>(0xF000)) == "f000");
	CHECK(to_string_view(int_to_ary<uint16_t, 16>(0xFEFE)) == "fefe");
	CHECK(to_string_view(int_to_ary<int16_t, 16>(0xFEFE)) == "fefe");
	CHECK(to_string_view(int_to_ary<uint32_t, 8>(0423)) == "423");
	CHECK(to_string_view(int_to_ary<uint32_t, 8>(0777)) == "777");
	CHECK(to_string_view(int_to_ary<int32_t, 8>(0)) == "0");
	CHECK(to_string_view(int_to_ary<uint32_t, 8>(0)) == "0");
	CHECK(to_string_view(int_to_ary<int32_t, 2>(0)) == "0");
	CHECK(to_string_view(int_to_ary<uint32_t, 2>(0)) == "0");
	CHECK(to_string_view(int_to_ary<int32_t, 16>(0)) == "0");
	CHECK(to_string_view(int_to_ary<uint32_t, 16>(0)) == "0");
	CHECK(to_string_view(int_to_ary<int32_t, 10>(0)) == "0");
	CHECK(to_string_view(int_to_ary<uint32_t, 10>(0)) == "0");
	CHECK(to_string_view(int_to_ary<bool, 8>(false)) == "0");
	CHECK(to_string_view(int_to_ary<bool, 8>(true)) == "1");
	CHECK(to_string_view(int_to_ary<bool, 10>(false)) == "0");
	CHECK(to_string_view(int_to_ary<bool, 10>(true)) == "1");
	CHECK(to_string_view(int_to_ary<uint8_t, 2>(0b10101010)) == "10101010");
	CHECK(to_string_view(int_to_ary<int8_t, 2>(0b10101010)) == "10101010");
	CHECK(to_string_view(int_to_ary<uint8_t, 2>(0b11111111)) == "11111111");
	CHECK(to_string_view(int_to_ary<int8_t, 2>(0b11111111)) == "11111111");
	CHECK(to_string_view(int_to_ary<uint16_t, 2>(0b111100001111)) == "111100001111");
	CHECK(to_string_view(int_to_ary<int16_t, 2>(0b111100001111)) == "111100001111");
	CHECK(to_string_view(int_to_ary<int64_t, 36>(9223372036854775807)) == "1y2p0ij32e8e7");
	CHECK(to_string_view(int_to_ary<int64_t, 36>(0x8000000000000001)) == "1y2p0ij32e8e9");
#if defined(__GNUC__)
	static_assert(std::is_integral<__int128_t>::value, "Warning, int128 won't pickup the optimized base 10 conversion path");
	__int128_t num = 10000000000000000000U;
	CHECK(to_string_view(int_to_ary<__int128_t, 10>(num * 100)) == "1000000000000000000000");
	num = 0xFFFFFFFFFFFFFFFF;
	CHECK(to_string_view(int_to_ary<__int128_t, 16>(num * 0x10000 + 0xffff)) == "ffffffffffffffffffff");
#endif
}

TEST_CASE ("Check char array to int conversions", "[i2s][int_conv]") {
	AryConversionTestHelper<uint32_t, 10>("0", 0);
	AryConversionTestHelper<int32_t, 10>("0", 0);
	AryConversionTestHelper<int16_t, 10>("0", 0);
	AryConversionTestHelper<int16_t, 16>("ff", 0xff);
	AryConversionTestHelper<uint8_t, 16>("ff", 0xff);
	AryConversionTestHelper<uint32_t, 36>("rs", 1000);
	AryConversionTestHelper<uint16_t, 8>("20", 16);
	AryConversionTestHelper<int32_t, 10>("1", 1);
	AryConversionTestHelper<int32_t, 10>("10", 10);
	AryConversionTestHelper<int32_t, 10>("100", 100);
	AryConversionTestHelper<int32_t, 10>("999", 999);
	AryConversionTestHelper<int32_t, 10>("1000", 1000);
	AryConversionTestHelper<int32_t, 10>("1001", 1001);
	AryConversionTestHelper<int32_t, 10>("12345", 12345);
	AryConversionTestHelper<int32_t, 10>("123456", 123456);
	AryConversionTestHelper<int32_t, 10>("1234567", 1234567);
	AryConversionTestHelper<int32_t, 10>("12345678", 12345678);
	AryConversionTestHelper<int32_t, 10>("123456789", 123456789);
	AryConversionTestHelper<int32_t, 10>("2147483647", 2147483647);
	AryConversionTestHelper<uint64_t, 16>("ffffffffffffffff", 0xffffffffffffffff);
	AryConversionTestHelper<int64_t, 16>("ffffffffffffffff", 0xffffffffffffffff);
	AryConversionTestHelper<int64_t, 16>("7fffffffffffffff", 0x7fffffffffffffff);
	AryConversionTestHelper<int32_t, 16>("7fffffff", 0x7fffffff);
	AryConversionTestHelper<bool, 10>("1", true);
	AryConversionTestHelper<bool, 10>("0", false);
}
