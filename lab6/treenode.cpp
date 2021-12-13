#include <stdexcept>
#include "treenode.h"

TreeNode::TreeNode(unsigned char _byte, int _frequency) :
    left(nullptr), right(nullptr),
    byte(_byte),
    frequency(_frequency)
{

}

TreeNode::~TreeNode()
{
    delete left;
    delete right;
}

void TreeNode::addChild(TreeNode *child)
{
    if (!left) {
        left = child;
    }
    else if (!right) {
        right = child;
    }
    else {
        throw std::logic_error("already 2 children");
    }
}

unsigned char TreeNode::getByte() const
{
    return byte;
}

TreeNode *TreeNode::getLeft() const
{
    return left;
}

TreeNode *TreeNode::getRight() const
{
    return right;
}

int TreeNode::getFrequency() const
{
    return frequency;
}
