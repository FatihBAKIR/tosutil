#include <tut/elf.hpp>
#include <boost/process.hpp>

namespace bp = boost::process;
namespace fs = boost::filesystem;

void program_arm()
{

}

void program_openocd()
{
	std::string openocd_executable = "C:/x-tools/OpenOCD-20181130/bin/openocd.exe";

	
}

int main(int argc, char** argv)
{
	auto elf = tut::load_elf(argv[2]);

	switch (get_machine(elf))
	{
	case tut::elf_machine::ARM:
		break;
	}
}