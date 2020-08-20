#pragma once

#include <FC/String.h>

#include <cstring>
#include <fstream>

inline String ReadFile(const String& path) {
	std::ifstream file(path);
	
	if (!file.is_open() || !file.good())
		throw RuntimeException("Failed to open '" + path + "'");
	
	String data;
	file.seekg(0, std::ios::end);
	data.reserve(file.tellg());
	file.seekg(0, std::ios::beg);
	data.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	
	return data;
}

inline bool StrEndsWith(const String& str, const String& end) {
	if (str.size() < end.size())
		return false;
		
	if (strcmp(&str.c_str()[str.size() - end.size()], end.c_str()) == 0)
		return true;
	else
		return false;
}
