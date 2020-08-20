#pragma once

#include <Lang/Token.h>

#include <FC/String.h>

class TokenReader {
public:
    bool Append(const char symbol);
	Token FetchToken();
	
private:
	String m_str;
};

