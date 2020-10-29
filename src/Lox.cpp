#include "Lox.h"

#include <Scanner.h>

Lox::Lox()
{
}

Lox::~Lox()
{
}

void Lox::RunFile(const char* path)
{
	std::ifstream file(path);
	Run(std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()));
	if (m_hadError) exit(65);
}

void Lox::RunPrompt()
{
	for (;;)
	{
		std::cout << "> ";
		char buf[256];
		buf[0] = '\0';
		std::cin.getline(buf, 256, '\n');
		if (strlen(buf) == 0) break;
		Run(buf);
		m_hadError = false;
	}
}

void Lox::Error(int line, std::string message)
{
	Report(line, "", message);
}

void Lox::Run(std::string source)
{
	Scanner scanner(*this, source);
	std::vector<Token> tokens = scanner.ScanTokens();

	for (const auto& token : tokens)
	{
		std::cout << token << std::endl;
	}
}

void Lox::Report(int line, std::string where, std::string message)
{
	printf("[line %d] Error %s: %s\n", line, where.c_str(), message.c_str());
	m_hadError = true;
}
