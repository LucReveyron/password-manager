#include "../include/doctest_header.hpp"

#include <iostream>
#include <random>
#include <algorithm> // for std::max_element
#include "../include/password_encryption.hpp"

TEST_CASE("Encrypt function test") {
    // Test data
    unsigned char plaintext[] = "This is a test plaintext";
    int plaintext_len = sizeof(plaintext) - 1; // excluding null terminator
    unsigned char key[] = "01234567890123456789012345678901"; // 256-bit key
    unsigned char iv[] = "0123456789012345"; // 128-bit IV
    unsigned char ciphertext[128]; // Assuming ciphertext buffer is large enough

    SUBCASE("Valid input") {
        int ciphertext_len = encrypt(plaintext, plaintext_len, key, KEY_SIZE, iv, 
                                    EVP_CIPHER_iv_length(EVP_aes_256_cbc()), ciphertext);
        CHECK(ciphertext_len > 0); // Check if ciphertext length is positive
    }

    SUBCASE("Null pointers") {
        // Passing null pointers should result in an error
        int ciphertext_len = encrypt(nullptr, plaintext_len, key, KEY_SIZE, iv, EVP_CIPHER_iv_length(EVP_aes_256_cbc()), ciphertext);
        CHECK(ciphertext_len == -1); // Check if error code is returned

        ciphertext_len = encrypt(plaintext, plaintext_len, nullptr, KEY_SIZE, iv, EVP_CIPHER_iv_length(EVP_aes_256_cbc()), ciphertext);
        CHECK(ciphertext_len == -1); // Check if error code is returned

        ciphertext_len = encrypt(plaintext, plaintext_len, key, KEY_SIZE, nullptr, EVP_CIPHER_iv_length(EVP_aes_256_cbc()), ciphertext);
        CHECK(ciphertext_len == -1); // Check if error code is returned

        ciphertext_len = encrypt(plaintext, plaintext_len, key, KEY_SIZE, iv, EVP_CIPHER_iv_length(EVP_aes_256_cbc()), nullptr);
        CHECK(ciphertext_len == -1); // Check if error code is returned
    }

    SUBCASE("Invalid key or IV length") {
        // Passing incorrect key or IV length should result in an error
        unsigned char invalid_key[] = "123456789012345"; // 128-bit key
        unsigned char invalid_iv[] = "12345678"; // 128-bit IV

        int ciphertext_len = encrypt(plaintext, plaintext_len, invalid_key,16, iv, EVP_CIPHER_iv_length(EVP_aes_256_cbc()), ciphertext);
        CHECK(ciphertext_len == -1); // Check if error code is returned

        ciphertext_len = encrypt(plaintext, plaintext_len, key,KEY_SIZE, invalid_iv, 8, ciphertext);
        CHECK(ciphertext_len == -1); // Check if error code is returned
    }
}

// Do not test wrong decryption case to not introduce weakness in the encrypted data, 
// prefer check correctness of master key.
TEST_CASE("Encrypt and decrypt data using AES-256-CBC") {
    unsigned char key[] = "0123456789abcdef0123456789abcdef"; // 32 bytes for AES-256
    unsigned char iv[] = "1234567890abcdef"; // 16 bytes for AES block size
    unsigned char plaintext[] = "This is a test message.";
    unsigned char ciphertext[128];
    unsigned char decryptedtext[128];

    int plaintext_len = sizeof(plaintext) - 1; // Excluding null terminator for plaintext
    int decryptedtext_len;

    // Encrypt the plaintext
    int ciphertext_len = encrypt(plaintext, plaintext_len, key, KEY_SIZE, iv,
                                    EVP_CIPHER_iv_length(EVP_aes_256_cbc()), ciphertext);
    // Decrypt the ciphertext
    decryptedtext_len = decrypt(ciphertext, ciphertext_len, key, iv, decryptedtext);

    // Null-terminate the decrypted text
    decryptedtext[decryptedtext_len] = '\0';

    // Check if the decrypted text matches the original plaintext
    CHECK(strcmp((char*)plaintext, (char*)decryptedtext) == 0);
}