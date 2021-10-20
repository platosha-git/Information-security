#include <stdio.h>
#include <iostream>
#include <cstring>
#include <algorithm>

#include "aescoder.h"

using namespace std;

void AEScoder::keyExpansion()
{
    for (int i = 0; i < Nk; i++) {
        unsigned char word[4] = {key[4 * i], key[4 * i + 1], key[4 * i + 2], key[4 * i + 3]};
        memcpy(roundKey[i], word, 4);
    }

    for (int i = Nk; i < Nb * (Nr + 1); i++) {
        unsigned char curRow[4];
        memcpy(curRow, roundKey[i - 1], 4);

        if (i % Nk == 0) {
            rotate(curRow, curRow + 1, curRow + 4);
            subWord(curRow);
            xorWords(curRow, Rcon[i / Nk], curRow);
        }
        else if (Nk > 6 && i % Nk == 4) {
            subWord(curRow);
        }

        xorWords(roundKey[i - Nk], curRow, roundKey[i]);
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
            state[4 * i + j] ^= roundKey[4 * keyNumber + i][j];
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

        ///////////////////////////////
        unsigned char a[4], b[4];
        for (unsigned char c = 0; c < 4; c++) {
            a[c] = curCol[c];
            unsigned char h = (unsigned char)((signed char)curCol[c] >> 7);
            b[c] = curCol[c] << 1;
            b[c] ^= 0x1B & h;
        }
        ////////////////////////////////

        state[i * 4 + 0] = b[0] ^ a[3] ^ a[2] ^ b[1] ^ a[1];    // 2a0 + a3 + a2 + 3a1
        state[i * 4 + 1] = b[1] ^ a[0] ^ a[3] ^ b[2] ^ a[2];    // 2a1 + a0 + a3 + 3a2
        state[i * 4 + 2] = b[2] ^ a[1] ^ a[0] ^ b[3] ^ a[3];    // 2a2 + a1 + a0 + 3a3
        state[i * 4 + 3] = b[3] ^ a[2] ^ a[1] ^ b[0] ^ a[0];    // 2a3 + a2 + a1 + 3a0
    }
}

unsigned char AEScoder::g_mul(unsigned char a, unsigned char b)
{
    unsigned char p = 0;
    unsigned char counter;
    unsigned char hi_bit_set;
    for (counter = 0; counter < 8; counter++) {
        if ((b & 1) == 1) {
            p ^= a;
        }

        hi_bit_set = static_cast<unsigned char>(a & 0x80);
        a <<= 1;

        if (hi_bit_set == 0x80) {
            a ^= 0x1b;
        }

        b >>= 1;
    }

    return p;
}


