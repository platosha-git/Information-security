#include <stdio.h>
#include <iostream>
#include <cstring>

#include "aescoder.h"

using namespace std;

void AEScoder::encode(string &message)
{
    string res;
    unsigned char zeroes = 0;

    int i = 0, len = message.length();
    while (i < len) {
        unsigned char block[16];
        unsigned char j = 0;

        while (j < 16 && i + j < len) {
            block[j] = static_cast<unsigned char>(message[i + j]);
            j++;
        }
        i += 16;

        if (j < 16) {
            zeroes = static_cast<unsigned char>(16 - j);
            for (; j < 16; j++) {
                block[j] = 0;
            }
        }

        blockEncode(block);
        for (int k = 0; k < 16; k++) {
            res += block[k];
        }
    }

    unsigned char zBlock[16];
    memset(zBlock, 0, 15);
    zBlock[15] = zeroes;

    blockEncode(zBlock);
    for (int k = 0; k < 16; k++) {
        res += zBlock[k];
    }

    message = res;
}

void AEScoder::blockEncode(unsigned char (&block)[16])
{
    for (int i = 0; i < 16; i++) {
        state[i] = block[i];
    }

    addRoundKey(0);

    for (auto i = 1; i < Nr; i++) {
        sub_bytes(state);
        shift_rows(state);
        mix_columns(state);
        add_round_key(state, i);
    }

    sub_bytes(state);
    shift_rows(state);
    add_round_key(state, Nr);

    for (int i = 0; i < 16; i++) {
        block[i] = state[i];
    }
}

/*void AEScoder::addRoundKey(int keyNumber)
{
    for (int i = 0; i < 4; i++) {
        for  (int j = 0; j < 4; j++) {
            state[4 * i + j] ^= round_keys[round_key_number * 4 + i][j];
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
        int tmp[4] = {state[i], state[4 + i], state[8 + i], state[12 + i]};
        tmp = shiftRow(tmp, i);

        for (auto j = 0ul; j < 4; j++) {
            state[4 * j + i] = tmp[j];
        }
    }
}
