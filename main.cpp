#include <iostream>
#include "Tree.h"

using std::cout;
using std::endl;

int main()
{
    Tree::Node* root = nullptr;
    root = Tree::insertTreeNode(root,90);
    root = Tree::insertTreeNode(root,95);
    root = Tree::insertTreeNode(root,91); 
    root = Tree::insertTreeNode(root,9);

    Tree::showTree(root);

}