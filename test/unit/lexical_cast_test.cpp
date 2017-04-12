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

TEST_CASE ("Check string to int conversions", "[s2i][lexical_cast]") {
	using dhandy::lexical_cast;

	CHECK(lexical_cast<uint16_t>(std::string("0")) == 0);
	CHECK(lexical_cast<uint16_t>(std::string("1")) == 1);
	CHECK(lexical_cast<uint16_t>(std::string("9")) == 9);
	CHECK(lexical_cast<uint16_t>(std::string("10")) == 10);
	CHECK(lexical_cast<uint16_t>(std::string("11")) == 11);
	CHECK(lexical_cast<uint16_t>(std::string("99")) == 99);
	CHECK(lexical_cast<uint16_t>(std::string("512")) == 512);
	CHECK(lexical_cast<uint16_t>(std::string("513")) == 513);
	CHECK(lexical_cast<uint16_t>(std::string("15000")) == 15000);

	CHECK(lexical_cast<uint32_t>(std::string("-1")) == -1);
	CHECK(lexical_cast<uint32_t>(std::string("-2")) == -2);
	CHECK(lexical_cast<uint32_t>(std::string("-10")) == -10);
	CHECK(lexical_cast<uint32_t>(std::string("-100000")) == -100000);
}

TEST_CASE ("Check int to string conversions", "[i2s][lexical_cast]") {
}
