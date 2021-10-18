#ifndef AESCODER_H
#define AESCODER_H

#include <iostream>
#include "tables.h"

class AEScoder
{
public:
    void encode(std::string &message);

private:
    const static int Nb = 4;
    const static int Nk = 4;
    const static int Nr = 10;

    void blockEncode(unsigned char (&block)[16]);

    void addRoundKey(int keyNumber);
    void subBytes();
    void shiftRows();

    unsigned char state[16];
};

#endif // AESCODER_H
