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

#ifndef MY_INCL_DUCKTYPES_H
#define MY_INCL_DUCKTYPES_H

#include <climits>
#include <type_traits>

namespace dhandy {
	namespace internal {
		class ERROR_inttype_not_available {
			ERROR_inttype_not_available();
		};
	} // namespace internal

	// Retrieves a signed/unsigned integer type with sizeof( T ) == BYTES
	template<unsigned BYTES, bool SIGNED>
	struct int_t {
		typedef typename std::conditional< sizeof( signed char ) * CHAR_BIT == CHAR_BIT * BYTES,  signed char,
				typename std::conditional< sizeof( signed short ) * CHAR_BIT == CHAR_BIT * BYTES, signed short,
				typename std::conditional< sizeof( signed int ) * CHAR_BIT == CHAR_BIT * BYTES, signed int,
				typename std::conditional< sizeof( signed long ) * CHAR_BIT == CHAR_BIT * BYTES, signed long,
				typename std::conditional< sizeof( signed long long ) * CHAR_BIT == CHAR_BIT * BYTES, signed long long,
				internal::ERROR_inttype_not_available >::type >::type >::type >::type >::type type;
	};

	template<unsigned BYTES>
	struct int_t<BYTES, false> {
		typedef typename std::conditional< sizeof( unsigned char ) * CHAR_BIT == CHAR_BIT * BYTES, unsigned char,
				typename std::conditional< sizeof( unsigned short ) * CHAR_BIT == CHAR_BIT * BYTES, unsigned short,
				typename std::conditional< sizeof( unsigned int ) * CHAR_BIT == CHAR_BIT * BYTES, unsigned int,
				typename std::conditional< sizeof( unsigned long ) * CHAR_BIT == CHAR_BIT * BYTES, unsigned long,
				typename std::conditional< sizeof( unsigned long long ) * CHAR_BIT == CHAR_BIT * BYTES, unsigned long long,
				internal::ERROR_inttype_not_available >::type >::type >::type >::type >::type type;
	};

	// Retrieves the smallest unsigned integer type with sizeof( T ) >= BYTES
	template<unsigned BYTES>
	struct uint_t_min {
		typedef typename std::conditional< sizeof( unsigned char ) * CHAR_BIT >= CHAR_BIT * BYTES, unsigned char,
				typename std::conditional< sizeof( unsigned short ) * CHAR_BIT >= CHAR_BIT * BYTES, unsigned short,
				typename std::conditional< sizeof( unsigned int ) * CHAR_BIT >= CHAR_BIT * BYTES, unsigned int,
				typename std::conditional< sizeof( unsigned long ) * CHAR_BIT >= CHAR_BIT * BYTES, unsigned long,
				typename std::conditional< sizeof( unsigned long long ) * CHAR_BIT >= CHAR_BIT * BYTES, unsigned long long,
				internal::ERROR_inttype_not_available >::type >::type >::type >::type >::type type;
	};
} //namespace dhandy

#endif // MY_INCL_DUCKTYPES_H
