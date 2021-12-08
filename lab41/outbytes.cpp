#include "outbytes.h"

using namespace std;

OutBytes::OutBytes(const string &filename)
{
    file.open(filename, fstream::binary);
    file.put(0);
}

void OutBytes::writeBit(unsigned char bit)
{
    bits.push_back(bit);
    if (bits.size() >= 8) {
        flush();
    }
}

void OutBytes::flush()
{
    unsigned char byte = 0;

    for (int i = 0; i < 8; i++) {
        byte <<= 1;
        byte |= bits[i];
    }
    bits.erase(bits.begin(), bits.begin() + 8);

    file.put(byte);
}

void OutBytes::writeByte(unsigned char byte)
{
    if (bits.empty()) {
        file.put(byte);
    }
    else {
        for (int i = 0; i < 8; i++) {
            unsigned char bit = byte & 1;
            bits.push_back(bit);
            byte >>= 1;
        }
        flush();
    }
}

void OutBytes::close()
{
    if (!bits.empty()) {
        unsigned char addBits = 8 - bits.size();
        for (int i = 0; i < addBits; i++) {
            bits.push_back(1);
        }
        flush();

        file.seekp(0);
        file.put(addBits);
    }

    file.close();
}

void OutBytes::writeNumber(size_t number, unsigned char byte)
{
    vector<unsigned char> bits;
    while (number > 0) {
        unsigned char bit = static_cast<bool>(number & 1);
        bits.push_back(bit);
        number >>= 1;
    }

    size_t zeroes = byte * 8 - bits.size();
    for (size_t i = 0; i < zeroes; i++) {
        writeBit(false);
    }

    int size = static_cast<int>(bits.size());
    for (int i = size - 1; i >= 0; i--) {
        writeBit(bits[i]);
    }
}
