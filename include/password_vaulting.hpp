#ifndef PASSWORD_GENERATION_HPP  // Header guard to prevent multiple inclusions
#define PASSWORD_GENERATION_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>


// Represents a single node in the SecureVault, storing an identifier (e.g., a service name)
// and an encrypted password for that service.
struct VaultNode {
    std::string identifier;
    std::string encrypted_password;

    VaultNode(const std::string& id, const std::string& pwd);
};

// SecureVault provides a secure storage mechanism for passwords, 
// leveraging encryption to ensure that stored passwords are protected.
class SecureVault {
private:
    std::vector<VaultNode> nodes;

public:
    void add_node(const VaultNode& node);
    const std::vector<VaultNode>& get_nodes() const;
    void serialize(const std::string& filename) const;
    void deserialize(const std::string& filename);
};

#endif  // PASSWORD_GENERATION_HPP