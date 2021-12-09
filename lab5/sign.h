#ifndef SIGN_H
#define SIGN_H

#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <fstream>
#include <vector>

const char hn[] = "SHA256";

void generateKeys(EVP_PKEY **skey, EVP_PKEY **vkey);
int sign(const unsigned char *msg, size_t mlen,
         unsigned char **sig, size_t *slen, EVP_PKEY *pkey);
int verify(const unsigned char *msg, size_t mlen,
           const unsigned char *sig, size_t slen, EVP_PKEY *pkey);

#endif // SIGN_H
