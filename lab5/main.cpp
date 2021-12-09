#include <iostream>
#include <fstream>
#include <vector>

#include "sign.h"
#include "ioput.h"

using namespace std;

const string privateFilename = "/home/platosha/Desktop/BMSTU/7sem/Information-security/lab5/private.key";
const string publicFilename = "/home/platosha/Desktop/BMSTU/7sem/Information-security/lab5/public.key";

const string documentFilename = "/home/platosha/Desktop/BMSTU/7sem/Information-security/lab5/document";
const string signatureFilename = "/home/platosha/Desktop/BMSTU/7sem/Information-security/lab5/signature";

void menu()
{
    cout << "Sign document........1" << endl;
    cout << "Verify signature.....2" << endl;
    cout << "Exit.................3" << endl;
}

int main(void)
{
    OpenSSL_add_all_algorithms();

    EVP_PKEY *publicKey = EVP_PKEY_new();
    EVP_PKEY *privateKey = EVP_PKEY_new();

    unsigned char *signature = nullptr;
    size_t sigLen = 0;

    int choose = 0;
    while (choose != 3) {
        menu();
        cin >> choose;

        switch (choose) {
        case 1:
        {
            generateKeys(publicKey, privateKey);
            writeKeys(publicKey, publicFilename, privateKey, privateFilename);

            ifstream file(documentFilename, ios::binary | ios::ate);
            streamsize size = file.tellg();
            file.seekg(0, ios::beg);

            vector<unsigned char> buffer(static_cast<unsigned long>(size));
            file.read(reinterpret_cast<char *>(buffer.data()), size);

            sign(buffer.data(), buffer.size(), &signature, &sigLen, privateKey);

            writeSignature(signature, sigLen, signatureFilename);
            cout << "Document was signed!" << endl << endl;
            break;
        }
        case 2:
        {
            readKeys(&publicKey, publicFilename, &privateKey, privateFilename);
            sigLen = readSignature(&signature, signatureFilename);

            ifstream file(documentFilename, ios::binary | ios::ate);
            streamsize size = file.tellg();
            file.seekg(0, ios::beg);

            vector<unsigned char> buffer(static_cast<unsigned long>(size));
            file.read(reinterpret_cast<char *>(buffer.data()), size);

            int rc = verify(buffer.data(), buffer.size(), signature, sigLen, privateKey);
            if (rc == 0) {
                printf("Verified signature\n\n");
            } else {
                printf("Failed to verify signature, return code %d\n", rc);
            }
            break;
        }
        default:
            break;
        }
    }

    OPENSSL_free(signature);
    EVP_PKEY_free(publicKey);
    EVP_PKEY_free(privateKey);

    return 0;
}
