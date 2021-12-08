#ifndef RSA_H
#define RSA_H


#include <cmath>

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

#endif // RSA_H
