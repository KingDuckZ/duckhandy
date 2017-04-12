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
#include "duckhandy/lexical_cast.hpp"
#include <cstdint>
#include <string>
#include <cstddef>
#include <climits>

template <std::size_t C, std::size_t E, bool B=static_cast<bool>(C==E)>
struct CountDigitsDebugger { static constexpr const bool value = true; };
template <std::size_t C, std::size_t E>
struct CountDigitsDebugger<C, E, false> {};

TEST_CASE ("Check string to int conversions", "[s2i][lexical_cast]") {
	using dhandy::lexical_cast;
	using dhandy::tags::dec;
	using dhandy::tags::hex;
	using dhandy::tags::bin;

	static_assert(CountDigitsDebugger<bin<int32_t>::count_digits_bt(0), 1>::value, "Wrong digits count");
	static_assert(CountDigitsDebugger<bin<int32_t>::count_digits_bt(1), 1>::value, "Wrong digits count");
	static_assert(CountDigitsDebugger<bin<int32_t>::count_digits_bt(2), 2>::value, "Wrong digits count");
	static_assert(CountDigitsDebugger<bin<int32_t>::count_digits_bt(3), 2>::value, "Wrong digits count");
	static_assert(CountDigitsDebugger<bin<int32_t>::count_digits_bt(4), 3>::value, "Wrong digits count");
	static_assert(CountDigitsDebugger<bin<int32_t>::count_digits_bt(5), 3>::value, "Wrong digits count");
	static_assert(CountDigitsDebugger<bin<int32_t>::count_digits_bt(6), 3>::value, "Wrong digits count");
	static_assert(CountDigitsDebugger<bin<int32_t>::count_digits_bt(7), 3>::value, "Wrong digits count");
	static_assert(CountDigitsDebugger<bin<int32_t>::count_digits_bt(8), 4>::value, "Wrong digits count");
	static_assert(CountDigitsDebugger<bin<int32_t>::count_digits_bt(9), 4>::value, "Wrong digits count");
	static_assert(CountDigitsDebugger<bin<int32_t>::count_digits_bt(255), 8>::value, "Wrong digits count");
	static_assert(CountDigitsDebugger<bin<int32_t>::count_digits_bt(256), 9>::value, "Wrong digits count");
	static_assert(CountDigitsDebugger<bin<uint32_t>::count_digits_bt(255), 8>::value, "Wrong digits count");
	static_assert(CountDigitsDebugger<bin<uint32_t>::count_digits_bt(256), 9>::value, "Wrong digits count");
	static_assert(CountDigitsDebugger<bin<uint16_t>::count_digits_bt(255), 8>::value, "Wrong digits count");
	static_assert(CountDigitsDebugger<bin<uint16_t>::count_digits_bt(256), 9>::value, "Wrong digits count");
	static_assert(CountDigitsDebugger<bin<uint8_t>::count_digits_bt(255), 8>::value, "Wrong digits count");
	static_assert(CountDigitsDebugger<bin<int64_t>::count_digits_bt(255), 8>::value, "Wrong digits count");
	static_assert(CountDigitsDebugger<dec<int64_t>::count_digits_bt(-1), 2>::value, "Wrong digits count");
	static_assert(CountDigitsDebugger<dec<int64_t>::count_digits_bt(-2), 2>::value, "Wrong digits count");
	static_assert(CountDigitsDebugger<dec<int64_t>::count_digits_bt(-10), 3>::value, "Wrong digits count");
	static_assert(CountDigitsDebugger<dec<int64_t>::count_digits_bt(-99), 3>::value, "Wrong digits count");
	static_assert(static_cast<std::size_t>(sprout::log10(sprout::abs(-10000000.0))) == 7, "Wrong log10");
	static_assert(CountDigitsDebugger<dec<int64_t>::count_digits_bt(-10000000), 9>::value, "Wrong digits count");
	static_assert(CountDigitsDebugger<dec<int64_t>::count_digits_bt(-123456789), 10>::value, "Wrong digits count");
	static_assert(CountDigitsDebugger<dec<int32_t>::count_digits_bt(INT_MAX), 11>::value, "Wrong digits count");
	static_assert(CountDigitsDebugger<dec<int32_t>::count_digits_bt(INT_MIN), 11>::value, "Wrong digits count");

	CHECK(lexical_cast<uint16_t>(std::string("0")) == 0);
	CHECK(lexical_cast<uint16_t>(std::string("1")) == 1);
	CHECK(lexical_cast<uint16_t>(std::string("9")) == 9);
	CHECK(lexical_cast<uint16_t>(std::string("10")) == 10);
	CHECK(lexical_cast<uint16_t>(std::string("11")) == 11);
	CHECK(lexical_cast<uint16_t>(std::string("99")) == 99);
	CHECK(lexical_cast<uint16_t>(std::string("512")) == 512);
	CHECK(lexical_cast<uint16_t>(std::string("513")) == 513);
	CHECK(lexical_cast<uint16_t>(std::string("15000")) == 15000);

	CHECK(lexical_cast<int32_t>(std::string("-1")) == -1);
	CHECK(lexical_cast<int32_t>(std::string("-2")) == -2);
	CHECK(lexical_cast<int32_t>(std::string("-10")) == -10);
	CHECK(lexical_cast<int32_t>(std::string("-100000")) == -100000);
}

TEST_CASE ("Check int to string conversions", "[i2s][lexical_cast]") {
}
