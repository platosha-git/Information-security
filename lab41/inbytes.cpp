#include "inbytes.h"

using namespace std;

InBytes::InBytes(const string &filename)
{
    file.open(filename, fstream::binary);
    addBits = readByte();
}

unsigned char InBytes::readByte()
{
    if (file.eof()) {
        throw logic_error("eof");
    }

    unsigned char byte = static_cast<unsigned char>(file.get());
    return byte;
}

size_t InBytes::getNumBytes(unsigned char byte_n)
{
    size_t number = 0;
    for (int i = 0; i < byte_n; i++) {
        number <<= 8;
        unsigned char byte = readByte();
        number |= byte;
    }
    return number;
}

unsigned char InBytes::readBit()
{
    if (bits.empty()) {
        auto byte = readByte();
        // check the end of the file
        file.get();

        int end_bit_n = 0;
        if (file.eof()) {
            end_bit_n += addBits;
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

bool InBytes::isEof() {
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

