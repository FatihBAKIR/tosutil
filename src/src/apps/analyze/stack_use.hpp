#pragma once

#include <string>
#include <boost/filesystem.hpp>
#include <vector>

namespace tut
{
	struct su_entry
	{
		std::string file_name;
		int row, col;
		std::string function;
		int stack_use;
		std::string type;
	};

	std::vector<su_entry> parse_su_file(const boost::filesystem::path& su_file);
}