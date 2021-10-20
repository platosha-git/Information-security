#ifndef AESCODER_H
#define AESCODER_H

#include <iostream>
#include <array>
#include "tables.h"

class AEScoder
{
public:
    AEScoder(std::string key);
    void encode(std::string &message);
    void decode(std::string &message);

private:
    const static int Nb = 4;
    const static int Nk = 4;
    const static int Nr = 10;

    void keyExpansion();
    void subWord(unsigned char (&word)[4]);
    void xorWords(const unsigned char w1[4], const unsigned char w2[4], unsigned char (&res)[4]);

    void blockEncode();
    void blockDecode();

    void addRoundKey(const int keyNumber);
    void subBytes();
    void shiftRows();
    void mixColumns();
    unsigned char gMul(unsigned char a, unsigned char kf);


    unsigned char state[16];
    unsigned char key[4 * Nk];
    unsigned char roundKey[Nb * (Nr + 1)][4];
};

#endif // AESCODER_H
