#include <fstream>
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

void writeSignature(unsigned char *sign, size_t len, const string filename)
{
    ofstream file(filename);
    if (file.is_open()) {
        for (size_t i = 0; i < len; i++) {
            file.put(static_cast<char>(sign[i]));
        }
        file.close();

        outputSignature(sign, len);
    }
}

void outputSignature(const unsigned char *signature, size_t len)
{
    if (!signature || !len) {
        return;
    }

    cout << "Generated signature: ";
    for (size_t i = 0; i < len; ++i) {
        printf("%02X", signature[i]);
    }
    cout << endl;
}
