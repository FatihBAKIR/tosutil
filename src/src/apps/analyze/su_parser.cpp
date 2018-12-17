#include <string>
#include "stack_use.hpp"
#include <fstream>
#include <regex>

namespace fs = std::filesystem;

namespace tut
{
	std::vector<tut::su_entry> parse_su_file(const std::filesystem::path& su_file)
	{
		if (!fs::exists(su_file))
		{
			throw std::runtime_error("file not found: " + su_file.string());
		}
		std::ifstream file{ su_file };
		
		std::vector<tut::su_entry> res;
		while (file)
		{
			std::string line;
			line.resize(512);
			file.getline(line.data(), line.size(), '\n');

			std::regex pattern{"(.+):([0-9]+):([0-9]+):(.*)\t([0-9]+)\t(.*)"};
			std::smatch matches;
			auto regex_res = std::regex_search(line, matches, pattern);
			if (!regex_res)
			{
				continue;
			}

			su_entry entry;
			entry.file_name = matches[1];
			entry.row = std::stoi(matches[2]);
			entry.col = std::stoi(matches[3]);
			entry.function = matches[4];
			entry.stack_use = std::stoi(matches[5]);
			entry.type = matches[6];

			res.push_back(entry);
		}

		return res;
	}
}