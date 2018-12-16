#include <tut/elf.hpp>
#include <boost/process.hpp>
#include <tut/util.hpp>
#include <tut/loaders.hpp>
#include <fmt/format.h>
#include <iostream>

namespace bp = boost::process;
namespace fs = boost::filesystem;

void program_openocd(const tut::programmer_args_t& pargs, const std::string& program)
{
    fs::path openocd_root = "/usr";
	auto openocd_executable = openocd_root / "bin/openocd";

	auto script_search_path = openocd_root / "share/openocd/scripts";

	std::vector<std::string> args;
	args.push_back("-s");
	args.push_back(fmt::format("{}", script_search_path.string()));
	args.push_back("-f");
	args.push_back(fmt::format("{}", pargs.args["file"]));
	args.push_back("-c");
	args.push_back(fmt::format("program {} verify reset exit", program));

	std::cout << "+ " << openocd_executable << " ";
	for (auto& arg : args)
	{
		std::cout << arg << " ";
	}
	std::cout << '\n';

	bp::child(openocd_executable, bp::args(args)).wait();
}

int main(int argc, char** argv)
{
	auto full_path = fs::canonical(argv[2]);
	auto board = tut::load_board(argv[1]);

	program_openocd(board->programmers[0], full_path.string());
}