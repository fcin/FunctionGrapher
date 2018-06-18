#include "Calculator.h"

Calculator::Calculator(Parser& parser) : m_Parser(parser) {}

CalculateResult Calculator::CalculateForX(std::string value, double xCoord)
{
	std::vector<std::string> input = m_Parser.Parse(value);
	// Convert all X variables to xCoord
	for (unsigned int index = 0; index < input.size(); index++)
	{
		if (input[index] == "X" || input[index] == "x")
		{
			input[index] = std::to_string(xCoord);
		}
	}

	unsigned int index = 0;
	while (index < input.size())
	{
		std::string token = input[index];

		if (m_Parser.IsOperator(token))
		{
			double lastOperand = 0;
			double lastOperand2 = 0;
			try
			{
				lastOperand = std::stod(input[index - 2]);
				lastOperand2 = std::stod(input[index - 1]);
			}
			catch (const std::exception& ex)
			{
				std::string message = "Specified expression is invalid. " + std::string(ex.what());
				return { 0, true, message };
			}

			double result = 0;

			if (token == "+")
			{
				result = lastOperand + lastOperand2;
			}
			else if (token == "-")
			{
				result = lastOperand - lastOperand2;
			}
			else if (token == "*")
			{
				result = lastOperand * lastOperand2;
			}
			else if (token == "/")
			{
				// todo: handle
				if (lastOperand2 == 0)
					return { 0, true, "Specified expression is invalid" };
				result = lastOperand / lastOperand2;
			}
			else if (token == "^")
			{
				result = lastOperand;
				for (size_t index = 1; index < lastOperand2; index++)
				{
					result *= lastOperand;
				}
			}

			input[index] = std::to_string(result); // replace op with result
			input.erase(input.begin() + index - 2); // op1
			input.erase(input.begin() + index - 2); // op2
			index = 0;
		}

		index++;
	}

	return { std::stod(input[0]), false, "" };
}