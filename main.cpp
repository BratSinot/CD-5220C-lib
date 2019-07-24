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

#include <cstdio>
#include <string>
#include <CP866enc.hpp>

using namespace std;

int main(void) {
	cp866 test(string("АБВГД"));

	for ( auto ch : test ) {
		printf("0x%X ", (uint8_t)ch);
	}
	putchar('\n');
	for ( size_t i = 0; i < test.length(); i++ ) {
		printf("0x%X ", (uint8_t)test[i]);
	}
	putchar('\n');
	putchar('\n');

	test.replace("ЕЖЗИЙ");

	for ( auto ch : test ) {
		printf("0x%X ", (uint8_t)ch);
	}
	putchar('\n');
	for ( size_t i = 0; i < test.length(); i++ ) {
		printf("0x%X ", (uint8_t)test[i]);
	}

	return 0;
}
