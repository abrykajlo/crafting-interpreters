#include <vector>

#include <Token.h>

#pragma once

class Lox;

class Scanner
{
public:
	Scanner(Lox& lox, std::string source);

	const std::vector<Token>& ScanTokens();

private:
	void ScanToken();
	
	void AddToken(TokenType type);
	void AddToken(TokenType type, std::string str);
	void AddToken(TokenType type, double d);
	
	bool IsAlpha(char c);
	bool IsAlphaNumeric(char c);
	bool IsDigit(char c);
	bool IsAtEnd();
	
	bool Match(char expected);
	char Advance();
	char Peek();
	char PeekNext();

	void Number();
	void String();
	void Identifier();

	std::string m_source;
	std::vector<Token> m_tokens;
	Lox& m_lox;

	int m_start = 0;
	int m_current = 0;
	int m_line = 1;
};