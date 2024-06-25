#include <iostream>
#include "Tree.h"

using std::cout;
using std::endl;

int main()
{
    Tree::Node* root = nullptr;
    Tree::insertTreeNode(&root,70);
    Tree::insertTreeNode(&root,74);
    Tree::insertTreeNode(&root,60);
    Tree::insertTreeNode(&root,39);
    Tree::insertTreeNode(&root,29);
    Tree::insertTreeNode(&root,72);


    Tree::removeNode(root,74);

    Tree::showTree(root);
}