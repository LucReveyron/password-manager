#include <iostream>
#include "../include/password_generation.hpp"

int main() {
    int8_t pass_lenght = 12;
    std::string password = "";
    password = create_password(pass_lenght);
    std::cout << password << std::endl;
    return 0;
}