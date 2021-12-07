#ifndef RSA_H
#define RSA_H

#include <cmath>
#include <iostream>
#include <vector>
#include <climits>

class RSA {
public:
    std::vector<unsigned int> encode(const std::vector<unsigned int> &data, std::vector<unsigned int> key);
    std::vector<unsigned int> decode(const std::vector<unsigned int> &data, std::vector<unsigned int> key);

private:
    unsigned int binpow(unsigned int a, unsigned int e, unsigned int mod);
    unsigned int getChunkSize(std::vector<unsigned int> key);
    std::vector<unsigned int> resize(const std::vector<unsigned int> &data, unsigned int size, unsigned int newSize);
};

#endif // RSA_H
