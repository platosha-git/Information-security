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
void print_labeled(const char *label, const unsigned char *buff, size_t len);

void read_keys(EVP_PKEY **public_k, EVP_PKEY **private_k);
void write_sign(unsigned char *sign, size_t len, char *filename);
size_t read_sign(unsigned char **sign, char *filename);


#endif // SIGN_H
