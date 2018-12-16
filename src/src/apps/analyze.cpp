//
// Created by fatih on 12/15/18.
//

#include <string>
#include <tut/loaders.hpp>
#include <tut/elf.hpp>
#include <iostream>
#include <map>

void write_info(std::ostream& os, tut::elf_ptr e)
{
    os << to_string(get_machine(*e));
}

int main(int argc, char** argv)
{
    std::map<std::string, void(*)(std::ostream&, tut::elf_ptr)> funcs;
    funcs.emplace("info", &write_info);

	auto elf_obj = tut::load_elf(argv[2]);
    funcs[argv[1]](std::cout, std::move(elf_obj));
    std::cout << '\n';
}