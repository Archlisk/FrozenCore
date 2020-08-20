#pragma once

#include <FC/String.h>

struct Token {
    enum class Type {
        Invalid,
        
        Identifier,
        
        IntegerLiteral,
        FloatLiteral,
        StringLiteral,
        
        Plus,
        Minus,
        Asterisk,
        Slash,
        Equals,
        Less,
        Greater,
		Exclamation,
		PlusPlus,
        EqualsEquals,
        ExclamationEquals,
        
        LeftParen,
        RightParen,
        LeftBrace,
        RightBrace,
        LeftBracket,
        RightBracket,
        Dot,
        Comma,
		Colon,
        Semicolon,
    };
    
    static Type GetType(const String& str);
    
    static bool IsValue(Type type);
    static bool IsOperator(Type type);
    
    static bool IsValidIdentifierStart(const String& str);
    static bool IsValidStringStart(const String& str);
    static bool IsValidIntegerStart(const String& str);
    static bool IsValidFloatStart(const String& str);
    
    Token() : data(""), type(Type::Invalid) {}
    Token(String data, Type type) : data(data), type(type) {}
    
    String data;
    Type type;
};
