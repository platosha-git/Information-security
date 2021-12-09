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
int sign(const unsigned char *msg, size_t mlen,
         unsigned char **sig, size_t *slen, EVP_PKEY *publicKey);
int verify(const unsigned char *msg, size_t mlen,
           const unsigned char *sig, size_t slen, EVP_PKEY *privateKey);

#endif // SIGN_H
