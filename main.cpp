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


    Tree::showTree(root);

    cout<<"Depois da rotação"<<endl;
    Tree::Node* ptr = Tree::leftRotation(root);

    Tree::showTree(ptr);
}