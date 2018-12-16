#include <tut/elf.hpp>
#include <boost/process.hpp>
#include <tut/util.hpp>
#include <tut/loaders.hpp>
#include <fmt/format.h>
#include <iostream>

namespace bp = boost::process;
namespace fs = boost::filesystem;

struct program_descriptor
{
    fs::path full_path;
    tut::elf_ptr elf;
};

void program_avrdude(const tut::programmer_args_t& pargs, const program_descriptor& program)
{
    // must run objcopy etc if elf, needs binutils
}

void program_openocd(const tut::programmer_args_t& pargs, const program_descriptor& program)
{
    fs::path openocd_root = "/usr";
	auto openocd_executable = openocd_root / "bin/openocd";

	auto script_search_path = openocd_root / "share/openocd/scripts";

	std::vector<std::string> args;
	args.push_back("-s");
	args.push_back(script_search_path.string());
	args.push_back("-f");
	args.push_back(pargs.args["file"]);
	args.push_back("-c");
	args.push_back(fmt::format("program {} verify reset exit", program.full_path.string()));

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
    program_descriptor desc;

    desc.full_path = fs::canonical(argv[2]);
    desc.elf = tut::load_elf(desc.full_path.string());

	auto board = tut::load_board(argv[1]);
	auto& programmer = board->programmers[0];

	std::map<std::string, void(*)(const tut::programmer_args_t&, const program_descriptor&)>
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