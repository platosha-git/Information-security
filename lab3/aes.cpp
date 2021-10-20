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
    for (auto i = 0ul; i < 4; i++) {
            unsigned char col[4];
            for (auto j = 0ul; j < 4; j++) {
                col[j] = {state[j + 4 * i]};
            }

            unsigned char a[4];
            a[0] = col[0];
            a[1] = col[1];
            a[2] = col[2];
            a[3] = col[3];

            col[0] = g_mul(a[0], 2) ^ g_mul(a[3], 1) ^ g_mul(a[2], 1) ^ g_mul(a[1], 3);
            col[1] = g_mul(a[1], 2) ^ g_mul(a[0], 1) ^ g_mul(a[3], 1) ^ g_mul(a[2], 3);
            col[2] = g_mul(a[2], 2) ^ g_mul(a[1], 1) ^ g_mul(a[0], 1) ^ g_mul(a[3], 3);
            col[3] = g_mul(a[3], 2) ^ g_mul(a[2], 1) ^ g_mul(a[1], 1) ^ g_mul(a[0], 3);

            for (auto j = 0ul; j < 4; j++) {
                state[j + 4 * i] = col[j];
            }
        }
}

unsigned char AEScoder::g_mul(unsigned char a, unsigned char b) {
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


