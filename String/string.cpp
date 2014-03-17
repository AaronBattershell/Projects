// Aaron Battershell 6/3/14
// OOP Assignment 2

#include <string>
#include <cstring>
#include "string.hpp"

String::String() 
	: capacity(1), ptr(new char[1]) { 
	*ptr = '\0';
}

String::String(const char* toCoppy) 
	: capacity(strlen(toCoppy) + 1), ptr(new char[strlen(toCoppy) + 1]) {
	memcpy(ptr, toCoppy, capacity);
}

String::String(const String &toCoppy) 
	: capacity(toCoppy._size()), ptr(new char[toCoppy._size()]) {
	memcpy(ptr, toCoppy.ptr, toCoppy._size());
}

String::~String() {
	delete [] ptr;
}

bool String::empty() const {
	return _size() == 1;
}

int String::_size() const {
	return capacity;
}

int String::size() const {
	return capacity-1;
}

char String::operator [] (const int index) const {
	return ptr[index];	
}

bool String::operator == (const String &rhs) const {
	return !strcmp(ptr, rhs.ptr);
}

bool String::operator != (const String &rhs) const {
	return strcmp(ptr, rhs.ptr);
}

bool String::operator < (const String &rhs) const {
	return (strcmp(ptr, rhs.ptr) < 0); 
}

bool String::operator > (const String &rhs) const {
	return !(*this < rhs) && !(*this == rhs);
}

bool String::operator <= (const String &rhs) const {
	return (*this < rhs || *this == rhs);
}

bool String::operator >= (const String &rhs) const {
	return (*this > rhs || *this == rhs);
}

void String::operator = (const String &rhs) {
	capacity = rhs._size();
	String temp(rhs.ptr);
	std::swap(ptr, temp.ptr);
}

String String::operator + (const String &rhs) {
	char *newString = new char[size() + rhs._size()];
	memcpy(newString, ptr, size());
	memcpy(newString+size(), rhs.ptr, rhs._size());
	return String(newString);
}

void String::operator += (const String &rhs) {
	*this = *this + rhs;
}