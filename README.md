# Password Manager Project

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)


A simple password manager application for securely storing and managing passwords. This project provides a menu-driven interface for adding new passwords, searching existing passwords, and exiting the program.

## Features

- **Add New Passwords:** Users can add new passwords by providing a login name and master password.
- **Search Passwords:** Users can search for existing passwords by login name.
- **Secure Encryption:** Passwords are securely encrypted using AES-256 CBC mode.
- **Vault Storage:** Encrypted passwords are stored securely in a vault file.
- **Password Generation:** Option to generate strong passwords using random characters.

## Installation

1. **Clone the Repository:** Clone the repository to your local machine using Git:

   ```bash
   git clone https://github.com/your-username/password-manager.git

2. **Build the Project:** Navigate to the project directory and build the project using the provided Makefile:
   ```bash
   cd password-manager
   make
This will compile the source files and generate the executable password_manager.

## Usage

1. **Run the Executable:** Execute the built executable to launch the password manager application:
   ```bash
   ./password_manager

2. **Use the Menu Interface:**

- Add New Password: Select "New password" to add a new password. Follow the prompts to enter the login name and master password.
- Search Password: Select "Search password" to search for an existing password. Enter the login name to search for.
- Exit: Select "Exit" to exit the program.

## Dependencies

- **OpenSSL Library:** Required for encryption and decryption functionalities.
- **C++11 or Later Compiler:** Compiler supporting C++11 standard or later.
- **Standard C++ Libraries:** Standard libraries used in the C++ programming language.

## License

This project is licensed under the MIT License.
This version provides more detailed usage instructions, explaining how to run the executable and use the menu interface step by step. Feel free to use or modify it according to your project's needs.
