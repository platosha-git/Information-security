#ifndef OUTBYTES_H
#define OUTBYTES_H

#include <fstream>
#include <vector>
#include <string>

class OutBytes {
public:
    explicit OutBytes(const std::string &filename);

    void writeBit(unsigned char bit);
    void writeByte(unsigned char byte);
    void writeNumber(unsigned int number, unsigned char numBytes);

    void close();

private:
    std::vector<unsigned char> bits;
    std::ofstream file;

    void flush();
};

#endif // OUTBYTES_H
