#include <iostream>
#include "Tree.h"

using std::cout;
using std::endl;
using std::string;


namespace Tree
{

template <typename T>
Node<T>* newNode(T iValor)
{
    Node<T>* ptrTemp =  new Node<T>();

    // Atualizando os parâmetros
    ptrTemp->data = iValor;
    ptrTemp->color = Color::Red;
    ptrTemp->ptrLeft = nullptr;
    ptrTemp->ptrRight = nullptr;
    ptrTemp->ptrParent = nullptr;

    return ptrTemp;
}

template <typename T>
Node<T>* insertTreeNode(Node<T>* root, T data) {
    // Create a new node
    Node<T>* ptrNewNode = newNode(data);

    // Perform a standard BST insert
    Node<T>* ptrTemp = nullptr;
    Node<T>* ptrCurrent = root;

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

template <typename T>
Node<T>* fixInsert(Node<T>* root, Node<T>* ptrNewNode) {
    while (ptrNewNode != root && ptrNewNode->ptrParent->color == Color::Red) {
        if (ptrNewNode->ptrParent == ptrNewNode->ptrParent->ptrParent->ptrLeft) {
            Node<T>* y = ptrNewNode->ptrParent->ptrParent->ptrRight;
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
            Node<T>* y = ptrNewNode->ptrParent->ptrParent->ptrLeft;
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

template <typename T>
Node<T>* leftRotation(Node<T>* root, Node<T>* x) {
    Node<T>* y = x->ptrRight;
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

template <typename T>
Node<T>* rightRotation(Node<T>* root, Node<T>* y) {
    Node<T>* x = y->ptrLeft;
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

template <typename T>
void showTree(Node<T>* root)
{
    if(root == nullptr) return;

     cout << "Valor do nó = " << root -> data << " Sua cor é " << (root-> color == Red ? "\033[1;31mRed\033[0m" : "\033[1;30mBlack\033[0m") << endl;

    showTree(root -> ptrLeft);
    showTree(root -> ptrRight);
}

template <typename T>
Node<T>* minNode(Node<T>* root)
{
    if(root == nullptr)
    {
        return root;
    }

    Node<T>* current = root;
    while (current -> ptrLeft != nullptr) current = current -> ptrLeft;

    return current;
}

template <typename T>
Node<T>* maxNode(Node<T>* root)
{
    if(root == nullptr)
    {
        return root;
    }
    Node<T>* current = root;
    while (current -> ptrRight != nullptr) current = current -> ptrRight;

    return current;
}

template <typename T>
void inorderTraversal(Node<T>* root) 
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

template <typename T>
bool isValidRedBlackTree(Node<T>* root) 
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

    Node<T>* current = root;
    Node<T>* rightCurrent = root;
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
    Node<T>* stack[100];  // Pilha para percorrer a árvore
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

// Instâncias explícitas
template Node<int>* newNode(int);
template Node<float>* newNode(float);
template Node<double>* newNode(double);

template Node<int>* insertTreeNode(Node<int>*, int);
template Node<float>* insertTreeNode(Node<float>*, float);
template Node<double>* insertTreeNode(Node<double>*, double);

template Node<int>* fixInsert(Node<int>*, Node<int>*);
template Node<float>* fixInsert(Node<float>*, Node<float>*);
template Node<double>* fixInsert(Node<double>*, Node<double>*);

template Node<int>* leftRotation(Node<int>*, Node<int>*);
template Node<float>* leftRotation(Node<float>*, Node<float>*);
template Node<double>* leftRotation(Node<double>*, Node<double>*);

template Node<int>* rightRotation(Node<int>*, Node<int>*);
template Node<float>* rightRotation(Node<float>*, Node<float>*);
template Node<double>* rightRotation(Node<double>*, Node<double>*);

template void showTree(Node<int>*);
template void showTree(Node<float>*);
template void showTree(Node<double>*);

template Node<int>* minNode(Node<int>*);
template Node<float>* minNode(Node<float>*);
template Node<double>* minNode(Node<double>*);

template Node<int>* maxNode(Node<int>*);
template Node<float>* maxNode(Node<float>*);
template Node<double>* maxNode(Node<double>*);

template void inorderTraversal(Node<int>*);
template void inorderTraversal(Node<float>*);
template void inorderTraversal(Node<double>*);

template bool isValidRedBlackTree(Node<int>*);
template bool isValidRedBlackTree(Node<float>*);
template bool isValidRedBlackTree(Node<double>*);

}