#include <iostream>
#include "Tree.h"

using std::cout;
using std::endl;
using std::string;


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

void showTree(Node* root)
{
    if(root == nullptr) return;

     cout << "Valor do nó = " << root -> data << " Sua cor é " << (root-> color == Red ? "\033[1;31mRed\033[0m" : "\033[1;30mBlack\033[0m") << endl;

    showTree(root -> ptrLeft);
    showTree(root -> ptrRight);
}

Node* minNode(Node* root)
{
    if(root == nullptr)
    {
        return root;
    }

    Node* current = root;
    while (current -> ptrLeft != nullptr) current = current -> ptrLeft;

    return current;
}

Node* maxNode(Node* root)
{
    if(root == nullptr)
    {
        return root;
    }
    Node* current = root;
    while (current -> ptrRight != nullptr) current = current -> ptrRight;

    return current;
}
void inorderTraversal(Node* root) 
{
    if (root == nullptr) 
    {
        return;
    }

    // Percorrer a subárvore esquerda
    inorderTraversal(root->ptrLeft);

    // Processar o nó raiz
    cout << root->data << " ";

    // Percorrer a subárvore direita
    inorderTraversal(root->ptrRight);
}

bool isValidRedBlackTree(Node* root) 
{
    // Se a raiz é nula, a árvore é considerada válida
    if (root == nullptr) 
    {
        return true;
    }

    int isValid = true;

    // Verificar se a raiz é preta
    if (root->color != Black) 
    {
        return false;
    }

    Node* current = root;
    Node* rightCurrent = root;
    int iAmountBlack = 0;  // Contador de nós pretos no caminho da raiz até a folha mais à esquerda
    int iAmountright = 0;  // Contador de nós pretos no caminho da raiz até a folha mais à direita
    int pathBlackHeight = -1;  // Variável para armazenar a altura negra de um caminho

    // Loop para verificar se há nós vermelhos consecutivos e contar os nós pretos
    while (rightCurrent != nullptr) 
    {
        if (rightCurrent != nullptr) 
        {
            if (rightCurrent->color == Black) 
            {
                iAmountright++;
            }
            rightCurrent = rightCurrent->ptrRight;
        }

        // Verificar se há dois nós vermelhos consecutivos à direita
        if (rightCurrent != nullptr && rightCurrent->ptrRight != nullptr &&
            rightCurrent->color == Red && rightCurrent->ptrRight->color == Red) 
        {
            isValid = false;
            break;
        }

        if (current->color == Black) 
        {
            iAmountBlack++;
        }

        // Verificar se há dois nós vermelhos consecutivos à esquerda
        if (current->ptrLeft != nullptr && current->color == Red && current->ptrLeft->color == Red) 
        {
            isValid = false;
            break;
        }

        current = current->ptrLeft;
    }

    // Verificar a altura negra e se todas as folhas (nós nulos) são pretas
    Node* stack[100];  // Pilha para percorrer a árvore
    int top = -1;  // Índice do topo da pilha
    current = root;
    int blackHeight = 0;  // Contador da altura negra do caminho atual
    bool done = false;

    // Loop para percorrer a árvore e verificar a altura negra de todos os caminhos
    while (!done) 
    {
        if (current != nullptr) 
        {
            stack[++top] = current;
            current = current->ptrLeft;
        } 
        else 
        {
            if (top >= 0) 
            {
                current = stack[top--];
                if (current->color == Black) 
                {
                    blackHeight++;
                }
                // Verificar se a folha (nó nulo) é preta
                if (current->ptrLeft == nullptr && current->ptrRight == nullptr) 
                {
                    if (pathBlackHeight == -1) 
                    {
                        pathBlackHeight = blackHeight;
                    }
                    else if (pathBlackHeight != blackHeight) 
                    {
                        isValid = false;
                        break;
                    }
                }
                current = current->ptrRight;
            } 
            else 
            {
                done = true;
            }
        }
    }

    return isValid;
}
}