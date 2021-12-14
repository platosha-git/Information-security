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
    Huffman() = default;

    void compress(std::string inFile, std::string outFile);
    void decompress(std::string inFile, std::string outFile);

private:
    std::vector<int> frequency;
    TreeNode *getHTree();
    void build_h_table(const TreeNode *h_tree, HTable &table, std::string str);
    TreeNode *read_h_tree(InBytes &file);
};

#endif // HUFFMAN_H
