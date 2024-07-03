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
    // Cria um novo nó
    Node<T>* ptrNewNode = newNode(data);

    // Performa a inserção de um novo nó
    Node<T>* ptrTemp = nullptr;
    Node<T>* ptrCurrent = root;

    while (ptrCurrent != nullptr) {
        ptrTemp = ptrCurrent;

        if (ptrNewNode->data < ptrCurrent->data) ptrCurrent = ptrCurrent->ptrLeft;

        else ptrCurrent = ptrCurrent->ptrRight;
    }

    ptrNewNode->ptrParent = ptrTemp;

    if (ptrTemp == nullptr) {
        root = ptrNewNode; // Árvore vazia
    } else if (ptrNewNode->data < ptrTemp->data) {
        ptrTemp->ptrLeft = ptrNewNode;
    } else {
        ptrTemp->ptrRight = ptrNewNode;
    }

    // Corrige a árvore vermelha e preta
    root = fixInsert(root, ptrNewNode);

    return root;
}

template <typename T>
Node<T>* fixInsert(Node<T>* root, Node<T>* ptrNewNode) {
    while (ptrNewNode != root && ptrNewNode->ptrParent->color == Color::Red) {
        
        // Se o pai do nó é o filho esquerdo do avô
        if (ptrNewNode->ptrParent == ptrNewNode->ptrParent->ptrParent->ptrLeft) {
            Node<T>* uncle = ptrNewNode->ptrParent->ptrParent->ptrRight; // Tio do nó

            // Se o tio do nó é vermelho
            if (uncle != nullptr && uncle->color == Color::Red) {
                ptrNewNode->ptrParent->color = Color::Black;
                uncle->color = Color::Black;
                ptrNewNode->ptrParent->ptrParent->color = Color::Red;
                ptrNewNode = ptrNewNode->ptrParent->ptrParent;
            }
            
            // Se o tio do nó é preto
            else {
                // Se o nó é o filho direito do pai
                if (ptrNewNode == ptrNewNode->ptrParent->ptrRight) {
                    ptrNewNode = ptrNewNode->ptrParent;
                    root = leftRotation(root, ptrNewNode);
                }
                ptrNewNode->ptrParent->color = Color::Black;
                ptrNewNode->ptrParent->ptrParent->color = Color::Red;
                root = rightRotation(root, ptrNewNode->ptrParent->ptrParent);
            }
        } 

        // Se o pai do nó é o filho direito do avô
        else {
            Node<T>* uncle = ptrNewNode->ptrParent->ptrParent->ptrLeft; // Tio do nó

            // Se o tio do nó é vermelho
            if (uncle != nullptr && uncle->color == Color::Red) {
                ptrNewNode->ptrParent->color = Color::Black;
                uncle->color = Color::Black;
                ptrNewNode->ptrParent->ptrParent->color = Color::Red;
                ptrNewNode = ptrNewNode->ptrParent->ptrParent;
            } 
            
            // Se o tio do nó é preto
            else {
                // Se o nó é o filho esquerdo do pai
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
Node<T>* leftRotation(Node<T>* root, Node<T>* ptrCurrent) {
    Node<T>* ptrTemp = ptrCurrent->ptrRight;
    ptrCurrent->ptrRight = ptrTemp->ptrLeft;

    if (ptrTemp->ptrLeft != nullptr) {
        ptrTemp->ptrLeft->ptrParent = ptrCurrent;
    }

    ptrTemp->ptrParent = ptrCurrent->ptrParent;

    if (ptrCurrent->ptrParent == nullptr) {
        root = ptrTemp;
    } else if (ptrCurrent == ptrCurrent->ptrParent->ptrLeft) {
        ptrCurrent->ptrParent->ptrLeft = ptrTemp;
    } else {
        ptrCurrent->ptrParent->ptrRight = ptrTemp;
    }

    ptrTemp->ptrLeft = ptrCurrent;
    ptrCurrent->ptrParent = ptrTemp;

    return root;
}

template <typename T>
Node<T>* rightRotation(Node<T>* root, Node<T>* ptrCurrent) {
    Node<T>* ptrTemp = ptrCurrent->ptrLeft;
    ptrCurrent->ptrLeft = ptrTemp->ptrRight;

    if (ptrTemp->ptrRight != nullptr) {
        ptrTemp->ptrRight->ptrParent = ptrCurrent;
    }

    ptrTemp->ptrParent = ptrCurrent->ptrParent;

    if (ptrCurrent->ptrParent == nullptr) {
        root = ptrTemp;
    } else if (ptrCurrent == ptrCurrent->ptrParent->ptrRight) {
        ptrCurrent->ptrParent->ptrRight = ptrTemp;
    } else {
        ptrCurrent->ptrParent->ptrLeft = ptrTemp;
    }

    ptrTemp->ptrRight = ptrCurrent;
    ptrCurrent->ptrParent = ptrTemp;

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

template <typename T>
Node<T>* removeNode(Node<T>* root, T data) {
    Node<T>* nodeToDelete = searchNode(root, data);
    if (nodeToDelete == nullptr) {
        return root; // Node not found
    }

    Node<T>* y = nodeToDelete;
    Node<T>* x;
    Color originalColor = y->color;

    if (nodeToDelete->ptrLeft == nullptr) {
        x = nodeToDelete->ptrRight;
        root = transplant(root, nodeToDelete, nodeToDelete->ptrRight);
    } else if (nodeToDelete->ptrRight == nullptr) {
        x = nodeToDelete->ptrLeft;
        root = transplant(root, nodeToDelete, nodeToDelete->ptrLeft);
    } else {
        y = minNode(nodeToDelete->ptrRight);
        originalColor = y->color;
        x = y->ptrRight;
        if (y->ptrParent == nodeToDelete) {
            if (x != nullptr) {
                x->ptrParent = y;
            }
        } else {
            root = transplant(root, y, y->ptrRight);
            y->ptrRight = nodeToDelete->ptrRight;
            y->ptrRight->ptrParent = y;
        }
        root = transplant(root, nodeToDelete, y);
        y->ptrLeft = nodeToDelete->ptrLeft;
        y->ptrLeft->ptrParent = y;
        y->color = nodeToDelete->color;
    }
    delete nodeToDelete;
    if (originalColor == Color::Black) {
        root = fixDelete(root, x);
    }
    return root;
}

template <typename T>
Node<T>* transplant(Node<T>* root, Node<T>* u, Node<T>* v) {
    if (u->ptrParent == nullptr) {
        root = v;
    } else if (u == u->ptrParent->ptrLeft) {
        u->ptrParent->ptrLeft = v;
    } else {
        u->ptrParent->ptrRight = v;
    }
    if (v != nullptr) {
        v->ptrParent = u->ptrParent;
    }
    return root;
}

template <typename T>
Node<T>* fixDelete(Node<T>* root, Node<T>* x) {
    while (x != root && (x == nullptr || x->color == Color::Black)) {
        if (x == x->ptrParent->ptrLeft) {
            Node<T>* w = x->ptrParent->ptrRight;
            if (w->color == Color::Red) {
                w->color = Color::Black;
                x->ptrParent->color = Color::Red;
                root = leftRotation(root, x->ptrParent);
                w = x->ptrParent->ptrRight;
            }
            if ((w->ptrLeft == nullptr || w->ptrLeft->color == Color::Black) &&
                (w->ptrRight == nullptr || w->ptrRight->color == Color::Black)) {
                w->color = Color::Red;
                x = x->ptrParent;
            } else {
                if (w->ptrRight == nullptr || w->ptrRight->color == Color::Black) {
                    if (w->ptrLeft != nullptr) {
                        w->ptrLeft->color = Color::Black;
                    }
                    w->color = Color::Red;
                    root = rightRotation(root, w);
                    w = x->ptrParent->ptrRight;
                }
                w->color = x->ptrParent->color;
                x->ptrParent->color = Color::Black;
                if (w->ptrRight != nullptr) {
                    w->ptrRight->color = Color::Black;
                }
                root = leftRotation(root, x->ptrParent);
                x = root;
            }
        } else {
            Node<T>* w = x->ptrParent->ptrLeft;
            if (w->color == Color::Red) {
                w->color = Color::Black;
                x->ptrParent->color = Color::Red;
                root = rightRotation(root, x->ptrParent);
                w = x->ptrParent->ptrLeft;
            }
            if ((w->ptrLeft == nullptr || w->ptrLeft->color == Color::Black) &&
                (w->ptrRight == nullptr || w->ptrRight->color == Color::Black)) {
                w->color = Color::Red;
                x = x->ptrParent;
            } else {
                if (w->ptrLeft == nullptr || w->ptrLeft->color == Color::Black) {
                    if (w->ptrRight != nullptr) {
                        w->ptrRight->color = Color::Black;
                    }
                    w->color = Color::Red;
                    root = leftRotation(root, w);
                    w = x->ptrParent->ptrLeft;
                }
                w->color = x->ptrParent->color;
                x->ptrParent->color = Color::Black;
                if (w->ptrLeft != nullptr) {
                    w->ptrLeft->color = Color::Black;
                }
                root = rightRotation(root, x->ptrParent);
                x = root;
            }
        }
    }
    if (x != nullptr) {
        x->color = Color::Black;
    }
    return root;
}

template <typename T>
Node<T>* searchNode(Node<T>* root, T data) {
    while (root != nullptr && root->data != data) {
        if (data < root->data) {
            root = root->ptrLeft;
        } else {
            root = root->ptrRight;
        }
    }
    return root;
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

// Instâncias explícitas para a função de remoção
template Node<int>* removeNode(Node<int>*, int);
template Node<float>* removeNode(Node<float>*, float);
template Node<double>* removeNode(Node<double>*, double);

template Node<int>* transplant(Node<int>*, Node<int>*, Node<int>*);
template Node<float>* transplant(Node<float>*, Node<float>*, Node<float>*);
template Node<double>* transplant(Node<double>*, Node<double>*, Node<double>*);

template Node<int>* fixDelete(Node<int>*, Node<int>*);
template Node<float>* fixDelete(Node<float>*, Node<float>*);
template Node<double>* fixDelete(Node<double>*, Node<double>*);

template Node<int>* searchNode(Node<int>*, int);
template Node<float>* searchNode(Node<float>*, float);
template Node<double>* searchNode(Node<double>*, double);
} 

