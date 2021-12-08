#include "ioput.h"

using namespace std;

void writeKeys(EVP_PKEY *publicKey, const string publicFile,
               EVP_PKEY *privateKey, const string privateFile)
{
    writeKey(publicKey, publicFile);
    writeKey(privateKey, privateFile);
}

void writeKey(EVP_PKEY *key, const string filename)
{
    FILE *file = fopen(filename.c_str(), "wt");
    PEM_write_PUBKEY(file, key);
    fclose(file);
}
