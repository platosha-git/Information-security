#include <fstream>
#include <iostream>
#include "outbytes.h"
#include "inbytes.h"
#include "rsagenerator.h"
#include "rsa.h"

using namespace std;

const string publicFilename = "/home/platosha/Desktop/BMSTU/7sem/Information-security/lab41/public.key";
const string privateFilename = "/home/platosha/Desktop/BMSTU/7sem/Information-security/lab41/private.key";

const string inputFilename = "/home/platosha/Desktop/BMSTU/7sem/Information-security/lab41/input";
const string encodeFilename = "/home/platosha/Desktop/BMSTU/7sem/Information-security/lab41/encode";
const string decodeFilename = "/home/platosha/Desktop/BMSTU/7sem/Information-security/lab41/decode";

unsigned char getNumBytes(unsigned int n)
{
    double numBits = ceil(log2(static_cast<double>(n)));
    double numBytes = ceil(numBits / 8);
    return static_cast<unsigned char>(numBytes);
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
            unsigned char numBytes = getNumBytes(publicKey[1]);

            string message = getMessage(inputFilename);
            OutBytes otp(encodeFilename);

            for (char& symbol : message) {
                unsigned int enSymbol = rsa.encode(static_cast<unsigned char>(symbol));
                otp.writeSymbol(enSymbol, numBytes);
            }

            otp.close();
            break;
        }
        case 3:
        {
            vector<unsigned int> privateKey = readKey(privateFilename);
            rsa.initPrivateKey(privateKey);
            unsigned char numBytes = getNumBytes(privateKey[1]);

            InBytes inp(encodeFilename);
            ofstream otp(decodeFilename, fstream::binary);

            while (!inp.isEof()) {
                size_t symbol = inp.readSymbol(numBytes);
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
