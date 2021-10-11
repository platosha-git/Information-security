#include <iostream>
#include <fstream>
#include <string>

#include "iohandlers.h"

using namespace std;
const static string inFilename = "/home/platosha/Desktop/BMSTU/7sem/Information-security/lab2/message.txt";

string getConsoleStr()
{
    string str = "";
    cout << "Input message for encryption: ";
    cin.ignore();
    getline(cin, str);

    return str;
}

string getFileStr()
{
    string line;

    ifstream in(inFilename);
    if (in.is_open()) {
        getline(in, line);
    }

    in.close();

    cout << "line: " << line << endl;
    return line;
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
