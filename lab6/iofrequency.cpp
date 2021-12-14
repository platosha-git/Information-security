#include "huffman.h"

using namespace std;

const string freqFile = "/home/platosha/Desktop/BMSTU/7sem/Information-security/lab6/metdata";

unsigned char getNumBytes(unsigned int n)
{
    double numBits = ceil(log2(static_cast<double>(n)));
    double numBytes = ceil(numBits / 8);
    return static_cast<unsigned char>(numBytes);
}

void writeFrequncy(const HTable table, const vector<int> frequency)
{
    OutBytes output(freqFile);

    size_t tableSize = table.size() - 1;
    output.writeByte(static_cast<unsigned char>(tableSize));

    size_t max = *max_element(frequency.begin(), frequency.end());
    unsigned char numBytes = getNumBytes(max);
    output.writeByte(numBytes);

    for (auto &elem: table) {
        output.writeByte(elem.first);
        output.writeNumber(frequency[elem.first], numBytes);
    }

    output.close();
}

vector<int> readFrequency()
{
    InBytes input(freqFile);

    int numSymbols = input.readByte() + 1;
    unsigned char numBytes = input.readByte();

    vector<int> frequency(256, 0);
    for (int i = 0; i < numSymbols; i++) {
        unsigned char byte = input.readByte();
        int freq = input.readSymbol(numBytes);
        frequency[byte] = freq;
    }

    return frequency;
}
