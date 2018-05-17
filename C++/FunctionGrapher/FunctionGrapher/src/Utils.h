#pragma once
#include <vector>
#include <string>

class Utils
{
private:
	inline static bool IsNumber(char value) { return value >= '0' && value <= '9'; };

public:
	static std::vector<char> SplitWithoutSpaces(std::string value);
	static std::string ExtractToken(std::vector<char>& value);
};
