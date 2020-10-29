#include <iostream>

#include <Lox.h>

int main(int argc, char** argv)
{
	Lox lox;

	if (argc > 2)
	{
		std::cout << "Usage: jlox [script]" << std::endl;
		exit(64);
	}
	else if (argc == 2)
	{
		lox.RunFile(argv[1]);
	}
	else
	{
		lox.RunPrompt();
	}
}