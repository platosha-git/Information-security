#include <stdio.h>
#include <iostream>
#include <cstring>
#include <algorithm>

#include "aescoder.h"

using namespace std;

AEScoder::AEScoder(string _key)
{
    for (int i = 0; i < 4 * Nk; i++) {
        key[i] = static_cast<unsigned char>(_key[i]);
    }

    keyExpansion();
}

void AEScoder::encode(string &message)
{
    string res = "";
    unsigned char addition = 0;

    int i = 0, len = message.length();

    while (i < len) {
        memset(state, 0, 16);
        unsigned char j = 0;

        while (j < 16 && i + j < len) {
            state[j] = static_cast<unsigned char>(message[i + j]);
            j++;
        }
        i += 16;

        if (j < 16) {
            addition = static_cast<unsigned char>(16 - j);
            for (; j < 16; j++) {
                state[j] = 0;
            }
        }

        blockEncode();

        for (int k = 0; k < 16; k++) {
            res += state[k];
        }
    }

    memset(state, 0, 15);
    state[15] = addition;

    blockEncode();

    for (int k = 0; k < 16; k++) {
        res += state[k];
    }

    message = res;
}

/*void AEScoder::decode(string &message)
{
    string res = "";
    int i = 0, len = message.length();

    while (i < len) {
        memset(state, 0, 16);
        unsigned char j = 0;

        while (j < 16 && i + j < len) {
            state[j] = static_cast<unsigned char>(message[i + j]);
            j++;
        }
        i += 16;

        blockDecode();

        for (int k = 0; k < 16; k++) {
            res += (char) state[k];
        }
    }

    auto zeroes = res[res.length() - 1] + 16;
    if (zeroes > 0) {
        res = res.substr(0, res.size() - zeroes);
    }

    message = res;
}
*/
void AEScoder::blockEncode()
{
    addRoundKey(0);

    for (int i = 1; i < Nr; i++) {
        subBytes();
        shiftRows();
        mixColumns();
        addRoundKey(i);
    }

    subBytes();
    shiftRows();
    addRoundKey(Nr);
}

/*void AEScoder::blockDecode()
{
    addRoundKey(Nr);

    for (int i = Nr - 1; i > 0; i--) {
        invShiftRows();
        invSubBytes();
        addRoundKey(i);
        invMixColumns();
    }

    invShiftRows();
    invSubBytes();
    addRoundKey(0);
}
*/
