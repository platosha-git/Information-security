#include <iostream>

#include "iohandlers.h"
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

string getPlainString()
{
    cout << "From file......1" << endl;
    cout << "From console...2" << endl << endl;

    int chooseStream = 0;
    cin >> chooseStream;

    string plainString = "";
    if (chooseStream == 1) {
        plainString = getFileStr();
    }
    else {
        plainString = getConsoleStr();
    }

    return plainString;
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

            string plainString = getPlainString();
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
