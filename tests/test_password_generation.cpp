#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <iostream>
#include <random>
#include <algorithm> // for std::max_element
#include "../include/doctest.h"
#include "../include/password_generation.hpp"

// Test case
TEST_CASE("Test if generate_random_numbers returns a value between 0 and 2") {

    std::mt19937 gen(42);

    int8_t max_value = 2;
    int8_t lenght = 5;

    // Test multiple runs to ensure correctness on average
    for (int i = 0; i < 1000; ++i) {
        std::vector<uint8_t> result = generate_random_numbers(max_value, lenght);
        // Check size of the generation
        CHECK(result.size() == lenght);
        // Check maximum value of generation
        CHECK(*std::max_element(result.begin(), result.end()) <= max_value);
    }
}

TEST_CASE("Test password generation") {

    int8_t pass_lenght = 12;
    std::string password = "";
    password = create_password(pass_lenght, false);
    // Check size of the password is correct
    CHECK(password.size() == pass_lenght);
    // Check generation example
    CHECK(password == "i7T0I1&VM2Gd");
}

