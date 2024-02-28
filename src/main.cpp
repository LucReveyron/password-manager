#include <iostream>
#include <openssl/sha.h>
#include <openssl/rand.h>

// Function to generate a random string of specified length
std::string generateRandomString(int length) {
    std::string str(length, '\0');
    RAND_bytes(reinterpret_cast<unsigned char*>(&str[0]), length);
    return str;
}

// Function to calculate SHA-256 hash of a string
std::string calculateSHA256(const std::string& input) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, input.c_str(), input.length());
    SHA256_Final(hash, &sha256);

    std::string hashStr;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        hashStr += hash[i];
    }
    return hashStr;
}

int main() {
    // Generate a random string
    std::string randomString = generateRandomString(16);

    // Calculate SHA-256 hash of the random string
    std::string hash = calculateSHA256(randomString);

    // Print the random string and its SHA-256 hash
    std::cout << "Random String: " << randomString << std::endl;
    std::cout << "SHA-256 Hash: ";
    for (char c : hash) {
        printf("%02x", static_cast<unsigned char>(c));
    }
    std::cout << std::endl;

    return 0;
}

/*
#include <iostream>
#include "../include/password_generation.hpp"

int main() {
    int8_t pass_lenght = 12;
    std::string password = "";
    password = create_password(pass_lenght);
    std::cout << password << std::endl;
    return 0;
}
*/