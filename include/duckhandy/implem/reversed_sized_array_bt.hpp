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

#ifndef idFC25566D624140559C54B39FFFE52F04
#define idFC25566D624140559C54B39FFFE52F04

#include <array>
#include <type_traits>
#include <stdexcept>

namespace dhandy {
	template <typename T, std::size_t S>
	class ReversedSizedArray {
		static_assert(S > 0, "This container requires size to be at least 1");
		static_assert(std::is_trivial<T>::value, "Only use this container with trivial types");
	public:
		using iterator = typename std::array<T, S>::iterator;
		constexpr ReversedSizedArray() = default;
		~ReversedSizedArray() = default;

		constexpr std::size_t size() const { return S - (m_curr + 1); }
		constexpr bool empty() const { return m_curr + 1 == S; }
		constexpr const T operator[] (std::size_t idx) const { if (idx >= size()) throw std::out_of_range("Out of bound array access"); return m_data[idx + m_curr + 1]; }
		constexpr T& operator[] (std::size_t idx) { if (idx >= size()) throw std::out_of_range("Out of bound array access"); return m_data[idx + m_curr + 1]; }
		constexpr void push_front (const T& itm) { if (size() == S) throw std::length_error("ReversedSizedArray is full"); m_data[m_curr--] = itm; }
		constexpr const T* data() const { return m_data.data() + m_curr + 1; }
		constexpr iterator begin() { return m_data.begin() + m_curr + 1; }
		constexpr iterator end() { return m_data.end(); }

	private:
		std::array<T, S> m_data {};
		std::size_t m_curr {S - 1};
	};
} //namespace dhandy

#endif
