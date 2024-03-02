#ifndef PASSWORD_ENCRYPTION_HPP  // Header guard to prevent multiple inclusions
#define PASSWORD_ENCRYPTION_HPP

#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <vector>
#include <string>

int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
            unsigned char *iv, unsigned char *ciphertext);
int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,
            unsigned char *iv, unsigned char *plaintext);
void handleErrors(void);

#endif  // PASSWORD_ENCRYPTION_HPP
