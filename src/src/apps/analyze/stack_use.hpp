#pragma once

#include <string>
#include <filesystem>
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

	std::vector<su_entry> parse_su_file(const std::filesystem::path& su_file);
}