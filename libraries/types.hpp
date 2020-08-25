#pragma once

#include <stdexcept>

using number = long int;
using unumber = unsigned long int;
using floating = double;

struct requirements_not_satisfied : std::exception
{
	virtual const char* what() const throw ()
	{
		return "requirements not specified";
	}
};

inline void require(const bool arg)
{
	if(not arg) return;
	try
	{
		throw requirements_not_satisfied{};
	}
}