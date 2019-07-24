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

#include "CP866enc.hpp"

cp866::cp866(const char* str) {
	iconv_t conv = iconv_open("CP866", "UTF-8");

	if ( conv == (iconv_t)(-1) ) {
		switch ( errno ) {
			case EINVAL:
				throw std::runtime_error("The conversion from UTF-8 to CP866 is not supported by the implementation.");
				break;
			default:
				throw std::runtime_error("Unknown iconv_open() error.");
		}
	}

	size_t inbytesleft = strlen(str);
	size_t outbytesleft = inbytesleft;

	std::shared_ptr<char[]> buff(new char[inbytesleft]);

	const char* inbuf = str;
	char* outbuf = buff.get();

	size_t err = iconv(conv, (char**)&inbuf, &inbytesleft, &outbuf, &outbytesleft);

	if ( err == (size_t)(-1) ) {
		switch ( errno ) {
			case E2BIG:
				throw std::runtime_error("There is not sufficient room at out buffer.");
				break;
			case EILSEQ:
				throw std::runtime_error("An invalid multibyte sequence has been encountered in the input.");
				break;
			case EINVAL:
				throw std::runtime_error("An incomplete multibyte sequence has been encountered in the input.");
				break;
			default:
				throw std::runtime_error("Unknown iconv() error.");
		}
	}
	iconv_close(conv);

	len = strlen(buff.get());

	data = new char[len];
	if ( memcpy(data, buff.get(), len) != data ) {
		throw std::runtime_error("memcpy error.");
	}
}

cp866::cp866(std::string str) : cp866(str.c_str()) {};

cp866::~cp866() {
	delete[] data;
}
