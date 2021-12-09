#include <fstream>
#include <vector>
#include <cstring>
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

void readKeys(EVP_PKEY **publicKey, const string publicFile,
              EVP_PKEY **privateKey, const string privateFile)
{
    readKey(publicKey, publicFile);
    readKey(privateKey, privateFile);
}

void readKey(EVP_PKEY **key, const string filename)
{
    FILE *file = fopen(filename.c_str(), "rt");
    *key = PEM_read_PUBKEY(file, nullptr, nullptr, nullptr);
    fclose(file);
}

size_t readSignature(unsigned char **sign, const string filename)
{
    ifstream file(filename, ios::binary | ios::ate);
    streamsize size = file.tellg();
    file.seekg(0, ios::beg);

    vector<unsigned char> buffer(static_cast<unsigned long>(size));
    file.read(reinterpret_cast<char *>(buffer.data()), size);
    *sign = static_cast<unsigned char *>(malloc(buffer.size()));
    memcpy(*sign, buffer.data(), buffer.size());

    return buffer.size();
}
