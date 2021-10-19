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

private:
    const static int Nb = 4;
    const static int Nk = 4;
    const static int Nr = 10;

    void keyExpansion();
    void subWord(unsigned char (&word)[4]);
    void xorWords(const unsigned char w1[4], const unsigned char w2[4], unsigned char (&res)[4]);

    void blockEncode();

    void addRoundKey(int keyNumber);
    void subBytes();
    void shiftRows();

    void output(unsigned char *tbl, const int size);

    unsigned char state[16];
    unsigned char key[4 * Nk];
    unsigned char roundKeys[Nb * (Nr + 1)][4];
};

#endif // AESCODER_H
