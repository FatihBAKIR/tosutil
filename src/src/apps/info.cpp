//
// Created by fatih on 12/15/18.
//

#include <string>
#include <tut/loaders.hpp>
#include <iostream>
#include <map>

void do_processor(const std::string& proc)
{
    auto p = tut::load_proc(proc);
    std::cout << p->alias << '\n';
    std::cout << p->target->arch->alias << '\n';
}

int main(int argc, char** argv)
{
    std::map<std::string, void(*)(const std::string&)> handlers;
    handlers.emplace("proc", &do_processor);

    auto it = handlers.find(std::string(argv[1]));
    if (it == handlers.end())
    {
        return 1;
    }

    it->second(argv[2]);
}