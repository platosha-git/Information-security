#include "huffman.h"

using namespace std;

Huffman::Huffman()
{
    frequency = vector<int>(256, 0);
}

unsigned char getNumBytes(unsigned int n)
{
    double numBits = ceil(log2(static_cast<double>(n)));
    double numBytes = ceil(numBits / 8);
    return static_cast<unsigned char>(numBytes);
}

void Huffman::compress(string inFile, string outFile)
{
    frequency = getFrequency(inFile);
    TreeNode *tree = buildHTree();

    HTable table;
    buildHTable(tree, table, "");

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

        string code = table[symbol];
        for (auto &ch: code) {
            output.writeBit(ch == '1');
        }
    }

    output.close();
}

void Huffman::decompress(string inFile, string outFile)
{
    InBytes file(inFile);
    ofstream output(outFile, fstream::binary);

    frequency = file.readFrequency();
    TreeNode *tree = buildHTree();

    HTable table;
    buildHTable(tree, table, "");

    string code = "";
    while (!file.isEof()) {
        bool bit = file.readBit();
        code += bit ? '1' : '0';
        for (auto &item: table) {
            if (code == item.second) {
                output.put(item.first);
                code = "";
            }
        }
    }

    file.close();
    output.close();
}

TreeNode *Huffman::buildHTree()
{
    // Для получения канонического кода сравниваем сначала по частоте, потом по символу
    auto cmp = [](TreeNode *a, TreeNode *b) {
        if (a->getFrequency() < b->getFrequency()) {
            return true;
        }
        else if (a->getFrequency() == b->getFrequency()) {
            return a->getSymb() > b->getSymb();
        }
        return false;
    };

    set<TreeNode *, decltype(cmp)> queue(cmp);
    for (size_t i = 0; i < frequency.size(); i++) {
        if (frequency[i] == 0) {
            continue;
        }

        TreeNode *node = new TreeNode(static_cast<unsigned char>(i), frequency[i]);
        queue.insert(node);
    }

    while (queue.size() > 1) {
        TreeNode *node1 = *queue.begin();
        queue.erase(queue.begin());

        TreeNode *node2 = *queue.begin();
        queue.erase(queue.begin());

        TreeNode *newNode = new TreeNode(0, node1->getFrequency() + node2->getFrequency());
        newNode->addChild(node2);
        newNode->addChild(node1);

        queue.insert(newNode);
    }

    return *queue.begin();
}

// Построение таблицы Хаффмана на основе дерева
void Huffman::buildHTable(const TreeNode *root, HTable &table, string code)
{
    if (!root) {
        return;
    }

    if (!root->getLeft() && !root->getRight()) {
        table[root->getSymb()] = code;
        return;
    }

    buildHTable(root->getLeft(), table, code + '0');
    buildHTable(root->getRight(), table, code + '1');
}
