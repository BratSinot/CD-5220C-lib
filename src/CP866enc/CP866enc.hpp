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

#include <algorithm>
#include <iterator>
#include <memory>
#include <stdexcept>

class cp866 {
	private:
		std::unique_ptr<char[]> data;
		size_t len = 0;

		std::unique_ptr<char[]> fromcode;

		void init(const char* str);

	public:
		cp866() {};
		cp866(const char* codeset);
		cp866(std::string codeset);
		cp866(std::string str, std::string codeset);
		cp866(const char* str, const char* codeset);

		void setcode(std::string codeset);
		void setcode(const char* codeset);
		size_t length(void);
		char* get(void);
		void replace(std::string str);
		void replace(const char* str);

		char operator[](size_t n);

		class iterator : public std::iterator<std::input_iterator_tag, char*> {
			char* ch_ptr;

			public:
				iterator(char* ch);

				iterator& operator++();
				iterator operator++(int);

				bool operator==(const iterator& rhs);
				bool operator!=(const iterator& rhs);

				char& operator*();
		};

		iterator begin();
		iterator end();
};

#endif
