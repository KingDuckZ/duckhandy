/* Copyright 2017 Michele Santullo
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

#ifndef idB123739E9F8846899541DB26BEA86386
#define idB123739E9F8846899541DB26BEA86386

#include "lexical_cast.hpp"

namespace dhandy {
	namespace customize {
		template<typename C, std::size_t S>
		struct array_to_t<C, S, MaxSizedArray<C, S>> {
			static MaxSizedArray<C, S> make (MaxSizedArray<C, S>&& parIn) {
				return parIn;
			}
		};
	} //namespace customize

	template <typename C, template <typename> class Tag=tags::dec, typename F=void>
	inline auto int_to_string_ary (const F& parFrom) -> MaxSizedArray<C, Tag<F>::count_digits_bt(sprout::numeric_limits<F>::max())> {
		return dhandy::lexical_cast<MaxSizedArray<C, Tag<F>::count_digits_bt(sprout::numeric_limits<F>::max())>, Tag, F>(parFrom);
	}
} //namespace dhandy

#endif
