#ifndef IOPUT_H
#define IOPUT_H

#include <openssl/evp.h>
#include <openssl/pem.h>
#include <iostream>

void writeKeys(EVP_PKEY *publicKey, const std::string publicFile,
               EVP_PKEY *privateKey, const std::string privateFile);
void writeKey(EVP_PKEY *key, const std::string filename);

#endif // IOPUT_H
