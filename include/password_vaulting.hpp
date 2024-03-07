#ifndef PASSWORD_VAULTING_HPP  // Header guard to prevent multiple inclusions
#define PASSWORD_VAULTING_HPP

#include <vector>
#include <string>

// Represents a single node in the SecureVault, storing an identifier (e.g., a service name)
// an encrypted password for that service, the salt and the IV use to encrypt him.
class VaultNode {
public:
    std::string identifier;
    std::string encrypted_password;
    std::string salt;
    std::string iv;

    VaultNode(const std::string& id, const std::string& pwd, const std::string& salt, const std::string& iv);
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