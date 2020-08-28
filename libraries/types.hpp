#pragma once

#include <stdexcept>

using number = long int;
using unumber = unsigned long int;
using floating = double;

struct requirements_not_satisfied : std::exception
{
	requirements_not_satisfied(const char* msg) : _what{ msg } {}

	virtual const char* what() const throw ()
	{
		return _what;
	}

private:
	const char* _what;
};

// replacement of asserion. Easier to test
inline void require(const bool arg, const char* msg = "requirements not satisfied")
{
	if(arg) return;
	try
	{
		throw requirements_not_satisfied{ msg };
	}catch(const requirements_not_satisfied&)
	{
		throw;
	}
}