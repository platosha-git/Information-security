#ifndef TREENODE_H
#define TREENODE_H

class TreeNode {
public:
    explicit TreeNode(unsigned char _byte, int _frequency);

    void addChild(TreeNode *child);
    TreeNode *getLeft() const;
    TreeNode *getRight() const;

    unsigned char getByte() const;
    int getFrequency() const;

    ~TreeNode();

private:
    TreeNode *left, *right;
    unsigned char byte;
    int frequency;
};

#endif // TREENODE_H
