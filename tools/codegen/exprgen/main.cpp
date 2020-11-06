#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <map>

std::string getBaseName(const std::string& fileName);
void defineAst(const std::string& outputFile, const std::string& baseName, std::istream& defFile);

int main(int argc, char** argv)
{
	std::map<std::string, std::istream*> defFiles;
	std::string outputFile;

	if (argc > 1)
	{
		int currentArg = 1;
		while (currentArg < argc)
		{
			std::string flag = argv[currentArg++];
			std::string arg = argv[currentArg++];
			if (flag == "--def")
			{
				std::string baseName = getBaseName(arg);
				std::ifstream* defFile = new std::ifstream();
				defFile->open(arg, std::ios::in);
				defFiles[baseName] = defFile;
			}
			else if (flag == "--out")
			{
				outputFile = arg;
			}
			else
			{
				std::cerr << "Unknown argument\n";
				return -1;
			}
		}

		if (outputFile.empty())
		{
			std::cerr << "Output directory not specified\n";
			return -1;
		}
		else if (defFiles.empty())
		{
			defFiles["Expr"] = new std::istringstream(
				"Binary   : Expr left, Token operator, Expr right\n"
				"Grouping : Expr expression\n"
				"Literal  : Object value\n"
				"Unary    : Token operator, Expr right"
			);
		}

		for (auto& def : defFiles)
		{
			defineAst(outputFile, def.first, *def.second);
			delete def.second;
			def.second = nullptr;
		}
	}
	else
	{
		std::cerr << "Not enough arguments\n";
		return -1;
	}

	return 0;
}

bool isAlpha(char c);
std::string getBaseName(const std::string& fileName)
{
	int start = 0;
	int current = 0;

	std::string nameStr;

	while (current < fileName.length())
	{
		while (!isAlpha(fileName[start]))
		{
			if (isAlpha(fileName[++start]))
			{
				break;
			}
		}	
		current = start;
		while (isAlpha(fileName[current]))
		{
			if (++current == fileName.length())
			{
				return nameStr;
			}
			else if (!isAlpha(fileName[current]))
			{
				break;
			}
		}
		int count = current - start;
		nameStr = fileName.substr(start, count);
		start = current;
	}

	return nameStr;
}

void defineAst(const std::string& outputFile, const std::string& baseName, std::istream& defFile)
{
	std::fstream out;
	out.open(outputFile, std::ios::out | std::ios::trunc);

	out << "#include <memory>\n\n";
	out << "#include <variant>\n\n";
	
	out << "#include <Token.h>\n\n";
	
	out << "#pragma once\n\n";

	out << "struct " << baseName << "{};\n\n";

	out << "using ExprPtr = std::unique_ptr<Expr>;\n";
	out << "using Object = std::variant<nullptr_t, bool>;\n\n";

	char buf[256];
	char delims[] = ":, ";
	char *expr, *type, *member;
	while (!defFile.eof())
	{
		defFile.getline(buf, 256);
		expr = strtok(buf, delims);
		out << "struct " << expr << baseName << " : public " << baseName << "\n{\n";
		type = strtok(nullptr, delims);
		while (type != nullptr)
		{
			member = strtok(nullptr, delims);
			if (strcmp(type, "Expr") == 0)
			{
				out << "    ExprPtr m_";
			}
			else
			{
				out << "    " << type << " m_";
			}
			out << member << ";\n";
			// for next loop
			type = strtok(nullptr, delims);
		}
		out << "};\n\n";
	}
	out.flush();
}

bool isAlpha(char c)
{
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}
