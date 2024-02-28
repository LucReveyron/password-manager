#ifndef PASSWORD_GENERATION_HPP  // Header guard to prevent multiple inclusions
#define PASSWORD_GENERATION_HPP

#include <vector>
#include <string>
#include <random>

#define SEED 50

const std::vector<int> allowed_characters = {
    // Lowercase letters (97 - 122)
    // Uppercase letters (65 - 90)
    // Digits (48 - 57)
    // Special characters
    35, 36, 38, 64,
    48, 49, 50, 51, 52, 53, 54, 55, 56, 57,
    65, 66, 67, 68, 69, 70, 71, 72, 73, 74,
    75, 76, 77, 78, 79, 80, 81, 82, 83, 84,
    85, 86, 87, 88, 89, 90,
    97, 98, 99, 100, 101, 102, 103, 104, 105, 106,
    107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
    117, 118, 119, 120, 121, 122
};

std::vector<uint8_t> generate_random_numbers(int8_t max_value, int8_t lenght);
std::string create_password(uint8_t pass_lenght, bool rand = true);

#endif  // PASSWORD_GENERATION_HPP
