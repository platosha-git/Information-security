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
    void writeNumber(size_t number, unsigned char byte);

    void close();

private:
    std::vector<bool> bits;
    std::ofstream file;

    void flush();
};

#endif // OUTBYTES_H
