#include <iostream>
#include <fstream>

#include "rsagenerator.h"

using namespace std;

void menu()
{
    cout << "Genereate keys......1" << endl;
    cout << "Encode message......2" << endl;
    cout << "Decode message......3" << endl;
    cout << "Exit................4" << endl;
}

void writeMessage(const string message, const string filename)
{
    ofstream out(filename);
    if (out.is_open()) {
        out << message;
        out.close();
    }

    cout << message << endl;
    cout << "Message was written to the file!\n\n";
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
            std::ofstream file("/home/platosha/Desktop/BMSTU/7sem/Information-security/lab4/public.key");
            file << keys.PublicKey[0] << " " << keys.PublicKey[1];
            std::ofstream private_file("/home/platosha/Desktop/BMSTU/7sem/Information-security/lab4/private.key");
            private_file << keys.PrivateKey[0] << " " << keys.PrivateKey[1];
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
