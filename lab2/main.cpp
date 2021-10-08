#include <iostream>
#include <fstream>
#include "enigma.h"

using namespace std;
const static int numRotors = 3;
const static string fileName = "shifr.bin";

void menu()
{
    cout << "Encrypt message.....1" << endl;
    cout << "Decrypt message.....2" << endl;
    cout << "Exit................3" << endl << endl;
}

void writeToFile(string filename, string cipherString)
{
    ofstream out;
    out.open(filename);
    if (out.is_open()) {
        out << cipherString << endl;
    }
    out.close();
}

string readFromFile(string filename)
{
    string line = "";

    ifstream in;
    in.open(filename);
    if (in.is_open()) {
        getline(in, line);
    }
    in.close();

    return line;
}

int main()
{
    int choose = 0;
    while (choose != 3) {
        menu();
        cin >> choose;

        switch (choose) {
        case 1:
        {
            Enigma enigma(encoder, numRotors);

            string plainString;
            cout << "Input message for encryption: ";
            cin.ignore();
            getline(cin, plainString);

            string cipherString = enigma.encrypt(plainString);

            cout << "Encrypted message: " << cipherString << endl;
            writeToFile(fileName, cipherString);
            break;
        }

        case 2:
        {
            Enigma enigma(decoder, numRotors);

            string fileString = readFromFile(fileName);
            string originalString = enigma.encrypt(fileString);
            cout << "Original message: " << originalString << endl;
            break;
        }

        default:
            choose = 3;
            break;
        }
    }

    return 0;
}
