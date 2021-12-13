#include <iostream>
#include "huffman.h"

using namespace std;

const string document = "/home/platosha/Desktop/BMSTU/7sem/Information-security/lab6/document";
const string compressed = "/home/platosha/Desktop/BMSTU/7sem/Information-security/lab6/pressed";
const string decompressed = "/home/platosha/Desktop/BMSTU/7sem/Information-security/lab6/unpressed";

void menu()
{
    cout << "Compress document........1" << endl;
    cout << "Decompress document......2" << endl;
    cout << "Exit.....................3" << endl;
}

int main(void)
{
    Huffman huffman;

    int choose = 0;
    while (choose != 3) {
        menu();
        cin >> choose;

        switch (choose) {
        case 1:
            huffman.compress(document, compressed);
            cout << "Document was compressed successfuly!\n\n";
            break;
        case 2:
            huffman.decompress(compressed, decompressed);
            cout << "Document was decompressed successfuly!\n\n";
            break;
        default:
            break;
        }
    }

    return 0;
}
