#include "../include/doctest_header.hpp"

#include "../include/password_vaulting.hpp"
#include <fstream>

TEST_CASE("Testing SecureVault functionality") {
    SecureVault vault;
    std::string filename = "test_securevault.bin";

    SUBCASE("Add and retrieve nodes") {
        vault.add_node(VaultNode("site1", "password1"));
        vault.add_node(VaultNode("site2", "password2"));
        const auto& nodes = vault.get_nodes();

        CHECK(nodes.size() == 2);
        CHECK(nodes[0].identifier == "site1");
        CHECK(nodes[0].encrypted_password == "password1");
        CHECK(nodes[1].identifier == "site2");
        CHECK(nodes[1].encrypted_password == "password2");
    }

    SUBCASE("Serialize and deserialize vault") {
        vault.add_node(VaultNode("gmail", "encryptedGmailPassword"));
        vault.add_node(VaultNode("yahoo", "encryptedYahooPassword"));
        vault.serialize(filename);

        SecureVault loadedVault;
        loadedVault.deserialize(filename);

        const auto& nodes = loadedVault.get_nodes();
        CHECK(nodes.size() == 2);
        CHECK(nodes[0].identifier == "gmail");
        CHECK(nodes[0].encrypted_password == "encryptedGmailPassword");
        CHECK(nodes[1].identifier == "yahoo");
        CHECK(nodes[1].encrypted_password == "encryptedYahooPassword");

        // Cleanup
        std::remove(filename.c_str());
    }
}
