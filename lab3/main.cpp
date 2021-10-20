#include <iostream>
#include <fstream>
#include <sstream>

#include "aescoder.h"

using namespace std;

const static string inputFile = "/home/platosha/Desktop/BMSTU/7sem/Information-security/lab3/in.txt";
const static string outputFile = "/home/platosha/Desktop/BMSTU/7sem/Information-security/lab3/out.txt";

const string key = "rf6GeQysVk1390Po";

void getMessage(string &message)
{
    std::ifstream in(inputFile);
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

void writeMessage(string message)
{
    ofstream out(outputFile);
    if (out.is_open()) {
        out << message;
        out.close();
    }
}

int main()
{
    string message = "";
    getMessage(message);

    AEScoder coder(key);
    coder.decode(message);

    writeMessage(message);
    cout << message << endl;
    cout << "Message was written to the file!\n\n";

    return 0;
}
