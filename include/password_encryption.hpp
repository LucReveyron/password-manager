#ifndef PASSWORD_ENCRYPTION_HPP  // Header guard to prevent multiple inclusions
#define PASSWORD_ENCRYPTION_HPP

#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/rand.h>
#include <openssl/sha.h>
#include <vector>
#include <string>

#define KEY_SIZE    32
#define SALT_SIZE   16

void derivekey_from_password(const std::string& password, unsigned char* derivedKey, unsigned char* salt);
int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key, int key_lenght,
            unsigned char *iv, int iv_lenght, unsigned char *ciphertext);
int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,
            unsigned char *iv, unsigned char *plaintext);
void handleErrors(void);

#endif  // PASSWORD_ENCRYPTION_HPP
