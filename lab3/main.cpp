#include <iostream>
#include <fstream>
#include <sstream>

#include "aescoder.h"

using namespace std;

const static string inputFile = "/home/platosha/Desktop/BMSTU/7sem/Information-security/lab3/in.txt";
const static string outputFile = "/home/platosha/Desktop/BMSTU/7sem/Information-security/lab3/out.txt";

const string key = "rf6GeQysVk1390Po";
const int maxLines = 15;

void getMessage(string (&message)[maxLines], int &numLines)
{
    string line = "";

    ifstream in(inputFile);
    if (in.is_open()) {
        int i = 0;
        while (getline(in, line) && i < maxLines) {
            message[i] = line;
            i++;
        }
        numLines = i;
    }
    in.close();
}

void writeMessage(string message[maxLines], int numLines)
{
    ofstream out(outputFile);
    if (out.is_open()) {
        for (int i = 0; i < numLines; i++) {
            out << message[i];
        }
    }
    out.close();
}

int main()
{
    string message[maxLines];
    int numLines = 0;

    //getMessage(message, numLines);
    std::ifstream t(inputFile);
    std::stringstream buffer;
    buffer << t.rdbuf();
    auto data = buffer.str();

    AEScoder coder(key);
    //for (int i = 0; i < numLines; i++) {
        coder.decode(data);
    //}

    //writeMessage(data, 1);
    std::ofstream output(outputFile);
    output << data;
    cout << "Message was written to the file!\n\n";

    return 0;
}
