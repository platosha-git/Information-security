#include <iostream>
#include <fstream>

#include "rsagenerator.h"

using namespace std;

const string publicFilename = "/home/platosha/Desktop/BMSTU/7sem/Information-security/lab4/public.key";
const string privateFilename = "/home/platosha/Desktop/BMSTU/7sem/Information-security/lab4/private.key";

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
        /*case 2:
            getMessage(message, encodeFile);
            coder.encode(message);
            writeMessage(message, decodeFile);
            break;
        case 3:
            getMessage(message, decodeFile);
            coder.decode(message);
            writeMessage(message, encodeFile);
            break;
        */
        default:
            break;
        }
    }

    return 0;
}
