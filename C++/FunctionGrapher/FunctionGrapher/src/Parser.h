#pragma once
#include "Operator.h"
#include <vector>

class Parser
{
private:
	Operator m_Operators[5] = { 
		Operator("(", 1), 
		Operator("+", 2),
		Operator("-", 2),
		Operator("*", 3),
		Operator("/", 3) 
	};

public:
	Parser();
	std::string Parse(std::string input);
};