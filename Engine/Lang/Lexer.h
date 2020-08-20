#pragma once

#include <Lang/Token.h>

#include <fstream>

class Lexer {
public:
    Lexer(std::ifstream& file) : m_file(file) {}
	
	Token Read();
	Token Read(Token::Type type);
	Token Consume();
	Token Consume(Token::Type type);
	
	bool EndOfStream();
	
	char ReadChar();
    char ConsumeChar();
    
    inline void Rewind(int bytes) { m_file.seekg(-bytes, std::ios::cur); }
	inline void Reset() { m_file.seekg(0, std::ios::beg); m_line = 1; }
	
	inline u32 GetLine() { return m_line; }
	
	inline size_t GetPosition() { return m_file.tellg(); }
	inline void SetPosition(size_t position) { m_file.seekg(position, std::ios::beg); }
	
private:
	std::ifstream& m_file;
	u32 m_line = 1;
};

