#include "Token.h"

Token::Token(TokenType type, std::string lexeme, int line)
	: m_type(type), m_lexeme(lexeme), m_line(line)
{
}

Token::Token(TokenType type, std::string lexeme, double d, int line)
	: m_type(type), m_lexeme(lexeme), m_line(line), m_literal(d)
{
}

Token::Token(TokenType type, std::string lexeme, std::string str, int line)
	: m_type(type), m_lexeme(lexeme), m_line(line), m_literal(str)
{
}

std::ostream& operator<<(std::ostream& os, const Token& token)
{
	os << k_tokenTypeStrings[token.m_type] << " " << token.m_lexeme;
	if (token.m_literal.has_value())
	{
		os << " ";
		if (std::holds_alternative<std::string>(*token.m_literal))
		{
			os << std::get<std::string>(*token.m_literal);
		}
		else if (std::holds_alternative<double>(*token.m_literal))
		{
			os << std::get<double>(*token.m_literal);
		}
	}
	return os;
}
