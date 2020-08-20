#include <Core/Config.h>

#include <Lang/Lexer.h>
#include <Lang/LexerException.h>

#include <fstream>
#include <iostream>

Config::Config(const String& path) {
	std::cout << "Reading config file '" + path + "'" << std::endl;
	
	std::ifstream ifs(path);
	
	if (!ifs.good() || !ifs.is_open())
		throw RuntimeException("Failed to open config file '" + path + "'");
	
	Lexer lexer(ifs);
	
	try {
	
	while (!lexer.EndOfStream())
		ParseEntry(lexer, root);
	
	}
	catch (LexerException& e) {
		std::cout << "\tLexerException on line " << lexer.GetLine() << ": " << e.what() << std::endl;
	}
	
	ifs.close();
}

void Config::ParseEntry(Lexer& lexer, Value& parent) {
	switch (parent.GetType()) {
		case Value::Type::Object: {
			String key = lexer.Consume(Token::Type::Identifier).data;
			lexer.Consume(Token::Type::Equals);
			
			parent.AddChild(key, ParseValue(lexer));
			} break;
		
		case Value::Type::Array: {
			parent.AddElement(ParseValue(lexer));
			} break;
		
		default:
			throw RuntimeException("Unexpected parent type on line " + std::to_string(lexer.GetLine()));
			break;
	}
}

Config::Value Config::ParseValue(Lexer& lexer) {
	
	Token token = lexer.Consume();
	
	switch(token.type) {
		case Token::Type::LeftBrace: {
				Value val(Value::Type::Object);
				while (lexer.Read().type != Token::Type::RightBrace)
					ParseEntry(lexer, val);
				
				lexer.Consume(Token::Type::RightBrace);
				return val;
			} break;
			
		case Token::Type::LeftBracket: {
				Value val(Value::Type::Array);
				while (lexer.Read().type != Token::Type::RightBracket)
					ParseEntry(lexer, val);
					
				lexer.Consume(Token::Type::RightBracket);
				return val;
			} break;
			
		default: {
			Value val(Value::Type::Value);
			val.SetValue(token.data);
			
			lexer.Consume(Token::Type::Semicolon);
			return val;
			} break;
	}
	
	
}
