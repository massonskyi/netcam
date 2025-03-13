#include <iostream>
#include "core.hpp"

int main() {
    std::cout << "Hello World!" << std::endl;
    std::cout << "Version: " << (const char*)VERSION_ << std::endl;
    std::cout << "Git Version: " << (const char*)GIT_VERSION_ << std::endl;
    return 0;
};