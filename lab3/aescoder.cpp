#include "aescoder.h"

#include <stdio.h>

using namespace std;

AEScoder::AEScoder(string _message[maxLines], int _numLines) :
    numLines(_numLines)
{
    for (int i = 0; i < numLines; i++) {
        message[i] = _message[i];
    }
}
