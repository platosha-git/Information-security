#ifndef TREENODE_H
#define TREENODE_H

class TreeNode {
public:
    explicit TreeNode(unsigned char _symb, int _frequency);

    void addChild(TreeNode *child);
    TreeNode *getLeft() const;
    TreeNode *getRight() const;

    unsigned char getSymb() const;
    int getFrequency() const;

    ~TreeNode();

private:
    TreeNode *left, *right;
    unsigned char symb;
    int frequency;
};

#endif // TREENODE_H
