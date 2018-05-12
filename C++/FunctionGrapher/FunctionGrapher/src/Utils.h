#pragma once
#include <vector>
#include <string>

class Utils
{
private:
	inline static bool IsNumber(char value) { return !((int)value < (int)'0' || (int)value >(int)'9'); };

public:
	static std::vector<std::string> SplitWithoutSpaces(std::string value);
	static std::string ExtractToken(std::string& value);
};