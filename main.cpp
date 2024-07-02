#include <iostream>
#include "Tree.h"

using std::cout;
using std::endl;


// ###############################

#include <iomanip>
#include <algorithm>


using std::max;

int depth(Tree::Node<int>* root) {
    if (root == nullptr) return 0;
    return std::max(depth(root->ptrLeft), depth(root->ptrRight)) + 1;
}

void printGivenLevel(Tree::Node<int>* root, int level, int indentSpace, int spaceBetween) {
    if (root == nullptr) {
        for (int i = 0; i < indentSpace; ++i) cout << " ";
        cout << " ";
        for (int i = 0; i < spaceBetween; ++i) cout << " ";
        return;
    }
    if (level == 1) {
        for (int i = 0; i < indentSpace; ++i) cout << " ";
        cout << root->data << (root->color == Tree::Color::Red ? "\033[1;31mR\033[0m" : "\033[1;30mB\033[0m");
        for (int i = 0; i < spaceBetween; ++i) cout << " ";
    } else if (level > 1) {
        printGivenLevel(root->ptrLeft, level - 1, indentSpace / 2, spaceBetween);
        printGivenLevel(root->ptrRight, level - 1, indentSpace / 2, spaceBetween);
    }
}


void showTree2(Tree::Node<int>* root) {
    int d = depth(root);
    int indentSpace = (1 << (d - 1)); // Initial space based on tree depth
    int spaceBetween = (1 << d) - 1; // Space between nodes at the same level
    for (int i = 1; i <= d; ++i) {
        printGivenLevel(root, i, indentSpace, spaceBetween);
        cout << endl;
        indentSpace /= 2; // Reduce indent space as we go deeper
        spaceBetween /= 2;
    }
}

// ###############################





int main()
{
    Tree::Node<int>* root = nullptr;
    root = Tree::insertTreeNode(root,90);
    root = Tree::insertTreeNode(root,95);
    root = Tree::insertTreeNode(root,100);
    root = Tree::insertTreeNode(root,105);
    root = Tree::insertTreeNode(root,80);
    root = Tree::insertTreeNode(root,85);
    root = Tree::insertTreeNode(root,70);
    root = Tree::insertTreeNode(root,65);
    
    showTree2(root);

    


}


