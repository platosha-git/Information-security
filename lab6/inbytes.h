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
    std::vector<int> readFrequency();

    bool isEof();
    void close();

private:
    std::ifstream file;
    std::vector<unsigned char> bits;
    int addBits;
};

std::vector<int> getFrequency(const std::string &filename);

#endif // INBYTES_H
