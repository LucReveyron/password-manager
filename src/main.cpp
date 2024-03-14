/**
 * @file   main.cpp
 * @brief  Main program for managing passwords.
 * 
 * This program provides a menu-driven interface for managing passwords, including options
 * for adding new passwords, searching existing passwords, and exiting the program.
 * 
 * @author Luc Reveyron
 * @date   14/03/2024
 */

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