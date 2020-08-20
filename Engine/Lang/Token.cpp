#include <Lang/Token.h>
#include <Lang/CharTypes.h>

#include <map>

std::map<String, Token::Type> type_str {
    { "", Token::Type::Identifier },
    
    { "", Token::Type::IntegerLiteral },
    { "", Token::Type::FloatLiteral },
    { "", Token::Type::StringLiteral },
    
    { "+", Token::Type::Plus },
    { "++", Token::Type::PlusPlus },
    { "-", Token::Type::Minus },
    { "*", Token::Type::Asterisk },
    { "/", Token::Type::Slash },
    { "=", Token::Type::Equals },
	{ "<", Token::Type::Less },
    { ">", Token::Type::Greater },
    { "!", Token::Type::Exclamation},
    { "==", Token::Type::EqualsEquals },
	{ "!=", Token::Type::ExclamationEquals },
    
    { "(", Token::Type::LeftParen },
    { ")", Token::Type::RightParen },
    { "{", Token::Type::LeftBrace },
    { "}", Token::Type::RightBrace },
    { "[", Token::Type::LeftBracket },
    { "]", Token::Type::RightBracket },
    { ".", Token::Type::Dot },
    { ",", Token::Type::Comma },
    { ":", Token::Type::Colon },
    { ";", Token::Type::Semicolon },
};

bool Token::IsValue(Token::Type type) {
    return (type == Token::Type::Identifier ||
            type == Token::Type::FloatLiteral ||
            type == Token::Type::IntegerLiteral ||
            type == Token::Type::StringLiteral);
}

bool Token::IsOperator(Token::Type type) {
    return (type == Token::Type::Plus ||
            type == Token::Type::Minus ||
            type == Token::Type::Asterisk ||
            type == Token::Type::Slash ||
            type == Token::Type::Equals ||
            type == Token::Type::Less ||
            type == Token::Type::Greater ||
            type == Token::Type::EqualsEquals);
}

Token::Type Token::GetType(const String& str) {
    auto it = type_str.find(str);

    if (it != type_str.end())
        return it->second;
        
    if (IsValidIdentifierStart(str))
        return Token::Type::Identifier;
    if (IsValidIntegerStart(str))
        return Token::Type::IntegerLiteral;
    if (IsValidFloatStart(str))
        return Token::Type::FloatLiteral;
    if (IsValidStringStart(str))
        return Token::Type::StringLiteral;
    
    return Token::Type::Invalid;
}

bool Token::IsValidIdentifierStart(const String& str) {
    for (size_t i = 0; i < str.length(); i++) {
        if (IsNumber(str[i])) {
            if (i == 0)
                return false;
        }
        else if (!IsIdentifier(str[i]))
            return false;
    }
            
    return true;
}

bool Token::IsValidStringStart(const String& str) {
    if (str[0] != '"')
        return false;
    
    for (size_t i = 1; i < str.size(); i++)
        if (str[i] == '"' && (i + 1 < str.size()))
            return false;
    
    return true;
}

bool Token::IsValidIntegerStart(const String& str) {
    for (size_t c = 0; c < str.length(); c++) {
        if (!IsNumber(str[c])) {
			if (!(c == 1 && (str[c] == 'x' || str[c] == 'b')))
				return false;
		}
	}
            
    return true;
}

bool Token::IsValidFloatStart(const String& str) {
    bool found_decimal_point = false;

    for (size_t i = 0; i < str.size(); i++) {
        if (str[i] == '.') {
            if (found_decimal_point)
                return false;
            else
                found_decimal_point = true;
        }
        else if (!IsNumber(str[i]))
            return false;
    }
    
    return true;
}

