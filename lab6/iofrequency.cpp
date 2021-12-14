#include "huffman.h"

using namespace std;

unsigned char getNumBytes(unsigned int n)
{
    double numBits = ceil(log2(static_cast<double>(n)));
    double numBytes = ceil(numBits / 8);
    return static_cast<unsigned char>(numBytes);
}

void writeFrequncy(OutBytes &output, const HTable table, const vector<int> frequency)
{
    size_t tableSize = table.size() - 1;
    output.writeByte(static_cast<unsigned char>(tableSize));

    size_t max = *max_element(frequency.begin(), frequency.end());
    unsigned char numBytes = getNumBytes(max);
    output.writeByte(numBytes);

    for (auto &elem: table) {
        output.writeByte(elem.first);
        output.writeNumber(frequency[elem.first], numBytes);
    }
}

vector<int> readFrequency(InBytes &file)
{
    int numSymbols = file.readByte() + 1;
    unsigned char numBytes = file.readByte();

    vector<int> frequency(256, 0);
    for (int i = 0; i < numSymbols; i++) {
        unsigned char byte = file.readByte();
        int freq = file.readSymbol(numBytes);
        frequency[byte] = freq;
    }

    return frequency;
}
