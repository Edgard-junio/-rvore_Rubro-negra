#include <iostream>
#include "Tree.h"

using std::cout;
using std::endl;


namespace Tree
{

Node* newNode(int iValor)
{
    Node* ptrTemp = (Node*)malloc(sizeof(Node)); // Criando um nó com o tamanho de um Node

    // Atualizando os parâmetros
    ptrTemp->data = iValor;
    ptrTemp->color = Color::Red;
    ptrTemp->ptrLeft = nullptr;
    ptrTemp->ptrRight = nullptr;
    ptrTemp->ptrParent = nullptr;

    return ptrTemp;
}

Node* insertTreeNode(Node* root, int data) {
    // Create a new node
    Node* ptrNewNode = newNode(data);

    // Perform a standard BST insert
    Node* ptrTemp = nullptr;
    Node* ptrCurrent = root;

    while (ptrCurrent != nullptr) {
        ptrTemp = ptrCurrent;
        if (ptrNewNode->data < ptrCurrent->data)
            ptrCurrent = ptrCurrent->ptrLeft;
        else
            ptrCurrent = ptrCurrent->ptrRight;
    }

    ptrNewNode->ptrParent = ptrTemp;

    if (ptrTemp == nullptr) {
        root = ptrNewNode; // Tree was empty
    } else if (ptrNewNode->data < ptrTemp->data) {
        ptrTemp->ptrLeft = ptrNewNode;
    } else {
        ptrTemp->ptrRight = ptrNewNode;
    }

    // Fix the Red Black Tree properties
    root = fixInsert(root, ptrNewNode);

    return root;
}

Node* fixInsert(Node* root, Node* ptrNewNode) {
    while (ptrNewNode != root && ptrNewNode->ptrParent->color == Color::Red) {
        if (ptrNewNode->ptrParent == ptrNewNode->ptrParent->ptrParent->ptrLeft) {
            Node* y = ptrNewNode->ptrParent->ptrParent->ptrRight;
            if (y != nullptr && y->color == Color::Red) {
                ptrNewNode->ptrParent->color = Color::Black;
                y->color = Color::Black;
                ptrNewNode->ptrParent->ptrParent->color = Color::Red;
                ptrNewNode = ptrNewNode->ptrParent->ptrParent;
            } else {
                if (ptrNewNode == ptrNewNode->ptrParent->ptrRight) {
                    ptrNewNode = ptrNewNode->ptrParent;
                    root = leftRotation(root, ptrNewNode);
                }
                ptrNewNode->ptrParent->color = Color::Black;
                ptrNewNode->ptrParent->ptrParent->color = Color::Red;
                root = rightRotation(root, ptrNewNode->ptrParent->ptrParent);
            }
        } else {
            Node* y = ptrNewNode->ptrParent->ptrParent->ptrLeft;
            if (y != nullptr && y->color == Color::Red) {
                ptrNewNode->ptrParent->color = Color::Black;
                y->color = Color::Black;
                ptrNewNode->ptrParent->ptrParent->color = Color::Red;
                ptrNewNode = ptrNewNode->ptrParent->ptrParent;
            } else {
                if (ptrNewNode == ptrNewNode->ptrParent->ptrLeft) {
                    ptrNewNode = ptrNewNode->ptrParent;
                    root = rightRotation(root, ptrNewNode);
                }
                ptrNewNode->ptrParent->color = Color::Black;
                ptrNewNode->ptrParent->ptrParent->color = Color::Red;
                root = leftRotation(root, ptrNewNode->ptrParent->ptrParent);
            }
        }
    }
    root->color = Color::Black;
    return root;
}

Node* leftRotation(Node* root, Node* x) {
    Node* y = x->ptrRight;
    x->ptrRight = y->ptrLeft;

    if (y->ptrLeft != nullptr) {
        y->ptrLeft->ptrParent = x;
    }

    y->ptrParent = x->ptrParent;

    if (x->ptrParent == nullptr) {
        root = y;
    } else if (x == x->ptrParent->ptrLeft) {
        x->ptrParent->ptrLeft = y;
    } else {
        x->ptrParent->ptrRight = y;
    }

    y->ptrLeft = x;
    x->ptrParent = y;

    return root;
}

Node* rightRotation(Node* root, Node* y) {
    Node* x = y->ptrLeft;
    y->ptrLeft = x->ptrRight;

    if (x->ptrRight != nullptr) {
        x->ptrRight->ptrParent = y;
    }

    x->ptrParent = y->ptrParent;

    if (y->ptrParent == nullptr) {
        root = x;
    } else if (y == y->ptrParent->ptrRight) {
        y->ptrParent->ptrRight = x;
    } else {
        y->ptrParent->ptrLeft = x;
    }

    x->ptrRight = y;
    y->ptrParent = x;

    return root;
}


}