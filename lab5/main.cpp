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

            vector<unsigned char> document = readDocument(documentFilename);
            sign(document.data(), document.size(), &signature, &sigLen, privateKey);
            writeSignature(signature, sigLen, signatureFilename);

            cout << "Document was signed!" << endl << endl;
            break;
        }
        case 2:
        {
            readKeys(&publicKey, publicFilename, &privateKey, privateFilename);
            sigLen = readSignature(&signature, signatureFilename);
            vector<unsigned char> document = readDocument(documentFilename);

            int exitCode = verify(document.data(), document.size(), signature, sigLen, publicKey);
            if (exitCode == 0) {
                cout << "Verified signature" << endl << endl;
            }
            else {
                cout << "Failed to verify signature, return code " << exitCode << endl << endl;
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
