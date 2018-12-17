#pragma once

#include <tut/elf.hpp>
#include <boost/filesystem.hpp>
#include <tut/util.hpp>

namespace tut
{
	struct program_descriptor
	{
		boost::filesystem::path full_path;
	};

	struct programmer_base
	{
		virtual void program(const program_descriptor& pd) = 0;
		virtual ~programmer_base() = 0;
	};
}