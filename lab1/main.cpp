#include <iostream>
#include "LinuxInfo.h"

using namespace std;

const static string fileName = "licenseKey.txt";

bool accessCheck()
{
    size_t key = getHashKey();

    string line = "";
    ifstream in(fileName);
    if (in.is_open()) {
        getline(in, line);
    }
    in.close();

    if (line != "" && key == stoull(line)) {
        return true;
    }

    return false;
}

int main()
{
    bool isAvailable = accessCheck();

    if (isAvailable) {
        system("./program");
    }
    else {
        std::cout << "The programm is not available!" << std::endl;
    }

    return 0;
}