#ifndef RSA_H
#define RSA_H

#include <cmath>
#include <iostream>
#include <vector>
#include <climits>

typedef struct {
    uint64_t e;
    uint64_t m;
} key;

class RSA {
public:
    explicit RSA() = default;;

    void set_open_key(unsigned int e, unsigned int n);
    void set_private_key(unsigned int d, unsigned int n);
    unsigned int encode(unsigned char symbol);
    unsigned char decode(unsigned int symbol);

private:
    unsigned int e{};
    unsigned int d{};
    unsigned int n{};

    unsigned int binpow(unsigned int a, unsigned int n, unsigned int m);
};

std::vector<uint8_t> process_bytes(const std::vector<uint8_t> &data, key k, bool encrypt);
uint8_t get_chunk_size(key k);
std::vector<uint64_t> resize(const std::vector<uint64_t> &data, uint8_t in_size, uint8_t out_size);
uint64_t binpow(uint64_t a, uint64_t e, uint64_t mod = LLONG_MAX);
uint64_t sqr(uint64_t x);

#endif // RSA_H
