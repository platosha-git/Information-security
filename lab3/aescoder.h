#ifndef AESCODER_H
#define AESCODER_H

#include <iostream>
#include "tables.h"

class AEScoder
{
public:
    AEScoder(std::string message[maxLines], int numLines);
    //ShiftRows();

private:
    const static int Nb = 4;
    const static int Nk = 4;
    const static int Nr = 10;

    std::string message[maxLines];
    int numLines;
};

#endif // AESCODER_H
