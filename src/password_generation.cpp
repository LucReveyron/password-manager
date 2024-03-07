#include "../include/password_generation.hpp"
#include "../include/password_encryption.hpp"
#include <iostream>

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

std::string return_encrypted_password(std::string master_password, unsigned char* salt, unsigned char* iv)
{
    // Derive a 256-bit key from the master password
    unsigned char key[KEY_SIZE] = {0};
    derivekey_from_password(master_password, key, salt);

    // Generate a password 
    int8_t pass_lenght = PASSWORD_LENGHT;
    std::string password = "";
    password = create_password(pass_lenght);

    // Message to be encrypted 
    unsigned char *plaintext =
        (unsigned char *)password.c_str();

    //Buffer for ciphertext
    unsigned char encrypted_password[PASS_SIZE] = {0};
    int ciphertext_len = 0;

    // Generate random IV at each encryption
    RAND_bytes(iv, EVP_CIPHER_iv_length(EVP_aes_256_cbc()));

    // Encrypt the plaintext 
    ciphertext_len = encrypt (plaintext, strlen ((char *)plaintext), key,KEY_SIZE, iv,
                              EVP_CIPHER_iv_length(EVP_aes_256_cbc()), encrypted_password);

    std::cout << ciphertext_len << std::endl;

    return std::string(reinterpret_cast<const char*>(encrypted_password), KEY_SIZE);
}
