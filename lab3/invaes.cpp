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

        ///////////////////////////////
        /*unsigned char a[4];
        unsigned char b[4];
        unsigned char c;
        unsigned char h;
        for(c = 0; c < 4; c++) {
            a[c] = curCol[c];
            h = (unsigned char)((signed char)curCol[c] >> 7);
            b[c] = curCol[c] << 1;
            b[c] ^= 0x1B & h;
        }

        ////////////////////////////////
        state[i * 4 + 0] = b[0] ^ a[3] ^ a[2] ^ b[1] ^ a[1];
        state[i * 4 + 1] = b[1] ^ a[0] ^ a[3] ^ b[2] ^ a[2];
        state[i * 4 + 2] = b[2] ^ a[1] ^ a[0] ^ b[3] ^ a[3];
        state[i * 4 + 3] = b[3] ^ a[2] ^ a[1] ^ b[0] ^ a[0];
        */

        state[4 * i] = g_mul(curCol[0], 14) ^ g_mul(curCol[3], 9) ^ g_mul(curCol[2], 13) ^ g_mul(curCol[1], 11);
                state[4 * i + 1] = g_mul(curCol[1], 14) ^ g_mul(curCol[0], 9) ^ g_mul(curCol[3], 13) ^ g_mul(curCol[2], 11);
                state[4 * i + 2] = g_mul(curCol[2], 14) ^ g_mul(curCol[1], 9) ^ g_mul(curCol[0], 13) ^ g_mul(curCol[3], 11);
                state[4 * i + 3] = g_mul(curCol[3], 14) ^ g_mul(curCol[2], 9) ^ g_mul(curCol[1], 13) ^ g_mul(curCol[0], 11);
    }
}
