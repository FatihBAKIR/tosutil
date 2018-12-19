//
// Created by fatih on 12/15/18.
//

#include <string>
#include <tut/loaders.hpp>
#include <tut/elf.hpp>
#include <iostream>
#include <map>
#include <fmt/format.h>
#include "stack_use.hpp"

namespace fs = boost::filesystem;

void write_info(std::ostream& os, fs::path program)
{
	auto e = tut::load_elf(program);
    os << to_string(get_machine(*e));
}

void stack_use(std::ostream& os, fs::path su_file)
{
	auto use = tut::parse_su_file(su_file);
	for (auto& line : use)
	{
		fmt::print("{}({}) {} {}\n", line.file_name, line.row, line.function, line.stack_use);
	}
}

int main(int argc, char** argv)
{
    std::map<std::string, void(*)(std::ostream&, fs::path)> funcs;
    funcs.emplace("info", &write_info);
    funcs.emplace("stack_use", &stack_use);

	auto it = funcs.find(argv[1]);

	if (it == funcs.end())
	{
		std::cerr << "command " << argv[1] << " not found\n";
		return 1;
	}

    it->second(std::cout, argv[2]);
    std::cout << '\n';
}