#include "print_ip.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <tuple>

int main()
{
    functions::print_ip(char(-1));
    std::cout << std::endl;
    functions::print_ip(short(0));
    std::cout << std::endl;
    functions::print_ip(int(2130706433));
    std::cout << std::endl;
    functions::print_ip(long(8875824491850138409));
    std::cout << std::endl;
    functions::print_ip(std::string{"Hello, World!"}, std::cout);
    std::cout << std::endl;
    functions::print_ip(std::vector{100, 200, 300, 400});
    std::cout << std::endl;
    functions::print_ip(std::list{400, 300, 200, 100});
    std::cout << std::endl;
    functions::print_ip(std::make_tuple(123, 456, 789, 0) );
    std::cout << std::endl;
}