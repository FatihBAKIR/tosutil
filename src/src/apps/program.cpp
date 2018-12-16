#include <tut/elf.hpp>
#include <boost/process.hpp>
#include <tut/util.hpp>
#include <tut/loaders.hpp>
#include <fmt/format.h>
#include <iostream>

namespace bp = boost::process;
namespace fs = boost::filesystem;

void program_avrdude()
{

}

void program_openocd(const tut::programmer_args_t& pargs, const std::string& program)
{
	std::string openocd_executable = "openocd";

	std::vector<std::string> args;
	args.push_back(fmt::format("-f {}", pargs.args["file"]));
	args.push_back(fmt::format("-c \"program {} verify reset exit\"", program));

	std::cout << openocd_executable << " ";
	for (auto& arg : args)
	{
		std::cout << arg << " ";
	}
	std::cout << '\n';
}

int main(int argc, char** argv)
{
	auto full_path = fs::canonical(argv[2]);
	auto board = tut::load_board(argv[1]);

	program_openocd(board->programmers[0], full_path.string());
}