#pragma once

// STL
#include <stdexcept>
#include <sstream>
#include <iostream>

// Boost
#include <boost/stacktrace/stacktrace.hpp>

using number = long int;
using unumber = unsigned long int;
using floating = float;

struct requirements_not_satisfied : std::exception
{
	requirements_not_satisfied(const char* msg) : _what{ msg } {}

	virtual const char* what() const throw ()
	{
#ifndef NOSTACKTRACE
		std::cout << boost::stacktrace::to_string( boost::stacktrace::stacktrace() ) << std::endl;
#endif
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