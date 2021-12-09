#ifndef SIGN_H
#define SIGN_H

#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <fstream>
#include <vector>

#define UNUSED(x) ((void)(x))

const char hn[] = "SHA256";

void generateKeys(EVP_PKEY **skey, EVP_PKEY **vkey);
int sign(const unsigned char *msg, size_t mlen,
         unsigned char **sig, size_t *slen, EVP_PKEY *pkey);

int verify(const unsigned char *msg, size_t mlen, const unsigned char *sig, size_t slen, EVP_PKEY *pkey);

void read_keys(EVP_PKEY **public_k, EVP_PKEY **private_k);
size_t read_sign(unsigned char **sign, char *filename);


#endif // SIGN_H
