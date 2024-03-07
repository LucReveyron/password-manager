/**
 * @file password_vaulting.cpp
 * @brief This file contains the implementation of the VaultNode and SecureVault classes.
 *
 * VaultNode and SecureVault are use to manage the data structure that store password manager 
 * information.
 */

#include <fstream>
#include <stdexcept>
#include "../include/password_vaulting.hpp"

VaultNode::VaultNode(const std::string& id, const std::string& pwd, const std::string& salt, const std::string& iv)
    : identifier(id), encrypted_password(pwd), salt(salt), iv(iv) {}

void SecureVault::add_node(const VaultNode& node) {
    nodes.push_back(node);
}

const std::vector<VaultNode>& SecureVault::get_nodes() const {
    return nodes;
}

void SecureVault::serialize(const std::string& filename) const {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Cannot open file for writing");
    }

    size_t nodes_count = nodes.size();
    file.write(reinterpret_cast<const char*>(&nodes_count), sizeof(nodes_count));

    for (const auto& node : nodes) {
        size_t id_length = node.identifier.size();
        file.write(reinterpret_cast<const char*>(&id_length), sizeof(id_length));
        file.write(node.identifier.data(), id_length);

        size_t pwd_length = node.encrypted_password.size();
        file.write(reinterpret_cast<const char*>(&pwd_length), sizeof(pwd_length));
        file.write(node.encrypted_password.data(), pwd_length);

        size_t salt_length = node.salt.size();
        file.write(reinterpret_cast<const char*>(&salt_length), sizeof(salt_length));
        file.write(node.salt.data(), salt_length);

        size_t iv_length = node.iv.size();
        file.write(reinterpret_cast<const char*>(&iv_length), sizeof(iv_length));
        file.write(node.iv.data(), iv_length);
    }

    file.close();
}

void SecureVault::deserialize(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Cannot open file for reading");
    }

    size_t nodes_count;
    file.read(reinterpret_cast<char*>(&nodes_count), sizeof(nodes_count));

    nodes.clear();
    for (size_t i = 0; i < nodes_count; ++i) {
        size_t id_length;
        file.read(reinterpret_cast<char*>(&id_length), sizeof(id_length));
        std::string id(id_length, '\0');
        file.read(&id[0], id_length);

        size_t pwd_length;
        file.read(reinterpret_cast<char*>(&pwd_length), sizeof(pwd_length));
        std::string pwd(pwd_length, '\0');
        file.read(&pwd[0], pwd_length);

        size_t salt_length;
        file.read(reinterpret_cast<char*>(&salt_length), sizeof(salt_length));
        std::string salt(salt_length, '\0');
        file.read(&salt[0], salt_length);

        size_t iv_length;
        file.read(reinterpret_cast<char*>(&iv_length), sizeof(iv_length));
        std::string iv(iv_length, '\0');
        file.read(&iv[0], iv_length);

        nodes.emplace_back(id, pwd, salt, iv);
    }

    file.close();
}