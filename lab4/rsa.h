#ifndef RSA_H
#define RSA_H

#include <cmath>
#include <iostream>
#include <vector>
#include <climits>

class RSA {
public:
    explicit RSA() = default;

    void set_open_key(unsigned int e, unsigned int n);
    void set_private_key(unsigned int d, unsigned int n);

    std::vector<unsigned int> encode(const std::vector<unsigned int> &data, std::vector<unsigned int> key);
    std::vector<unsigned int> decode(const std::vector<unsigned int> &data, std::vector<unsigned int> key);

private:
    unsigned int e{};
    unsigned int d{};
    unsigned int n{};

    unsigned int binpow(unsigned int a, unsigned int e, unsigned int mod);
    unsigned int getChunkSize(std::vector<unsigned int> key);
};


std::vector<unsigned int> resize(const std::vector<unsigned int> &data, unsigned int in_size, unsigned int out_size);

#endif // RSA_H
