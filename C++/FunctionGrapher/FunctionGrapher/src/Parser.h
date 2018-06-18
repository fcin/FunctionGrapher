#pragma once
#include "Operator.h"
#include "Utils.h"
#include <vector>
#include <regex>

class Parser
{
private:
	const std::vector<Operator> m_Operators = {
		Operator('(', 1),
		Operator('+', 2),
		Operator('-', 2),
		Operator('*', 3),
		Operator('/', 3),
		Operator('^', 4)
	};

	Operator GetOperator(std::string& token);
	bool IsOperand(std::string& token) const;

public:
	Parser();
	std::vector<std::string> Parse(std::string input);
	bool IsOperator(std::string& token) const;
};