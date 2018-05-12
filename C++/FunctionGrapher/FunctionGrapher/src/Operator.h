#pragma once
#include <string>

struct Operator
{
private:
	std::string m_Sign;
	int m_Precedence;

public:
	inline Operator(std::string sign, int precedence) : m_Sign(sign), m_Precedence(precedence) { }
	const std::string& GetSign() const { return m_Sign; };
};