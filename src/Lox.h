#include <fstream>
#include <iostream>
#include <vector>

#pragma once

class Lox
{
public:
	Lox();
	~Lox();

	void RunFile(const char* path);
	void RunPrompt();
	void Error(int line, std::string message);

private:
	void Run(std::string source);
	void Report(int line, std::string where, std::string message);

	bool m_hadError = false;
};