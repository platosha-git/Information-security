#include <iostream>
#include <fstream>
#include <vector>
#include "sign.h"

using namespace std;

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
    EVP_PKEY *skey = nullptr, *vkey = nullptr;
    byte *sig = nullptr;
    size_t slen = 0;

    int choose = 0;
    while (choose != 3) {
        menu();
        cin >> choose;

        switch (choose) {
        case 1:
        {
            make_keys(&skey, &vkey);
            write_keys(skey, vkey);

            std::ifstream file(documentFilename, std::ios::binary | std::ios::ate);
            std::streamsize size = file.tellg();
            file.seekg(0, std::ios::beg);

            std::vector<unsigned char> buffer(static_cast<unsigned long>(size));
            file.read(reinterpret_cast<char *>(buffer.data()), size);

            sign(buffer.data(), buffer.size(), &sig, &slen, skey);
            write_sign(sig, slen, "/home/platosha/Desktop/BMSTU/7sem/Information-security/lab5/output");
            printf("Created signature\n");
            print_labeled("Signature", sig, slen);
            break;
        }
        case 2:
        {
            read_keys(&skey, &vkey);
            slen = read_sign(&sig, "/home/platosha/Desktop/BMSTU/7sem/Information-security/lab5/output");

            std::ifstream file(documentFilename, std::ios::binary | std::ios::ate);
            std::streamsize size = file.tellg();
            file.seekg(0, std::ios::beg);

            std::vector<unsigned char> buffer(static_cast<unsigned long>(size));
            file.read(reinterpret_cast<char *>(buffer.data()), size);

            auto rc = verify(buffer.data(), buffer.size(), sig, slen, vkey);
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

    OPENSSL_free(sig);
    EVP_PKEY_free(skey);
    EVP_PKEY_free(vkey);

    return 0;
}
