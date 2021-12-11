#ifndef RSA_H
#define RSA_H

#include <vector>

class RSA {
public:
    void initPublicKey(std::vector<unsigned int> publicKey);
    void initPrivateKey(std::vector<unsigned int> privateKey);

    unsigned int encode(unsigned char symbol);
    unsigned char decode(unsigned int symbol);

private:
    unsigned int e;
    unsigned int d;
    unsigned int n;

    unsigned int binpow(unsigned int a, unsigned int n, unsigned int mod);
};

#endif // RSA_H
