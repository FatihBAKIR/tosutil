#pragma once

#include <boost/filesystem>

namespace tut
{
	boost::filesystem::path find_file(
		const std::string& name, 
		const std::vector<boost::filesystem::path>& in,
		const std::vector<std::string> suffixes,
		const std::vector<std::string> prefixes);
}