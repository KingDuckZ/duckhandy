/* Copyright 2016, Michele Santullo
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

#ifndef id170B0E6C34D14EBA9B92A35977BDBFB3
#define id170B0E6C34D14EBA9B92A35977BDBFB3

#include "sequence_bt.hpp"
#include <cstddef>
#include <iostream>
#include <stdexcept>

namespace dhandy {
	namespace bt {
		template <std::size_t S, typename Ch=char>
		class string;

		template <std::size_t S, typename Ch>
		std::basic_ostream<Ch>& operator<< ( std::basic_ostream<Ch>& parStream, const string<S, Ch>& parString );

		template <std::size_t S, typename Ch>
		class string {
			friend std::ostream& operator<< <>( std::ostream& parStream, const string<S>& parString );
		public:
			using value_type = Ch;
			constexpr string ( const value_type* parString );

			constexpr std::size_t size ( void ) const { return S - 1; }
			template <std::size_t S2>
			constexpr string<S + S2 - 1, Ch> operator+ ( const string<S2, Ch>& parOther ) const;
			constexpr value_type operator[] ( std::size_t parIndex ) const;

			template <typename... Args>
			constexpr string ( Args... );

			constexpr const value_type (&data_arr() const)[S] { return m_data; }
			constexpr const value_type* data() const { return m_data; }

		private:
			template <std::size_t... I>
			constexpr string ( const index_seq<I...>&, const value_type* parString );

			const value_type m_data[S];
		};

		namespace implem {
			template <std::size_t S, std::size_t S2, std::size_t... I>
			constexpr string<S + S2 - 1> concat ( const index_seq<I...>&, const string<S>& parLeft, const string<S2>& parRight ) {
				return string<S + S2 - 1>(
					(I < S - 1 ? parLeft[I] : (I < S + S2 - 2 ? parRight[I - (S - 1)] : '\0'))...
				);
			}

		} //namespace implem

		template <std::size_t S, typename Ch>
		template <std::size_t... I>
		constexpr string<S, Ch>::string (const index_seq<I...>&, const value_type* parString) :
			m_data{parString[I]...}
		{
		}

		template <std::size_t S, typename Ch>
		inline constexpr string<S, Ch>::string (const value_type* parString) :
			string(index_range<0, S>(), parString)
		{
		}

		template <std::size_t S, typename Ch>
		template <typename... Args>
		inline constexpr string<S, Ch>::string (Args... parArgs) :
			m_data{parArgs...}
		{
		}

		template <std::size_t S, typename Ch>
		template <std::size_t S2>
		constexpr inline string<S + S2 - 1, Ch> string<S, Ch>::operator+ (const string<S2, Ch>& parOther) const {
			return implem::concat(index_range<0, S + S2 - 1>(), string<S>(m_data), parOther);
		}

		template <std::size_t S, typename Ch>
		inline std::ostream& operator<< (std::ostream& parStream, const string<S, Ch>& parString) {
			parStream << parString.m_data;
			return parStream;
		}

		template <std::size_t S, typename Ch>
		constexpr auto string<S, Ch>::operator[] (std::size_t parIndex) const -> value_type {
			return (parIndex < S ? m_data[parIndex] : throw std::out_of_range(""));
		}

		template <std::size_t S, typename Ch>
		constexpr string<S, Ch> make_string (const Ch (&parData)[S]) {
			return string<S>(parData);
		}
	} //namespace bt
} //namespace dhandy

#endif
