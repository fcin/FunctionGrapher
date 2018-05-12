#include "Utils.h"

std::vector<std::string> Utils::SplitWithoutSpaces(std::string value)
{
	std::vector<std::string> splittedValues;
	for (unsigned int index = 0; index < value.length(); index++)
	{
		if (value[index] == ' ')
			continue;

		splittedValues.push_back(std::string(1, value[index]));
	}
	return splittedValues;
}

std::string Utils::ExtractToken(std::string& value)
{
	std::string token;

	while (value.length() > 0 && IsNumber(value[0]))
	{
		token += value[0];
		value = value.substr(0, 1);
	}

	// Not a number, so must be an operator or a variable,
	// assign one character and return.
	if (token.length() == 0)
	{
		token += value[0];
		value = value.substr(0, 1);
	}

	return token;
}