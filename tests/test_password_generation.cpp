#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../include/doctest_header.hpp"

#include <iostream>
#include <random>
#include <algorithm> // for std::max_element
#include "../include/password_generation.hpp"
#include "../include/password_encryption.hpp"

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

TEST_CASE("Base64 encoding and decoding") {

    unsigned char binaryData[3] = {0x41, 0x42, 0x43};
    std::string encoded = base64_encode(binaryData, 3);

    size_t decoded_len = 0;
    unsigned char* decoded = base64_decode(encoded, decoded_len);

    // Check length consistency
    CHECK(decoded_len == 3);

    // Compare original and decoded data
    bool is_same = std::memcmp(binaryData, decoded, decoded_len) == 0;
    CHECK(is_same);

    delete[] decoded; // Clean up dynamically allocated memory
}

TEST_CASE("Full encryption and decryption cycle with base64 encoding/decoding") {
    unsigned char binaryData[3] = {0x41, 0x42, 0x43};
    unsigned char key[32]; // 256-bit key for AES-256
    unsigned char iv[16];  // 128-bit IV for AES

    // Fill key and IV with example values for testing
    memset(key, 'A', sizeof(key));
    memset(iv, 'B', sizeof(iv));

    // Buffer for ciphertext (ensure it's large enough)
    unsigned char ciphertext[1024];

    int encrypted_length = encrypt(binaryData, 3, key, sizeof(key), iv, sizeof(iv), ciphertext);
    REQUIRE(encrypted_length > 0);

    // Base64 encode the encrypted data
    std::string encoded = base64_encode(ciphertext, encrypted_length);

    // Base64 decode
    size_t decoded_len;
    unsigned char* decoded_data = base64_decode(encoded, decoded_len);
    REQUIRE(decoded_data != nullptr);

    // Decrypt the data
    unsigned char decrypted_text[3];
    int decrypted_length = decrypt(decoded_data, decoded_len, key, iv, decrypted_text);
    REQUIRE(decrypted_length > 0);

    CHECK(memcmp(decrypted_text, binaryData, decrypted_length) == 0);

    delete[] decoded_data; // Clean up dynamically allocated memory in base64_decode
}