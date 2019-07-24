// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

/*
	Copyright (C) 2019 DolphinCommode

	This is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	CP866enc is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CP866_HPP_
#define CP866_HPP_

extern "C" {
	#include <iconv.h>
}

#include <cstring>

#include <iterator>
#include <memory>
#include <stdexcept>

class cp866 {
	private:
		char* data;
		size_t len;

	public:
		cp866(std::string str);
		cp866(const char* str);
		~cp866();

		size_t length(void) { return len; };
		char* get(void) { return data; };

		class iterator : public std::iterator<std::input_iterator_tag, char*> {
			char* ch_ptr;

			public:
				iterator(char* ch) : ch_ptr(ch) {}
				iterator& operator++() {
					++ch_ptr;
					return *this;
				}
				iterator operator++(int) {
					iterator tmp(*this);
					operator++();
					return tmp;
				}
				bool operator==(const iterator& rhs) {
					return ch_ptr == rhs.ch_ptr;
				}
				bool operator!=(const iterator& rhs) {
					return ch_ptr != rhs.ch_ptr;
				}
				char& operator*() {
					return *ch_ptr;
				}
		};

		iterator begin() {
			return iterator(data);
		}
		iterator end() {
			return iterator(data + len);
		}
};

#endif
