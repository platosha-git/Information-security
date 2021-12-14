#include "inbytes.h"

using namespace std;

InBytes::InBytes(const string &filename)
{
    file.open(filename, fstream::binary);
    addBits = readByte();
}

bool InBytes::readBit()
{
    if (bits.empty()) {
        unsigned char byte = readByte();
        file.get();

        int endBits = 0;
        if (file.eof()) {
            endBits += addBits;
        }
        else {
            file.unget();
        }

        bool resBit = static_cast<bool>((byte >> 7) & 1);
        for (int i = 6; i >= endBits; i--) {
            bool bit = static_cast<bool>((byte >> i) & 1);
            bits.push_back(bit);
        }

        return resBit;
    }

    bool bit = bits[0];
    bits.erase(bits.begin());

    return bit;
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

vector<int> getFrequency(const string &filename)
{
    ifstream file(filename, ios::binary);
    vector<int> frequency(256, 0);

    while (!file.eof()) {
        unsigned char symbol = file.get();
        frequency[symbol]++;
    }

    file.close();
    return frequency;
}
