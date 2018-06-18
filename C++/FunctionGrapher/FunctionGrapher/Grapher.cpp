#include <string>
#include "src\Parser.h"
#include "src\Calculator.h"

extern "C" __declspec(dllexport) double _cdecl CalculateAt(char* expression, double xCoord)
{
	//std::string input = "(8954.523 + 214) * 7547";
	std::string input = std::string(expression);
	Parser parser;
	Calculator calculator(parser);
	CalculateResult result = calculator.CalculateForX(input, xCoord);
	return result.Value;
}