#include <tut/elf.hpp>
#include <boost/process.hpp>
#include <tut/util.hpp>
#include <tut/loaders.hpp>
#include <fmt/format.h>
#include <iostream>
#include "program.hpp"

namespace bp = boost::process;
namespace fs = boost::filesystem;

void program_avrdude(const tut::programmer_args_t& pargs, const tut::program_descriptor& program)
{
    // must run objcopy etc if elf, needs binutils
}

void program_openocd(const tut::programmer_args_t& pargs, const tut::program_descriptor& program);

int main(int argc, char** argv) try
{
	if (argc < 3)
	{
		std::cerr << "usage: program board file\n";
		return 1;
	}

    tut::program_descriptor desc;

    desc.full_path = fs::canonical(argv[2]);

	auto board = tut::load_board(argv[1]);
	auto& programmer = board->programmers[0];

	std::map<std::string, void(*)(const tut::programmer_args_t&, const tut::program_descriptor&)>
	        programmers;
	programmers.emplace("openocd", &program_openocd);
	programmers.emplace("avrdude", &program_avrdude);

	auto programmer_it = programmers.find(programmer.programmer->alias);

	if (programmer_it == programmers.end())
    {
	    std::cerr << "programmer " << programmer.programmer->alias <<  " not found";
	    return 1;
    }

	programmer_it->second(board->programmers[0], desc);
}
catch (std::exception& e)
{
	std::cerr << e.what() << '\n';
	return 1;
}