#pragma once
#include <string>
#include <vector>
#include "Utils.h"
#include "Parser.h"
#include "CalculateResult.h"

class Calculator
{
private:
	Parser & m_Parser;

public:
	Calculator(Parser& parser);
	CalculateResult CalculateForX(std::string value, double xCoord);
};
