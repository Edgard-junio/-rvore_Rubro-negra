#include <iostream>
#include "Tree.h"

using std::cout;
using std::endl;

using std::max;


int main()
{
    // Testes das funções de inserção e remoção
    Tree::Node<int>* root = nullptr;
    root = Tree::insertTreeNode(root,5);
    root = Tree::insertTreeNode(root,3);
    root = Tree::insertTreeNode(root,7);
    root = Tree::insertTreeNode(root,2);
    root = Tree::insertTreeNode(root,1);
    root = Tree::insertTreeNode(root,13);
    root = Tree::insertTreeNode(root,11);
    root = Tree::insertTreeNode(root,0);
    root = Tree::insertTreeNode(root,-1);

    cout << "Árvore após inserção do -1:" << endl;

    showTree(root);

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
    
    cout <<endl<< (Tree::isValidRedBlackTree(root) == 0 ? "Essa árvore é válida" : "Essa árvore não é válida") << endl;

    cout << endl;
}



