#include "inbytes.h"

using namespace std;

InBytes::InBytes(const string &filename)
{
    file.open(filename, fstream::binary);
    extra_bits = readByte();
}

bool InBytes::readBit() {
    if (bits.empty()) {
        auto byte = readByte();
        // check the end of the file
        file.get();

        int end_bit_n = 0;
        if (file.eof()) {
            end_bit_n += extra_bits;
        } else {
            file.unget();
        }

        auto result_bit = static_cast<bool>((byte >> 7) & 1);
        for (auto i = 6; i >= end_bit_n; i--) {
            auto bit = static_cast<bool>((byte >> i) & 1);
            bits.push_back(bit);
        }

        return result_bit;
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

// Считаем частоту для каждого символа в файле
vector<int> getSymbolFrequency(const string &filename)
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

