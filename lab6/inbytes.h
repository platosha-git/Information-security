#ifndef INBYTES_H
#define INBYTES_H

#include <string>
#include <vector>
#include <fstream>

class InBytes {
public:
    explicit InBytes(const std::string &filename);

    bool readBit();
    unsigned char readByte();
    size_t readSymbol(unsigned char numByte);

    bool isEof();
    void close();

private:
    std::ifstream file;
    std::vector<unsigned char> bits;
    int extra_bits;
};

std::vector<int> getSymbolFrequency(const std::string &filename);

#endif // INBYTES_H
