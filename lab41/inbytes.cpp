#include "inbytes.h"

using namespace std;

InBytes::InBytes(const string &filename)
{
    file.open(filename, fstream::binary);
    readByte();
}

unsigned char InBytes::readByte()
{
    if (file.eof()) {
        throw logic_error("eof");
    }

    unsigned char byte = static_cast<unsigned char>(file.get());
    return byte;
}

size_t InBytes::readSymbol(unsigned char numBytes)
{
    size_t number = 0;
    for (int i = 0; i < numBytes; i++) {
        number <<= 8;
        unsigned char byte = readByte();
        number |= byte;
    }
    return number;
}

bool InBytes::isEof()
{
    file.get();
    if (file.eof()) {
        file.unget();
        return true;
    }
    file.unget();
    return false;
}

void InBytes::close()
{
    file.close();
}

string getMessage(const std::string filename)
{
    string message = "";
    ifstream inp(filename, std::fstream::binary);

    while (!inp.eof()) {
        char symbol = inp.get();
        if (symbol < 0) {
            break;
        }
        message += symbol;
    }
    inp.close();

    return message;
}
