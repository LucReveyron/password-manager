/**
 * @file   password_encryption.cpp
 * @brief  Implementation of functions for password-based encryption and decryption.
 * 
 * This file contains the implementation of functions for deriving a key from a password,
 * encrypting plaintext using AES-256 CBC mode, and decrypting ciphertext.
 * 
 * @author Luc Reveyron
 * @date   14/03/2024
 */

#include <iostream>
#include "../include/password_encryption.hpp"

void derivekey_from_password(const std::string& password, unsigned char* derivedKey, unsigned char* salt)
{
    // Generate a random salt only if it's not already provided
    if (salt[0] == '\0') {
        RAND_bytes(salt, SALT_SIZE);
    }

    // Derive the key using PBKDF2
    PKCS5_PBKDF2_HMAC_SHA1(
        password.c_str(),
        static_cast<int>(password.length()),
        salt,
        SALT_SIZE,
        NBR_ITERATIONS,
        KEY_SIZE,
        derivedKey
    );
}

int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key, int key_lenght,
            unsigned char *iv, int iv_lenght, unsigned char *ciphertext)
{
    // Check if any input pointer is null
    if(plaintext == nullptr || key == nullptr || iv == nullptr || ciphertext == nullptr){
        return -1;
    }

    // Check key and IV size 
    if(key_lenght != KEY_SIZE || iv_lenght != EVP_CIPHER_iv_length(EVP_aes_256_cbc()))
        return -1;

    EVP_CIPHER_CTX *ctx;

    int len;

    int ciphertext_len;

    /* Create and initialise the context */
    if(!(ctx = EVP_CIPHER_CTX_new()))
        handle_errors();

    /*
     * Initialise the encryption operation. IMPORTANT - ensure you use a key
     * and IV size appropriate for your cipher
     * In this example we are using 256 bit AES (i.e. a 256 bit key). The
     * IV size for *most* modes is the same as the block size. For AES this
     * is 128 bits
     */
    if(EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv) != 1){
        EVP_CIPHER_CTX_free(ctx);
        handle_errors();
    }

    /*
     * Provide the message to be encrypted, and obtain the encrypted output.
     * EVP_EncryptUpdate can be called multiple times if necessary
     */
    if(EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len) != 1){
        EVP_CIPHER_CTX_free(ctx);
        handle_errors();
    } 
    ciphertext_len = len;

    /*
     * Finalise the encryption. Further ciphertext bytes may be written at
     * this stage.
     */
    if(EVP_EncryptFinal_ex(ctx, ciphertext + len, &len) != 1){
        EVP_CIPHER_CTX_free(ctx);
        handle_errors();
    }
    ciphertext_len += len;

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);

    return ciphertext_len;
}

int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,
            unsigned char *iv, unsigned char *plaintext)
{
        // Check if any input pointer is null
    if(plaintext == nullptr || key == nullptr || iv == nullptr || ciphertext == nullptr){
        return -1;
    }
    
    EVP_CIPHER_CTX *ctx;

    int len;

    int plaintext_len;

    /* Create and initialise the context */
    if(!(ctx = EVP_CIPHER_CTX_new()))
        handle_errors();

    /*
     * Initialise the decryption operation. IMPORTANT - ensure you use a key
     * and IV size appropriate for your cipher
     * In this example we are using 256 bit AES (i.e. a 256 bit key). The
     * IV size for *most* modes is the same as the block size. For AES this
     * is 128 bits
     */
    if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv)){
        EVP_CIPHER_CTX_free(ctx);
        handle_errors();
    }

    /*
     * Provide the message to be decrypted, and obtain the plaintext output.
     * EVP_DecryptUpdate can be called multiple times if necessary.
     */
    if(1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len)){
        EVP_CIPHER_CTX_free(ctx);
        handle_errors();
    }
    plaintext_len = len;

    /*
     * Finalise the decryption. Further plaintext bytes may be written at
     * this stage.
     */
    if(1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len)){
        EVP_CIPHER_CTX_free(ctx);
        std::cerr << "Decryption failed.\n";
        ERR_print_errors_fp(stderr);  // Print the OpenSSL error stack to stderr
        handle_errors();
    }
    plaintext_len += len;

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);

    return plaintext_len;
}

void handle_errors(void)
{
    ERR_print_errors_fp(stderr);
    abort();
}