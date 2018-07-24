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

#ifndef idC1B85F801982440AB8C66070635BEE17
#define idC1B85F801982440AB8C66070635BEE17

#include "ducktypes.hpp"

namespace dhandy {
	// Machine independent definition of sized integer types
	typedef int_t<1, true>::type i8;
	typedef int_t<2, true>::type i16;
	typedef int_t<4, true>::type i32;
	typedef int_t<8, true>::type i64;
	typedef int_t<1, false>::type u8;
	typedef int_t<2, false>::type u16;
	typedef int_t<4, false>::type u32;
	typedef int_t<8, false>::type u64;
} //namespace dhandy

#endif
