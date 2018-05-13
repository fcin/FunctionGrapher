#include "Parser.h"
#include <stdexcept>
#include <stdexcept>

Parser::Parser()
{

}

std::string Parser::Parse(std::string input)
{
	std::vector<char> tokens = Utils::SplitWithoutSpaces(input);
	std::vector<Operator> opstack;
	std::string output;

	while (tokens.size() > 0)
	{
		std::string token = Utils::ExtractToken(tokens);

		if (IsOperand(token))
		{
			output += token;
		}
		else if (token == "(")
		{
			opstack.push_back(GetOperator(token[0]));
		}
		else if (token == ")")
		{
			// Move all operators between () to output.
			while (opstack.size() > 0)
			{
				Operator op = opstack[opstack.size() - 1];
				opstack.pop_back();
				if (op.GetSign() == '(')
					break;

				output.push_back(op.GetSign());
			}
		}
		else if (IsOperator(token[0]))
		{
			Operator op = GetOperator(token[0]);
			Operator currOperator = opstack[opstack.size() - 1];
			// Move all consecutive operators with higher precedence to output.
			while (opstack.size() > 0 && currOperator.GetPrecedence() >= op.GetPrecedence())
			{
				opstack.pop_back();
				output.push_back(currOperator.GetSign());
				currOperator = opstack[opstack.size() - 1];
			}

			opstack.push_back(op);
		}
		else
		{
			throw std::invalid_argument("Unexpected token:" + token);
		}
	}

	while (opstack.size() > 0)
	{
		Operator value = opstack[opstack.size() - 1];
		opstack.pop_back();
		output.push_back(value.GetSign());
	}

	return output;
}

bool Parser::IsOperator(char& token) const
{
	for (unsigned int index = 0; index < m_Operators.size(); index++)
	{
		if (token == m_Operators[index].GetSign())
			return true;
	}

	return false;
}

Operator Parser::GetOperator(char& token)
{
	for (unsigned int index = 0; index < m_Operators.size(); index++)
	{
		if (token == m_Operators[index].GetSign())
		{
			return m_Operators.at(index);
		}
	}

	throw std::invalid_argument("Token does not exist");
}


bool Parser::IsOperand(std::string& token) const
{
	std::regex operands("[0-9A-Za-z]");
	
	return std::regex_match(token, operands);
}