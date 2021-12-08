#ifndef INBYTES_H
#define INBYTES_H

#include <string>
#include <vector>
#include <fstream>

class InBytes {
public:
    explicit InBytes(const std::string &filename);

    unsigned char readBit();
    unsigned char readByte();
    size_t getNumBytes(unsigned char byte);

    bool isEof();
    void close();

private:
    std::ifstream file;
    std::vector<unsigned char> bits;
    int addBits;
};

std::string getMessage(const std::string filename);

#endif // INBYTES_H
