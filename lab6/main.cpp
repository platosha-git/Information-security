#include <iostream>
#include "huffman.h"

using namespace std;

int main(void)
{
    int choose = 0;
    cin >> choose;

    Huffman huffman;
    if (choose == 1) {
        huffman.compress("input", "output");
    } else {
        huffman.decompress("output", "result");
    }

    return 0;
}
