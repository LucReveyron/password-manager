#include "../include/password_generation.hpp"

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