#pragma once

#include <string>

inline bool IsIndent(char symbol) {
    return (symbol == '\n' || symbol == '\t' || symbol == ' ');
}

inline bool IsNumber(char symbol) {
    return isdigit(symbol);
}

inline bool IsIdentifier(char symbol) {
    return (isalpha(symbol) || symbol == '_');
}
