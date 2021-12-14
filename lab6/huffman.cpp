#include "huffman.h"
#include "iofrequency.cpp"

using namespace std;

Huffman::Huffman()
{
    frequency = vector<int>(256, 0);
}

void Huffman::compress(string inFile, string outFile)
{
    frequency = getFrequency(inFile);
    TreeNode *tree = buildHTree();

    HTable table;
    buildHTable(tree, table, "");

    ifstream file(inFile, ios::binary);
    OutBytes output(outFile);

    writeFrequncy(output, table, frequency);
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
    file.close();
}

void Huffman::decompress(string inFile, string outFile)
{
    InBytes file(inFile);
    ofstream output(outFile, fstream::binary);

    frequency = readFrequency(file);
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

    //Формирование списка свободных узлов
    set<TreeNode *, decltype(cmp)> list(cmp);
    for (size_t i = 0; i < frequency.size(); i++) {
        if (frequency[i] == 0) {
            continue;
        }

        TreeNode *node = new TreeNode(static_cast<unsigned char>(i), frequency[i]);
        list.insert(node);
    }

    while (list.size() > 1) {
        TreeNode *node1 = *list.begin();
        list.erase(list.begin());

        TreeNode *node2 = *list.begin();
        list.erase(list.begin());

        TreeNode *newNode = new TreeNode(0, node1->getFrequency() + node2->getFrequency());
        newNode->addChild(node2);
        newNode->addChild(node1);

        list.insert(newNode);
    }

    return *list.begin();
}

void Huffman::buildHTable(const TreeNode *root, HTable &table, string code)
{
    if (!root) {
        return;
    }

    if (!root->getLeft() && !root->getRight()) {
        table[root->getSymb()] = code;
        return;
    }

    buildHTable(root->getLeft(), table, code + '1');
    buildHTable(root->getRight(), table, code + '0');
}
