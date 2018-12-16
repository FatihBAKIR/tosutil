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

void do_board(const std::string& board)
{
	auto b = tut::load_board(board);
	std::cout << b->alias << '\n';
	std::cout << b->proc->alias << '\n';
	std::cout << b->programmers[0]->alias << '\n';
}

int main(int argc, char** argv)
{
    std::map<std::string, void(*)(const std::string&)> handlers;
    handlers.emplace("proc", &do_processor);
    handlers.emplace("board", &do_board);

	argv[1] = "board";
	argv[2] = "nucleo/f103rb";
    auto it = handlers.find(std::string(argv[1]));
    if (it == handlers.end())
    {
        return 1;
    }

    it->second(argv[2]);
}