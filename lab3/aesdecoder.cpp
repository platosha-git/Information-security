#include <stdio.h>
#include <iostream>
#include <cstring>
#include <algorithm>

#include "aescoder.h"

using namespace std;

void AEScoder::decode(string &message)
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

void AEScoder::blockDecode()
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
