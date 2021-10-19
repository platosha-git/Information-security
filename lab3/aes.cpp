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
        memcpy(roundKeys[i], tmp, 4);
    }

    for (int i = Nk; i < Nb * (Nr + 1); i++) {
        unsigned char tmp[4];
        memcpy(tmp, roundKeys[i - 1], 4);

        if (i % Nk == 0) {
            rotate(tmp, tmp + 1, tmp + 4);
            subWord(tmp);
            xorWords(tmp, Rcon[i / Nk], tmp);
        }
        else if (Nk > 6 && i % Nk == 4) {
            subWord(tmp);
        }

        xorWords(roundKeys[i - Nk], tmp, roundKeys[i]);
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

/*void AEScoder::addRoundKey(int keyNumber)
{
    for (int i = 0; i < 4; i++) {
        for  (int j = 0; j < 4; j++) {
            state[4 * i + j] ^= keys[keyNumber * 4 + i][j];
        }
    }
}
*/
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


