#ifndef PASSWORD_MANAGER_HPP
#define PASSWORD_MANAGER_HPP

#include <string>
#include <iostream>
#include <cstring> // For std::memcpy
#include <algorithm> // For std::min
#include "../include/password_vaulting.hpp"

class PasswordManager {
private:
    SecureVault vault;
    const std::string filename;

public:
    PasswordManager();
    ~PasswordManager();
    void add_password(const std::string &login);
    void search_passwords();
    void load_vault();
    void save_vault();
};

#endif // PASSWORDMANAGER_HPP
