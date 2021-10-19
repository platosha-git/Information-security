#include <stdio.h>
#include <iostream>
#include <cstring>

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

    unsigned char lastBlock[16];
    memset(lastBlock, 0, 15);
    lastBlock[15] = addition;

    //blockEncode(lastBlock);
    for (int k = 0; k < 16; k++) {
        res += lastBlock[k];
    }

    message = res;
}

void AEScoder::blockEncode()
{
    cout << "before:" << endl;
    for (int i = 0; i < 16; i++) {
        cout << state[i] << " ";
    }
    cout << endl;

    //addRoundKey(0);

    /*for (int i = 1; i < Nr; i++) {
        //subBytes();
        //ShiftRows(state)
        //MixColumns(state)
        //AddRoundKey(state, w[round*Nb, (round+1)*Nb-1])
    }
    */
}
