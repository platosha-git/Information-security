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
#include "bitifile.h"
#include "bitofile.h"

using HTable = std::unordered_map<unsigned char, std::string>;

class Huffman {
public:
    Huffman() = default;

    void compress(std::string inp_file, std::string otp_file);
    void decompress(std::string inp_file, std::string otp_file);
private:
    std::vector<size_t> get_priorities(const std::string &filename);
    TreeNode *get_h_tree(const std::vector<size_t> &priorities);
    void build_h_table(const TreeNode *h_tree, HTable &table, std::string str);
    TreeNode *read_h_tree(BitIFile &file);
};

#endif // HUFFMAN_H
