#include <Lang/Lexer.h>
#include <Lang/CharTypes.h>
#include <Lang/TokenReader.h>
#include <Lang/LexerException.h>

Token Lexer::Read() {
    while (IsIndent(ReadChar()))
        ConsumeChar();
    
    TokenReader reader;
    while (reader.Append(ReadChar()))
        ConsumeChar();
    
    Token token = reader.FetchToken();
    if (token.data.length() == 0)
        throw LexerException("Invalid token");
        
    Rewind(token.data.length());
    
    if (token.type == Token::Type::StringLiteral) {
        token.data.pop_back();
        token.data.erase(token.data.begin());
    }
    
    return token;
}

Token Lexer::Read(Token::Type type) {
    Token token = Read();
    
    if (token.type != type)
        throw LexerException("Unexpected token '" + token.data + "'");
    
    return token;
}

Token Lexer::Consume() {
    while (IsIndent(ReadChar()))
        ConsumeChar();
    
    TokenReader reader;
    while (reader.Append(ReadChar()))
        ConsumeChar();
    
    Token token = reader.FetchToken();
    if (token.data.length() == 0)
        throw LexerException("Invalid token");
    
    if (token.type == Token::Type::StringLiteral) {
        token.data.pop_back();
        token.data.erase(token.data.begin());
    }
    
    return token;
}

Token Lexer::Consume(Token::Type type) {
    Token token = Consume();
    
    if (token.type != type)
        throw LexerException("Unexpected token '" + token.data + "'");
    
    return token;
}

char Lexer::ReadChar() {
    return m_file.peek();
}

char Lexer::ConsumeChar() {
    int next_char = m_file.get();
    
    if (next_char == EOF)
        throw LexerException("Unexpected end of file");
    
    if (next_char == '\n')
        m_line++;
    
    return next_char;
}

bool Lexer::EndOfStream() {
    while (IsIndent(ReadChar()))
        ConsumeChar();
        
    return m_file.eof();
}
