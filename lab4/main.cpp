#include <iostream>
#include <fstream>
#include <sstream>

#include "iobytes.h"
#include "rsagenerator.h"
#include "rsa.h"

using namespace std;

const string publicFilename = "/home/platosha/Desktop/BMSTU/7sem/Information-security/lab4/public.key";
const string privateFilename = "/home/platosha/Desktop/BMSTU/7sem/Information-security/lab4/private.key";

const string inputFilename = "/home/platosha/Desktop/BMSTU/7sem/Information-security/lab4/input";
const string encodeFilename = "/home/platosha/Desktop/BMSTU/7sem/Information-security/lab4/encode";
const string decodeFilename = "/home/platosha/Desktop/BMSTU/7sem/Information-security/lab4/decode";

void menu()
{
    cout << "Genereate keys......1" << endl;
    cout << "Encode message......2" << endl;
    cout << "Decode message......3" << endl;
    cout << "Exit................4" << endl;
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

int main()
{
    int choose = 0;
    while (choose != 4) {
        menu();
        cin >> choose;

        switch(choose) {
        case 1:
        {
            RSAGenerator generator;
            Keys keys = generator.getKeys();
            writeKey(keys.PublicKey, publicFilename);
            writeKey(keys.PrivateKey, privateFilename);
            break;
        }
        case 2:
        {
            uint64_t e = 7, m = 5;
            vector<unsigned int> message = readBytes(inputFilename);
            vector<unsigned int> enMessage = process_bytes(message, {e, m}, true);
            writeBytes(encodeFilename, enMessage);
            cout << "Done." << endl;

            break;
        }
        case 3:
        {
            uint64_t e = 7, m = 5;
            vector<unsigned int> in = readBytes(encodeFilename);
            vector<unsigned int> deMessage = process_bytes(in, {e, m}, false);
            writeBytes(decodeFilename, deMessage);
            cout << "Done." << endl;
            break;
        }
        default:
            break;
        }
    }

    return 0;
}
