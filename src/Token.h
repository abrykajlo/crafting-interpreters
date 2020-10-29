#include <ostream>
#include <optional>
#include <string>
#include <variant>

#include <TokenType.h>

#pragma once

class Token
{
public:
	Token(TokenType type, std::string lexeme, int line);
	Token(TokenType type, std::string lexeme, double d, int line);
	Token(TokenType type, std::string lexeme, std::string str, int line);

	friend std::ostream& operator<<(std::ostream& os, const Token& token);

private:
	TokenType m_type;
	std::string m_lexeme;
	std::optional<std::variant<double, std::string>> m_literal;
	int m_line;
};