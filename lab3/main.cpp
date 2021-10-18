#include <iostream>
#include <fstream>

#include "aescoder.h"

using namespace std;

const static string inputFile = "/home/platosha/Desktop/BMSTU/7sem/Information-security/lab3/in.txt";
const static string outputFile = "/home/platosha/Desktop/BMSTU/7sem/Information-security/lab3/out.txt";

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
            out << message[i] << endl;
        }
    }
    out.close();
}

int main()
{
    string message[maxLines];
    int numLines = 0;

    getMessage(message, numLines);

    AEScoder coder;
    for (int i = 0; i < numLines; i++) {
        coder.encode(message[i]);
    }

    writeMessage(message, numLines);

    return 0;
}
