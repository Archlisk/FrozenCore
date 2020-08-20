#include <Lang/TokenReader.h>

bool TokenReader::Append(const char symbol) {
    if (Token::GetType(m_str + symbol) == Token::Type::Invalid)
        return false;
    else {
        m_str += symbol;
        return true;
    }
}

Token TokenReader::FetchToken() {
    return Token(m_str, Token::GetType(m_str));
}
