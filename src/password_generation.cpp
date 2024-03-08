#include "../include/password_generation.hpp"
#include "../include/password_encryption.hpp"
#include <iostream>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <cstring> // for memcpy

// Define a global random number generator engine
std::mt19937 gen;

std::vector<uint8_t> generate_random_numbers(int8_t max_value, int8_t lenght) {
    /*
    Generate vector of random number

    Input : 
        - max_value : define boundary for normal distribution of random generation
        - lenght : define the lenght of the vector
    Output: vector of random number
    */

    // Define the distribution
    std::uniform_int_distribution<> dis(0, max_value);

    // Vector to store the generated random numbers
    std::vector<uint8_t> random_numbers;

    // Generate 'count' number of random numbers
    for (int i = 0; i < lenght; ++i) {
        // Generate a random number
        int random_number = dis(gen);

        // Add the random number to the vector
        random_numbers.push_back(random_number);
    }

    return random_numbers;
}

std::string create_password(uint8_t pass_lenght, bool rand)
{
    /*
    Generate a string password with random number, character and special character

    Input : 
        - pass_lenght : size of the password
        - rand : allow to fixe seed of random number for testing
    Output : string of size pass_lenght 
    */

    // Initialize the random number generator engine based on the value of 'rand'
    if(rand){
        std::random_device rd;
        gen.seed(rd());
    }
    else{
        gen.seed(SEED); // Seed with a fixed value
    }

    std::string password = "";

    std::vector<uint8_t> list_numbers = generate_random_numbers(allowed_characters.size(), pass_lenght);

    for(int8_t i = 0; i < pass_lenght; i++)
    {
        password.push_back(static_cast<char>(allowed_characters[list_numbers[i]]));
    }

    return password;
}

// Base64 encode binary data
std::string base64_encode(const unsigned char* input, size_t input_len) {
    BIO* bio = BIO_new(BIO_s_mem());
    BIO* b64 = BIO_new(BIO_f_base64());
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    bio = BIO_push(b64, bio);
    BIO_write(bio, input, input_len);
    BIO_flush(bio);
    BUF_MEM* bufferPtr;
    BIO_get_mem_ptr(bio, &bufferPtr);
    std::string encoded(bufferPtr->data, bufferPtr->length);
    BIO_free_all(bio);
    return encoded;
}

// Base64 decode string data
unsigned char* base64_decode(const std::string& input, size_t& output_len) {
    BIO* bio = BIO_new_mem_buf(input.data(), input.size());
    BIO* b64 = BIO_new(BIO_f_base64());
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    bio = BIO_push(b64, bio);

    // Dynamically allocate memory to hold the decoded data
    unsigned char* buffer = new unsigned char[input.size()]; // Allocate enough memory

    size_t total_read = 0;
    int readBytes;
    while ((readBytes = BIO_read(bio, buffer + total_read, input.size() - total_read)) > 0) {
        total_read += readBytes;
    }
    BIO_free_all(bio);
    
    output_len = total_read;
    return buffer; // Return the dynamically allocated buffer
}

std::string return_encrypted_password(std::string master_password, unsigned char* salt, unsigned char* iv)
{
    // Derive a 256-bit key from the master password
    unsigned char key[KEY_SIZE];
    derivekey_from_password(master_password, key, salt);

    // Generate a password 
    int8_t pass_lenght = PASSWORD_LENGHT;
    std::string password = "";
    password = create_password(pass_lenght);

    // Message to be encrypted 
    unsigned char *plaintext =
        (unsigned char *)password.c_str();

    //Buffer for ciphertext
    unsigned char encrypted_password[128];
    int ciphertext_len = 0;

    // Generate random IV at each encryption
    RAND_bytes(iv, EVP_CIPHER_iv_length(EVP_aes_256_cbc()));

    // Encrypt the plaintext 
    ciphertext_len = encrypt (plaintext, strlen ((char *)plaintext), key, sizeof(key), iv,
                              EVP_CIPHER_iv_length(EVP_aes_256_cbc()), encrypted_password);

    std::string encoded_password = base64_encode(encrypted_password, ciphertext_len);
    return encoded_password;
}
