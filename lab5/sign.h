#ifndef SIGN_H
#define SIGN_H

#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <fstream>
#include <vector>

const char hn[] = "SHA256";

void generateKeys(EVP_PKEY *publicKey, EVP_PKEY *privateKey);
void sign(const unsigned char *message, size_t msgLen,
         unsigned char **signature, size_t *sigLen, EVP_PKEY *privateKey);
int verify(const unsigned char *message, size_t msgLen,
           const unsigned char *signature, size_t sigLen, EVP_PKEY *publicKey);

#endif // SIGN_H
