#include <stdexcept>
#include "treenode.h"

using namespace std;

TreeNode::TreeNode(unsigned char _symb, int _frequency) :
    left(nullptr), right(nullptr),
    symb(_symb),
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
        throw logic_error("already 2 children");
    }
}

unsigned char TreeNode::getSymb() const
{
    return symb;
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
