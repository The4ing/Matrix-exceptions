#include "FunctionCalculator.h"

#include <string>
#include <iostream>


int main()
{
    try {
        FunctionCalculator(std::cin, std::cout).run();
    }
    catch (const std::exception& e) {
        std::cout << e.what();
    }

}
