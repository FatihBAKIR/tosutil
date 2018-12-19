#include <boost/filesystem.hpp>
#include <boost/process.hpp>
#include "program.hpp"
#include <fmt/format.h>

namespace fs = boost::filesystem;
namespace bp = boost::process;

enum class verification_result
{
	ok,
	wrong_machine
};

static [[nodiscard]]
verification_result
verify_program(const tut::program_descriptor& program)
{
	auto e = tut::load_elf(program.full_path);
	// so far, we only support arm on openocd
	if (get_machine(e) != tut::elf_machine::ARM)
	{
		return verification_result::wrong_machine;
	}

	return verification_result::ok;
}

void program_openocd(const tut::programmer_args_t& pargs, const tut::program_descriptor& program)
{
	if (auto res = verify_program(program); res != verification_result::ok)
	{
		throw std::runtime_error("Not a compatible binary! (" + std::to_string(int(res)) + ")");
	}

    fs::path openocd_root = "/usr";
	auto openocd_executable = bp::search_path("openocd", { openocd_root / "bin" });

	if (openocd_executable.empty())
	{
		throw std::runtime_error("Could not find openocd executable");
	}

	auto script_search_path = openocd_root / "share/openocd/scripts";

	std::vector<std::string> args;
	args.push_back("-s");
	args.push_back(script_search_path.string());
	for (auto& script : pargs.args["scripts"])
	{
		args.push_back("-f");
		args.push_back(script);
	}
	args.push_back("-c");
	args.push_back(fmt::format("program {} verify reset exit", program.full_path.string()));

	bp::child(openocd_executable, bp::args(args)).wait();
}