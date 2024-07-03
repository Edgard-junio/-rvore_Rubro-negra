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

int main()
{
    // Testes das funções de inserção e remoção

    Tree::Node<int>* root = nullptr;
    root = Tree::insertTreeNode(root,5);
    root = Tree::insertTreeNode(root,3);
    root = Tree::insertTreeNode(root,7);
    root = Tree::insertTreeNode(root,2);

    cout << "Árvore após inserção de 5, 3, 7 e 2:" << endl;

    showTree2(root);

    cout << endl;

    // Testa função de busca 

    Tree::Node<int>* node = Tree::searchNode(root, 3);

    cout << "Busca por 3: " << (node != nullptr ? "Encontrado" : "Não encontrado") << endl;

    node = Tree::searchNode(root, 4);

    cout << "Busca por 4: " << (node != nullptr ? "Encontrado" : "Não encontrado") << endl;

    // Testa função de mínimo e máximo

    Tree::Node<int>* min = Tree::minNode(root);

    cout << "Mínimo: " << min->data << endl;

    Tree::Node<int>* max = Tree::maxNode(root);

    cout << "Máximo: " << max->data << endl;

    // Testa função de inOrderTraversal

    cout << "InOrderTraversal: ";

    Tree::inorderTraversal(root);

    cout << endl;
}


