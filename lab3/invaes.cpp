#include <stdio.h>
#include <iostream>
#include <cstring>
#include <algorithm>

#include "aescoder.h"

using namespace std;

void AEScoder::invSubBytes()
{
    for (int i = 0; i < 16; i++) {
        int row = state[i] / 0x10;
        int col = state[i] % 0x10;
        state[i] = InvSbox[16 * row + col];
    }
}

void AEScoder::invShiftRows()
{
    for (int i = 0; i < 4; i++) {
        int curRow[4] = {state[i], state[4 + i], state[8 + i], state[12 + i]};
        rotate(curRow, curRow + 4 - i, curRow + 4);

        for (int j = 0; j < 4; j++) {
            state[4 * j + i] = curRow[j];
        }
    }
}

void AEScoder::invMixColumns()
{
    for (int i = 0; i < 4; i++) {
        unsigned char curCol[4];
        for (int j = 0; j < 4; j++) {
            curCol[j] = state[j + 4 * i];
        }

        state[4 * i + 0] = gMul(curCol[0], 14) ^ gMul(curCol[3], 9) ^ gMul(curCol[2], 13) ^ gMul(curCol[1], 11);
        state[4 * i + 1] = gMul(curCol[1], 14) ^ gMul(curCol[0], 9) ^ gMul(curCol[3], 13) ^ gMul(curCol[2], 11);
        state[4 * i + 2] = gMul(curCol[2], 14) ^ gMul(curCol[1], 9) ^ gMul(curCol[0], 13) ^ gMul(curCol[3], 11);
        state[4 * i + 3] = gMul(curCol[3], 14) ^ gMul(curCol[2], 9) ^ gMul(curCol[1], 13) ^ gMul(curCol[0], 11);
    }
}

unsigned char AEScoder::gMul(unsigned char a, unsigned char b)
{
    unsigned char res = 0;
    for (unsigned char counter = 0; counter < 8; counter++) {
        if ((b & 1) == 1) {
            res ^= a;
        }

        unsigned char h = static_cast<unsigned char>(a & 0x80);
        a <<= 1;

        if (h == 0x80) {
            a ^= 0x1b;
        }

        b >>= 1;
    }

    return res;
}
