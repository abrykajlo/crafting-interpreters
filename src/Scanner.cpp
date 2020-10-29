#include "Scanner.h"

#include <map>

#include <Lox.h>

namespace
{
	static std::map<std::string, TokenType> k_keywords = {
		std::pair("and", AND),
		std::pair("class", CLASS),
		std::pair("else", ELSE),
		std::pair("false", FALSE),
		std::pair("for", FOR),
		std::pair("fun", FUN),
		std::pair("if", IF),
		std::pair("nil", NIL),
		std::pair("or", OR),
		std::pair("print", PRINT),
		std::pair("return", RETURN),
		std::pair("super", SUPER),
		std::pair("this", THIS),
		std::pair("true", TRUE),
		std::pair("var", VAR),
		std::pair("while", WHILE),
	};
}

Scanner::Scanner(Lox& lox, std::string source)
	: m_lox(lox)
	, m_source(source)
{
}

const std::vector<Token>& Scanner::ScanTokens()
{
	while (!IsAtEnd())
	{
		m_start = m_current;
		ScanToken();
	}

	m_tokens.emplace_back(EOF_LOX, "", m_line);
	return m_tokens;
}

void Scanner::ScanToken()
{
	char c = Advance();
	switch (c)
	{
	case '(':
		AddToken(LEFT_PAREN);
		break;
	case ')':
		AddToken(RIGHT_PAREN);
		break;
	case '{':
		AddToken(LEFT_BRACE);
		break;
	case '}':
		AddToken(RIGHT_BRACE);
		break;
	case ',':
		AddToken(COMMA);
		break;
	case '.':
		AddToken(DOT);
		break;
	case '-':
		AddToken(MINUS);
		break;
	case '+':
		AddToken(PLUS);
		break;
	case ';':
		AddToken(SEMICOLON);
		break;
	case '*':
		AddToken(STAR);
		break;
	case '!':
		AddToken(Match('=') ? BANG_EQUAL : BANG);
		break;
	case '=':
		AddToken(Match('=') ? EQUAL_EQUAL : EQUAL);
		break;
	case '<':
		AddToken(Match('=') ? LESS_EQUAL : LESS);
		break;
	case '>':
		AddToken(Match('=') ? GREATER_EQUAL : GREATER);
		break;
	case '/':
		if (Match('/'))
		{
			while (Peek() != '\n' && !IsAtEnd()) Advance();
		}
		else
		{
			AddToken(SLASH);
		}
		break;
	case ' ':
	case '\r':
	case '\t':
		break;
	case '\n':
		m_line++;
		break;
	case '"':
		String();
		break;
	default:
		if (IsDigit(c))
		{
			Number();
		}
		else if (IsAlpha(c))
		{
			Identifier();
		}
		else
		{
			m_lox.Error(m_line, "Unexpected character.");
		}
		break;
	}
}

void Scanner::String()
{
	while (Peek() != '"' && !IsAtEnd())
	{
		if (Peek() == '\n') m_line++;
		Advance();
	}

	if (IsAtEnd())
	{
		m_lox.Error(m_line, "Unterminated string.");
		return;
	}

	Advance();

	std::string value = m_source.substr(m_start + 1, m_current - m_start - 2);
	AddToken(STRING, value);
}

void Scanner::Identifier()
{
	while (IsAlphaNumeric(Peek())) Advance();
	std::string text = m_source.substr(m_start, m_current - m_start);
	TokenType type = IDENTIFIER;
	auto it = k_keywords.find(text);
	if (it != std::end(k_keywords))
	{
		type = it->second;
	}
	AddToken(type);
}

char Scanner::Advance()
{
	m_current++;
	return m_source[m_current - 1];
}

void Scanner::AddToken(TokenType type)
{
	int count = m_current - m_start;
	std::string text = m_source.substr(m_start, count);
	m_tokens.emplace_back(type, text, m_line);
}

void Scanner::AddToken(TokenType type, std::string str)
{
	int count = m_current - m_start;
	std::string text = m_source.substr(m_start, count);
	m_tokens.emplace_back(type, text, str, m_line);
}

void Scanner::AddToken(TokenType type, double d)
{
	int count = m_current - m_start;
	std::string text = m_source.substr(m_start, count);
	m_tokens.emplace_back(type, text, d, m_line);
}

bool Scanner::IsAlpha(char c)
{
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool Scanner::IsAlphaNumeric(char c)
{
	return IsAlpha(c) || IsDigit(c);
}

bool Scanner::IsDigit(char c)
{
	return c >= '0' && c <= '9';
}

bool Scanner::IsAtEnd()
{
	return m_current >= m_source.length();
}

bool Scanner::Match(char expected)
{
	if (IsAtEnd()) return false;
	if (m_source[m_current] != expected) return false;

	m_current++;
	return true;
}

void Scanner::Number()
{
	while (IsDigit(Peek())) Advance();

	if (Peek() == '.' && IsDigit(PeekNext()))
	{
		Advance();

		while (IsDigit(Peek())) Advance();
	}

	AddToken(NUMBER, strtod(&m_source[m_start], nullptr));
}

char Scanner::Peek()
{
	if (IsAtEnd()) return '\0';
	return m_source[m_current];
}

char Scanner::PeekNext()
{
	if (m_current + 1 >= m_source.length()) return '\0';
	return m_source[m_current + 1];
}
