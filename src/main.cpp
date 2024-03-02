#include <iostream>
#include "../include/password_generation.hpp"
#include "../include/password_encryption.hpp"

#define PASSWORD_LENGHT 12

int main (void)
{
    // Master password
    std::string masterPassword = "MySuperSecureMasterPassword";

    // Derive a 256-bit key from the master password
    unsigned char key[KEY_SIZE] = {0};;
    // Salt for PBKDF2
    unsigned char salt[SALT_SIZE] = {0};

    derivekey_from_password(masterPassword, key, salt);

    // Generate a password 
    int8_t pass_lenght = PASSWORD_LENGHT;
    std::string password = "";
    password = create_password(pass_lenght);

    // Print the original password
    std::cout << "Password: ";
    std::cout << password << std::endl;
    
    // Message to be encrypted 
    unsigned char *plaintext =
        (unsigned char *)password.c_str();

    //Buffer for ciphertext
    unsigned char ciphertext[128] = {0};

    // Buffer for the decrypted text 
    unsigned char decryptedtext[128] = {0};

    int decryptedtext_len = 0, ciphertext_len = 0;

    // Generate random IV at each encryption
    unsigned char iv[EVP_CIPHER_iv_length(EVP_aes_256_cbc())];
    RAND_bytes(iv, EVP_CIPHER_iv_length(EVP_aes_256_cbc()));

    // Encrypt the plaintext 
    ciphertext_len = encrypt (plaintext, strlen ((char *)plaintext), key,KEY_SIZE, iv,
                              EVP_CIPHER_iv_length(EVP_aes_256_cbc()), ciphertext);

   // Do something useful with the ciphertext here 
    printf("Ciphertext is:\n");
    BIO_dump_fp (stdout, (const char *)ciphertext, ciphertext_len);

    // Combine salt, IV, and encrypted data
    std::string combinedData(reinterpret_cast<char*>(salt), sizeof(salt));
    combinedData += std::string(reinterpret_cast<char*>(iv), EVP_CIPHER_iv_length(EVP_aes_256_cbc()));
    combinedData += std::string(reinterpret_cast<char*>(ciphertext), ciphertext_len);;

    // Decrypt the ciphertext 
    decryptedtext_len = decrypt(ciphertext, ciphertext_len, key, iv,
                                decryptedtext);

    // Add a NULL terminator. We are expecting printable text 
    decryptedtext[decryptedtext_len] = '\0';

    // Show the decrypted text 
    printf("Decrypted text is:\n");
    printf("%s\n", decryptedtext);
}