#include "logger.h"

// STL
#include <fstream>

// Boost
#include <boost/stacktrace/stacktrace.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/filesystem/operations.hpp>

logger::logger(const std::string &file_name)
	: preambula{file_name} {}

std::string logger::get_preambula(const uint16_t depth) const
{
	std::stringstream ss;
	ss << "[" << boost::posix_time::to_iso_extended_string(boost::posix_time::microsec_clock::local_time()) << "]"; // time
	ss << "[" << preambula << "]";																					// logger name
	
	const std::vector<boost::stacktrace::frame> frames{boost::stacktrace::stacktrace().as_vector()};

	// std::cout << "#######################" <<std::endl;
	// for(const auto& fr : frames)
	// 	std::cout << "STACK: " << fr.name() << ": " << fr.source_file() << ":" << fr.source_line() << std::endl;
	// std::cout << "#######################" <<std::endl;

	if (depth < frames.size()) // info about log position
	{
		const boost::stacktrace::frame &fr{frames[depth]};
		if(fr.source_line() > 0) ss << "[" << fr.source_file() << ":" << fr.source_line() << "]" << "[" << fr.name() << "]";
	}
	return ss.str() + " ";
}

void logger::print_out(const std::string &msg, const format_function &_format) const
{
	if (not logger::dump_file.empty())
	{
		std::unique_ptr<std::ofstream> file{nullptr};
		if (boost::filesystem::exists(boost::filesystem::path(logger::dump_file)))
			file = std::make_unique<std::ofstream>(logger::dump_file, std::ios::app);
		else
			file = std::make_unique<std::ofstream>(logger::dump_file);

		if (file->good())
		{
			(*file) << msg << std::endl;
		}
		file->close();
	}

	_format(std::cout);
	std::cout << msg << std::endl;
	logger::reset_color_scheme(std::cout);
	std::cout << '\0';
}

void logger::dbg(const std::string & msg) const
{
	print_out( get_preambula(3) + msg, debug_format );
}

void logger::info(const std::string & msg) const
{
	print_out( get_preambula(3) + msg, info_format );
}

void logger::warn(const std::string & msg) const
{
	print_out( get_preambula(3) + msg, warn_format );
}

void logger::error(const std::string & msg) const
{
	print_out( get_preambula(3) + msg, erro_format );
}