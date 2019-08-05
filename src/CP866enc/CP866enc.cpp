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

void cp866::init(const char* str) {
	iconv_t conv = iconv_open("CP866", fromcode.get());

	if ( conv == (iconv_t)(-1) ) {
		switch ( errno ) {
			case EINVAL:
				throw std::runtime_error(std::string("The conversion from ") + std::string(fromcode.get()) + std::string(" to CP866 is not supported by the implementation."));
				break;
			default:
				throw std::runtime_error("Unknown iconv_open() error.");
		}
	}

	// libiconv change len arguments, so copy them
	size_t inbytesleft = strlen(str);
	size_t outbytesleft = inbytesleft;

	std::shared_ptr<char[]> buff(new char[inbytesleft]);

	// libiconv change pointer arguments as well, so copy them.
	const char* inbuf = str;
	char* outbuf = buff.get();

	size_t err = iconv(conv, (char**)&inbuf, &inbytesleft, &outbuf, &outbytesleft);

	if ( err == (size_t)(-1) ) {
		switch ( errno ) {
			case E2BIG:
				throw std::runtime_error("There is not sufficient room at out buffer.");
			case EILSEQ:
				throw std::runtime_error("An invalid multibyte sequence has been encountered in the input.");
			case EINVAL:
				throw std::runtime_error("An incomplete multibyte sequence has been encountered in the input.");
			default:
				throw std::runtime_error("Unknown iconv() error.");
		}
	}

	len = strlen(buff.get());

	data = std::make_unique<char[]>(len);
	std::copy(buff.get(), buff.get() + len, data.get());

	iconv_close(conv);
}

cp866::cp866(std::string codeset) : cp866(codeset.c_str()) {};

cp866::cp866(const char* codeset) {
	setcode(codeset);
}

cp866::cp866(std::string str, std::string codeset) : cp866(str.c_str(), codeset.c_str()) {};

cp866::cp866(const char* str, const char* codeset) : cp866(codeset) {
	init(str);
}

void cp866::setcode(std::string codeset) {
	setcode(codeset.c_str());
}
void cp866::setcode(const char* codeset) {
	size_t code_len = strlen(codeset);

	fromcode = std::make_unique<char[]>(code_len);
	std::copy(codeset, codeset + code_len, fromcode.get());
}

size_t cp866::length(void) {
	return len;
}

char* cp866::get(void) {
	return data.get();
}

void cp866::replace(std::string str) {
	replace(str.c_str());
}

void cp866::replace(const char* str) {
	if ( fromcode == nullptr ) {
		throw std::runtime_error("Calling replace() without calling constructor first.");
	}

	if ( data != nullptr ) {
		data.reset();
		len = 0;
	}

	init(str);
}

char cp866::operator[](size_t n) {
	if ( n >= len ) {
		throw std::out_of_range("Out of Range.");
	}

	return data[n];
}

cp866::iterator::iterator(char* ch) : ch_ptr(ch) {};

cp866::iterator& cp866::iterator::operator++() {
	++ch_ptr;

	return *this;
}

cp866::iterator cp866::iterator::operator++(int) {
	iterator tmp(*this);
	operator++();

	return tmp;
}

bool cp866::iterator::operator==(const cp866::iterator& rhs) {
	return ch_ptr == rhs.ch_ptr;
}

bool cp866::iterator::operator!=(const cp866::iterator& rhs) {
	return ch_ptr != rhs.ch_ptr;
}

char& cp866::iterator::operator*() {
	return *ch_ptr;
}

cp866::iterator cp866::begin() {
	return iterator(data.get());
}

cp866::iterator cp866::end() {
	return iterator(data.get() + len);
}
