#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <algorithm>
#include <cmath>
#include <vector>
#include <string>
#include <functional>
#include <fstream>
#include <unordered_map>
#include <set>
#include "treenode.h"
#include "inbytes.h"
#include "outbytes.h"

using HTable = std::unordered_map<unsigned char, std::string>;

class Huffman {
public:
    Huffman();

    void compress(std::string inFile, std::string outFile);
    void decompress(std::string inFile, std::string outFile);

private:
    std::vector<int> frequency;
    TreeNode *buildHTree();
    void buildHTable(const TreeNode *root, HTable &table, std::string code);
};

#endif // HUFFMAN_H
