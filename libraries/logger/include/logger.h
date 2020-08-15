#pragma once

// STL
#include <iostream>
#include <functional>
#include <sstream>

// submodule
#include "../../rang/include/rang.hpp"

// Boost
#include <boost/core/demangle.hpp>

class logger
{
public:
	using format_function = std::function<std::ostream &(std::ostream &)>;

	template <typename T>
	inline static logger get_logger(const char * alternative = "unknown")
	{
		const char *name = typeid(T).name();
		boost::core::scoped_demangled_name demangled( name );
		return logger( (demangled.get() ? demangled.get() : alternative) );
	}

	inline static std::string dump_file;

	inline static format_function reset_color_scheme = [](std::ostream &os) -> std::ostream & { return os << rang::bg::reset << rang::fg::reset; };
	inline static format_function debug_color_scheme = [](std::ostream &os) -> std::ostream & { return os << rang::bg::reset << rang::fg::gray; };
	inline static format_function info_color_scheme = [](std::ostream &os) -> std::ostream & { return os << rang::bg::reset << rang::fg::blue; };
	inline static format_function warn_color_scheme = [](std::ostream &os) -> std::ostream & { return os << rang::bg::reset << rang::fg::yellow; };
	inline static format_function erro_color_scheme = [](std::ostream &os) -> std::ostream & { return os << rang::bg::reset << rang::fg::red; };

	inline static format_function debug_format = [](std::ostream &os) -> std::ostream & { logger::info_color_scheme(os); return os << "[DEBUG]"; };
	inline static format_function info_format = [](std::ostream &os) -> std::ostream & { logger::info_color_scheme(os); return os << "[INFO]"; };
	inline static format_function warn_format = [](std::ostream &os) -> std::ostream & { logger::warn_color_scheme(os); return os << "[WARNING]"; };
	inline static format_function erro_format = [](std::ostream &os) -> std::ostream & { logger::erro_color_scheme(os); return os << "[ERROR]"; };

	template <typename T>
	logger &operator<<(const T &obj)
	{
		std::stringstream ss;
		ss << get_preambula(2);
		ss << obj;
		print_out(ss.str(), debug_format);
		return *this;
	}

	void dbg(const std::string &) const;
	void info(const std::string &) const;
	void warn(const std::string &) const;
	void error(const std::string &) const;

private:
	const std::string_view preambula;
	std::string get_preambula(const uint16_t depth) const;
	logger(const std::string &file_name);
	void print_out(const std::string &, const format_function &_format = logger::reset_color_scheme) const;
};

template <typename T>
class Log
{
public:
	logger log = logger::get_logger<T>();
};