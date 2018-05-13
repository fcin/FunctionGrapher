#pragma once
#include <string>

struct Operator
{
private:
	char m_Sign;
	int m_Precedence;

public:
	inline Operator(char sign, int precedence) : m_Sign(sign), m_Precedence(precedence) { }
	inline const char& GetSign() const { return m_Sign; };
	inline const int GetPrecedence() const { return m_Precedence; };
};