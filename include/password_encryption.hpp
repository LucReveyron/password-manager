#ifndef PASSWORD_ENCRYPTION_HPP  // Header guard to prevent multiple inclusions
#define PASSWORD_ENCRYPTION_HPP

#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/rand.h>
#include <openssl/sha.h>
#include <vector>
#include <string>

#define NBR_ITERATIONS  10000
#define KEY_SIZE        32
#define PASS_SIZE       16
#define SALT_SIZE       16
#define IV_SIZE         EVP_CIPHER_iv_length(EVP_aes_256_cbc())
#define CIPHERTEXT_SIZE 12
#define NULL_SIZE       1

void derivekey_from_password(const std::string& password, unsigned char* derivedKey, unsigned char* salt);
int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key, int key_lenght,
            unsigned char *iv, int iv_lenght, unsigned char *ciphertext);
int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,
            unsigned char *iv, unsigned char *plaintext);
void handle_errors(void);

#endif  // PASSWORD_ENCRYPTION_HPP
