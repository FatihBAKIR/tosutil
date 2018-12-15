#include <iostream>
#include <tut/util.hpp>
#include <tut/loaders.hpp>

int main() {
    std::cout
            << tut::load_proc("STM32F103RB")->name << '\n'
            << tut::load_proc("STM32F103RB")->target->arch->name << '\n';
    std::cout << '\n';
    std::cout
            << tut::load_proc("atmega328p")->name << '\n'
            << tut::load_proc("atmega328p")->target->arch->name << '\n';
    return 0;
}