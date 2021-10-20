#include <stdio.h>
#include <iostream>
#include <cstring>
#include <algorithm>

#include "aescoder.h"

using namespace std;

void AEScoder::keyExpansion()
{
    for (int i = 0; i < Nk; i++) {
        unsigned char tmp[4] = {key[4 * i], key[4 * i + 1], key[4 * i + 2], key[4 * i + 3]};
        memcpy(roundKey[i], tmp, 4);
    }

    for (int i = Nk; i < Nb * (Nr + 1); i++) {
        unsigned char tmp[4];
        memcpy(tmp, roundKey[i - 1], 4);

        if (i % Nk == 0) {
            rotate(tmp, tmp + 1, tmp + 4);
            subWord(tmp);
            xorWords(tmp, Rcon[i / Nk], tmp);
        }
        else if (Nk > 6 && i % Nk == 4) {
            subWord(tmp);
        }

        xorWords(roundKey[i - Nk], tmp, roundKey[i]);
    }
}

void AEScoder::subWord(unsigned char (&word)[4])
{
    for (int i = 0; i < 4; i++) {
        int row = word[i] / 0x10;
        int col = word[i] % 0x10;
        word[i] = Sbox[16 * row + col];
    }
}

void AEScoder::xorWords(const unsigned char w1[4], const unsigned char w2[4], unsigned char (&res)[4])
{
    for (int i = 0; i < 4; i++) {
        res[i] = w1[i] ^ w2[i];
    }
}

void AEScoder::addRoundKey(const int keyNumber)
{
    for (int i = 0; i < 4; i++) {
        for  (int j = 0; j < 4; j++) {
            state[4 * i + j] ^= roundKey[keyNumber * 4 + i][j];
        }
    }
}

void AEScoder::subBytes()
{
    for (int i = 0; i < 16; i++) {
        int oldState = state[i];
        state[i] = Sbox[oldState];
    }
}

void AEScoder::shiftRows()
{
    for (int i = 0; i < 4; i++) {
        int curRow[4] = {state[i], state[4 + i], state[8 + i], state[12 + i]};
        rotate(curRow, curRow + i, curRow + 4);

        for (int j = 0; j < 4; j++) {
            state[4 * j + i] = curRow[j];
        }
    }
}

void AEScoder::mixColumns()
{
    for (int i = 0; i < 4; i++) {
        unsigned char curCol[4];
        for (int j = 0; j < 4; j++) {
            curCol[j] = state[j + 4 * i];
        }

        unsigned char a[4];
        memcpy(a, curCol, 4);

        curCol[0] = gMul(a[0], 2) ^ gMul(a[3], 1) ^ gMul(a[2], 1) ^ gMul(a[1], 3);
        curCol[1] = gMul(a[1], 2) ^ gMul(a[0], 1) ^ gMul(a[3], 1) ^ gMul(a[2], 3);
        curCol[2] = gMul(a[2], 2) ^ gMul(a[1], 1) ^ gMul(a[0], 1) ^ gMul(a[3], 3);
        curCol[3] = gMul(a[3], 2) ^ gMul(a[2], 1) ^ gMul(a[1], 1) ^ gMul(a[0], 3);

        for (int j = 0; j < 4; j++) {
            state[j + 4 * i] = curCol[j];
        }
    }
}

unsigned char AEScoder::gMul(unsigned char a, unsigned char kf)
{
    unsigned char res = 0, hi_bit_set = 0;

    for (unsigned char counter = 0; counter < 8; counter++) {
        if ((kf & 1) == 1) {
            res ^= a;
        }

        hi_bit_set = static_cast<unsigned char>(a & 0x80);
        a <<= 1;

        if (hi_bit_set == 0x80) {
            a ^= 0x1b;
        }

        kf >>= 1;
    }

    return res;
}


