#include "huffman.h"

using namespace std;

unsigned char getNumBytes(unsigned int n)
{
    double numBits = ceil(log2(static_cast<double>(n)));
    double numBytes = ceil(numBits / 8);
    return static_cast<unsigned char>(numBytes);
}

void Huffman::compress(string inFile, string outFile)
{
    vector<int> frequency = getSymbolFrequency(inFile);
    TreeNode *tree = get_h_tree(frequency);

    HTable table;
    build_h_table(tree, table, "");

    ifstream file(inFile, ios::binary);
    OutBytes output(outFile);

    size_t tableSize = table.size() - 1;
    output.writeByte(static_cast<unsigned char>(tableSize));

    size_t max = *max_element(frequency.begin(), frequency.end());
    unsigned char numBytes = getNumBytes(max);
    output.writeByte(numBytes);

    for (auto &elem: table) {
        output.writeByte(elem.first);
        output.writeSymbol(frequency[elem.first], numBytes);
    }

    while (true) {
        unsigned char symbol = file.get();
        if (file.eof()) {
            break;
        }

        auto code = table[symbol];
        for (auto &ch: code) {
            output.writeBit(ch == '1');
        }
    }

    output.close();
}

// Построение дерева Хаффмана
TreeNode *Huffman::get_h_tree(const std::vector<int> &priorities) {
    // Для получения канонического кода сравниваем сначала по частоте, потом по символу
    auto cmp = [](TreeNode *a, TreeNode *b) {
        if (a->getFrequency() < b->getFrequency()) {
            return true;
        } else if (a->getFrequency() == b->getFrequency()) {
            return a->getByte() > b->getByte();
        }
        return false;
    };

    set<TreeNode *, decltype(cmp)> queue(cmp);
    for (size_t i = 0; i < priorities.size(); i++) {
        if (priorities[i] == 0) {
            continue;
        }

        auto node = new TreeNode(static_cast<unsigned char>(i), priorities[i]);
        queue.insert(node);
    }

    while (queue.size() > 1) {
        auto node1 = *queue.begin();
        queue.erase(queue.begin());
        auto node2 = *queue.begin();
        queue.erase(queue.begin());

        auto new_node = new TreeNode(0, node1->getFrequency() + node2->getFrequency());
        new_node->addChild(node2);
        new_node->addChild(node1);

        queue.insert(new_node);
    }

    return *queue.begin();
}

// Построение таблицы Хаффмана на основе дерева
void Huffman::build_h_table(const TreeNode *h_tree, HTable &table, std::string str) {
    if (!h_tree) {
        return;
    }

    if (!h_tree->getLeft() && !h_tree->getRight()) {
        table[h_tree->getByte()] = str;
        return;
    }

    build_h_table(h_tree->getLeft(), table, str + "0");
    build_h_table(h_tree->getRight(), table, str + "1");
}

void Huffman::decompress(std::string inp_file, std::string otp_file) {
    InBytes file(inp_file);
    auto tree = read_h_tree(file);
    HTable table;
    build_h_table(tree, table, "");

    std::ofstream output(otp_file, std::fstream::binary);
    try {
        std::string code;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
        while (true) {
            auto bit = file.readBit();
            code += bit ? "1" : "0";
            for (auto &item: table) {
                if (code == item.second) {
                    output.put(item.first);
                    code = "";
                    continue;
                }
            }
        }
#pragma clang diagnostic pop
    } catch (std::exception &) {}


    file.close();
    output.close();
}

TreeNode *Huffman::read_h_tree(InBytes &file) {
    int symbols_n = file.readByte() + 1;
    auto bytes_per_freq = file.readByte();
    std::vector<int> priorities(256, 0);

    for (auto i = 0; i < symbols_n; i++) {
        auto byte = file.readByte();
        auto freq = file.readSymbol(bytes_per_freq);
        priorities[byte] = freq;
    }

    auto tree = get_h_tree(priorities);

    return tree;
}
