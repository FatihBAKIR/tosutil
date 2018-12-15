#include <iostream>
#include <tut/util.hpp>
#include <tut/loaders.hpp>

int main() {
    std::cout
            << tut::load_proc("STM32/F103RB")->alias << '\n'
            << tut::load_proc("STM32/F103RB")->target->arch->alias << '\n';

    std::cout << '\n';
    
    std::cout
            << tut::load_proc("atmega328p")->alias << '\n'
            << tut::load_proc("atmega328p")->target->arch->alias << '\n';
}