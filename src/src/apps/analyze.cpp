//
// Created by fatih on 12/15/18.
//

#include <string>
#include <tut/loaders.hpp>
#include <elfio/elfio.hpp>
#include <elfio/elfio_dump.hpp>
#include <iostream>
#include <map>

void write_info(std::ostream& os, ELFIO::elfio& e)
{
    os << e.get_machine();
}

int main(int argc, char** argv)
{
    std::map<std::string, void(*)(std::ostream&, ELFIO::elfio&)> funcs;
    funcs.emplace("info", &write_info);

    ELFIO::elfio e;

    e.load(argv[2]);

    funcs[argv[1]](std::cout, e);
    std::cout << '\n';
}