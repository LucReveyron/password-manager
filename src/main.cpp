#include <iostream>
#include "../include/password_generation.hpp"
#include "../include/password_encryption.hpp"
#include "../include/password_manager.hpp"

#include <iostream>
#include <vector>
#include <functional>

class MenuOption {
public:
    std::string name;
    std::function<void()> action;

    MenuOption(std::string name, std::function<void()> action)
        : name(std::move(name)), action(std::move(action)) {}
};

class Menu {
private:
    std::vector<MenuOption> options;
    bool exitMenu = false;

public:
    void addOption(const std::string& name, std::function<void()> action) {
        options.emplace_back(name, action);
    }

    void display() const {
        for (size_t i = 0; i < options.size(); ++i) {
            std::cout << i + 1 << ". " << options[i].name << std::endl;
        }
    }

    void exit() {
        exitMenu = true;
    }

    void run() {
        while (!exitMenu) {
            display();
            std::cout << "> ";
            size_t choice;
            std::cin >> choice;

            if (choice > 0 && choice <= options.size()) {
                options[choice - 1].action();
            } else {
                std::cout << "Invalid selection. Please try again." << std::endl;
            }
        }
    }
};

int main() {
    PasswordManager pm;
    Menu menu;

    menu.addOption("New password", [&pm]() {
        std::cout << "Enter login name: ";
        std::string login;
        std::cin >> login;
        pm.add_password(login);
        std::cout << "Password saved securely." << std::endl;
    });

    menu.addOption("Search password", [&pm]() {
        pm.search_passwords();
    });

    // Continue with the Exit option as before
    menu.addOption("Exit", [&menu]() {
        std::cout << "Exiting program." << std::endl;
        menu.exit();
    });

    menu.run();

    return 0;
}


/*
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
*/