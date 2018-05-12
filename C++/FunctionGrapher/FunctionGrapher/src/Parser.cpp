#include "Parser.h"
#include "Utils.h"

Parser::Parser()
{

}

std::string Parser::Parse(std::string input)
{
	std::vector<std::string> tokens = Utils::SplitWithoutSpaces(input);
	std::vector<Operator> opstack;
	std::string output;

	while (tokens.size() > 0)
	{
		std::string token = Utils::ExtractToken(&input);
	}

	return "";
}