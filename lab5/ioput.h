#ifndef IOPUT_H
#define IOPUT_H

#include <openssl/evp.h>
#include <openssl/pem.h>
#include <iostream>

void writeKeys(EVP_PKEY *publicKey, const std::string publicFile,
               EVP_PKEY *privateKey, const std::string privateFile);
void writeKey(EVP_PKEY *key, const std::string filename);

void writeSignature(unsigned char *sign, size_t len, const std::string filename);
void outputSignature(const unsigned char *signature, size_t len);

#endif // IOPUT_H
