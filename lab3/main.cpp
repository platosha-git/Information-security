#include <iostream>
#include <fstream>
#include <sstream>

#include "aescoder.h"

using namespace std;

const static string encodeFile = "/home/platosha/Desktop/BMSTU/7sem/Information-security/lab3/encode.txt";
const static string decodeFile = "/home/platosha/Desktop/BMSTU/7sem/Information-security/lab3/decode.txt";

const string key = "rf6GeQysVk1390Po";

void menu()
{
    cout << "Encode message......1" << endl;
    cout << "Decode message......2" << endl;
    cout << "Exit................3" << endl;
}

void getMessage(string &message, const string filename)
{
    std::ifstream in(filename);
    if (in.is_open()) {
        std::stringstream buffer;
        buffer << in.rdbuf();

        auto line = buffer.str();
        int len = line.size();

        for (int i = 0; i < len; i++) {
            message += line[i];
        }

        in.close();
    }
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
    while (choose != 3) {
        menu();
        cin >> choose;

        string message = "";
        AEScoder coder(key);

        switch(choose) {
        case 1:
            getMessage(message, encodeFile);
            coder.encode(message);
            writeMessage(message, decodeFile);
            break;
        case 2:
            getMessage(message, decodeFile);
            coder.decode(message);
            writeMessage(message, encodeFile);
            break;
        default:
            break;
        }
    }

    return 0;
}
