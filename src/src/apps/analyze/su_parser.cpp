#include <string>
#include "stack_use.hpp"
#include <fstream>
#include <regex>
#include <tut/errors.hpp>

namespace fs = boost::filesystem;

namespace tut
{
	std::vector<tut::su_entry> parse_su_file(const boost::filesystem::path& su_file)
	{
		if (!fs::exists(su_file))
		{
			throw tut::file_not_found(su_file);
		}

		std::ifstream file{ su_file.string() };
		
		std::vector<tut::su_entry> res;
		while (file)
		{
			std::string line;
			line.resize(1024);
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