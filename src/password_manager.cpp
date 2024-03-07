#include "../include/password_encryption.hpp"
#include "../include/password_generation.hpp"
#include "../include/password_manager.hpp"


void string_to_unsigned_char(const std::string& str, unsigned char* uchar_texto, size_t size)
{
    std::copy(str.begin(), str.begin() + std::min(str.size(), size), uchar_texto);
}

PasswordManager::PasswordManager() : filename("vault_file.bin") 
{
    load_vault();
}

PasswordManager::~PasswordManager()
{
    save_vault();
}

void PasswordManager::add_password(const std::string &login)
{
    std::string master_password = "";
    std::cout << "Please enter the master password : \n";
    std::cin >> master_password;
    // To do : password verification based on hashing

    // Salt for PBKDF2
    unsigned char salt[SALT_SIZE] = {0};
    // IV for encryption
    unsigned char iv[EVP_CIPHER_iv_length(EVP_aes_256_cbc())];

    std::string encrypted_password = return_encrypted_password(master_password, salt, iv);
    std::cout << encrypted_password << std::endl;
    VaultNode node(login, encrypted_password, std::string(reinterpret_cast<const char*>(salt), SALT_SIZE), 
                                            std::string(reinterpret_cast<const char*>(iv), SALT_SIZE));
    vault.add_node(node);
}

void PasswordManager::search_passwords()
{
    auto nodes = vault.get_nodes();
    for (size_t i = 0; i < nodes.size(); ++i) {
        std::cout << i + 1 << ". " << nodes[i].identifier << std::endl;
    }

    std::cout << "Select a login to view password, or 0 to return: ";
    int choice;
    std::cin >> choice;

    if (choice > 0 && static_cast<size_t>(choice) <= nodes.size()) {
        auto& node = nodes[choice - 1];
        // Convert data from vault to unsigned char 
        unsigned char encrypted_password[PASS_SIZE];
        std::cout << node.encrypted_password << std::endl;
        string_to_unsigned_char(node.encrypted_password, encrypted_password, PASS_SIZE);
        unsigned char salt[SALT_SIZE];
        string_to_unsigned_char(node.salt, salt, SALT_SIZE);
        unsigned char iv[EVP_CIPHER_iv_length(EVP_aes_256_cbc())];
        string_to_unsigned_char(node.iv, iv, EVP_CIPHER_iv_length(EVP_aes_256_cbc()));

        std::string master_password = "";
        std::cout << "Please enter the master password : \n";
        std::cin >> master_password;
        unsigned char key[KEY_SIZE] = {0};
        derivekey_from_password(master_password, key, salt);

        unsigned char decrypted_password[PASS_SIZE];
        //Bug here !!!
        int decryptedtext_len = decrypt(encrypted_password, PASS_SIZE, key, iv, decrypted_password); 
        std::cout << "Password for " << node.identifier << ": " << decrypted_password << std::endl;
    }
}

void PasswordManager::load_vault()
{
    try {
        vault.deserialize(filename);
    } catch (const std::exception& e) {
        std::cerr << "Failed to load vault: " << e.what() << std::endl;
        std::cout << "Continue with a new empty vault\n" << std::endl;
    }
}

void PasswordManager::save_vault()
{
    try {
        vault.serialize(filename);
    } catch (const std::exception& e) {
        std::cerr << "Failed to save vault: " << e.what() << std::endl;
    }
}