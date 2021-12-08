#include <fstream>
#include <iostream>
#include "bitofile.h"
#include "bitifile.h"
#include "rsagenerator.h"
#include "rsa.h"

using namespace std;

const string publicFilename = "/home/platosha/Desktop/BMSTU/7sem/Information-security/lab41/public.key";
const string privateFilename = "/home/platosha/Desktop/BMSTU/7sem/Information-security/lab41/private.key";

const string inputFilename = "/home/platosha/Desktop/BMSTU/7sem/Information-security/lab41/input";
const string encodeFilename = "/home/platosha/Desktop/BMSTU/7sem/Information-security/lab41/encode";
const string decodeFilename = "/home/platosha/Desktop/BMSTU/7sem/Information-security/lab41/decode";

unsigned char bytes_per_int(unsigned int n) {
    auto bits_per_freq = ceil(log2(static_cast<double>(n)));
    auto bytes_per_freq = ceil(bits_per_freq / 8);
    return static_cast<unsigned char>(bytes_per_freq);
}

void writeKey(const vector<unsigned int> key, const string filename)
{
    ofstream out(filename);
    if (out.is_open()) {
        out << key[0] << " " << key[1];
        out.close();
    }

    cout << key[0] << " " << key[1] << endl;
    cout << "Key was written to the file!\n\n";
}

vector<unsigned int> readKey(const string filename)
{
    vector<unsigned int> key(2, 0);
    ifstream in(filename);
    if (in.is_open()) {
        in >> key[0] >> key[1];
        in.close();
    }

    return key;
}

void menu()
{
    cout << "Genereate keys......1" << endl;
    cout << "Encode message......2" << endl;
    cout << "Decode message......3" << endl;
    cout << "Exit................4" << endl;
}

int main(void)
{
    int choose = 0;
    RSA rsa;

    while (choose != 4) {
        menu();
        cin >> choose;

        switch(choose) {
        case 1:
        {
            RSAGenerator generator;
            Keys keys = generator.getKeys();
            writeKey(keys.PublicKey, "public.key");
            writeKey(keys.PrivateKey, "private.key");
            break;
        }
        case 2:
        {
            vector<unsigned int> publicKey = readKey(publicFilename);
            rsa.initPublicKey(publicKey);
            unsigned char bytes = bytes_per_int(publicKey[1]);

            ifstream inp(inputFilename, std::fstream::binary);
            BitOFile otp(encodeFilename);

            while (!inp.eof()) {
                char symbol = inp.get();
                if (symbol < 0) {
                    break;
                }
                unsigned int enSymbol = rsa.encode(static_cast<unsigned char>(symbol));
                otp.write_number(enSymbol, bytes);
            }

            inp.close();
            otp.close();
            break;
        }
        case 3:
        {
            vector<unsigned int> privateKey = readKey(privateFilename);
            rsa.initPrivateKey(privateKey);
            unsigned char bytes = bytes_per_int(privateKey[1]);

            BitIFile inp(encodeFilename);
            std::ofstream otp(decodeFilename, std::fstream::binary);

            while (!inp.eof()) {
                size_t symbol = inp.read_number(bytes);
                unsigned char deSymbol = rsa.decode(symbol);
                otp.put(deSymbol);
            }

            inp.close();
            otp.close();
            break;
        }
        default:
            break;
        }
    }

    return 0;
}
