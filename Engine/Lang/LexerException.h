#pragma once

#include <FC/String.h>
#include <exception>

class LexerException : std::exception {
public:
    LexerException(String error_str) : m_error_str(error_str) {}

    virtual const char* what() const throw() {
        return m_error_str.c_str();
    }
    
private:
    String m_error_str;
};
