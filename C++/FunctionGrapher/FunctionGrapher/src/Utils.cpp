#include "Utils.h"

std::vector<char> Utils::SplitWithoutSpaces(std::string value)
{
	std::vector<char> splittedValues;
	for (unsigned int index = 0; index < value.length(); index++)
	{
		if (value[index] == ' ')
			continue;

		splittedValues.push_back(value[index]);
	}
	return splittedValues;
}

std::string Utils::ExtractToken(std::vector<char>& value)
{
	std::string token;

	while (value.size() > 0 && IsNumber(value.at(0)))
	{
		token += value[0];
		value.erase(value.begin());
	}

	// Not a number, so must be an operator or a variable,
	// assign one character and return.
	if (token.length() == 0)
	{
		token += value[0];
		value.erase(value.begin());
	}

	return token;
}