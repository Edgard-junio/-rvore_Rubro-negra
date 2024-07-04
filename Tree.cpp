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

    if (ptrTemp == nullptr) 
    {
        root = ptrNewNode; // Árvore vazia
    } 
    
    else if (ptrNewNode->data < ptrTemp->data) 
    {
        ptrTemp->ptrLeft = ptrNewNode;
    } 
    
    else 
    {
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
        if (ptrNewNode->ptrParent == ptrNewNode->ptrParent->ptrParent->ptrLeft) 
        {
            Node<T>* uncle = ptrNewNode->ptrParent->ptrParent->ptrRight; // Tio do nó

            // Se o tio do nó é vermelho
            if (uncle != nullptr && uncle->color == Color::Red) 
            {
                ptrNewNode->ptrParent->color = Color::Black;
                uncle->color = Color::Black;
                ptrNewNode->ptrParent->ptrParent->color = Color::Red;
                ptrNewNode = ptrNewNode->ptrParent->ptrParent;
            }
            
            // Se o tio do nó é preto
            else 
            {
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
        else 
        {
            Node<T>* uncle = ptrNewNode->ptrParent->ptrParent->ptrLeft; // Tio do nó

            // Se o tio do nó é vermelho
            if (uncle != nullptr && uncle->color == Color::Red) 
            {
                ptrNewNode->ptrParent->color = Color::Black;
                uncle->color = Color::Black;
                ptrNewNode->ptrParent->ptrParent->color = Color::Red;
                ptrNewNode = ptrNewNode->ptrParent->ptrParent;
            } 
            
            // Se o tio do nó é preto
            else 
            {
                // Se o nó é o filho esquerdo do pai
                if (ptrNewNode == ptrNewNode->ptrParent->ptrLeft) 
                {
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

    if (ptrTemp->ptrLeft != nullptr) 
    {
        ptrTemp->ptrLeft->ptrParent = ptrCurrent;
    }

    ptrTemp->ptrParent = ptrCurrent->ptrParent;

    // Se o nó atual é a raiz
    if (ptrCurrent->ptrParent == nullptr) 
    {
        root = ptrTemp;
    } 

    // Se o nó atual é o filho esquerdo do pai
    else if (ptrCurrent == ptrCurrent->ptrParent->ptrLeft) 
    {
        ptrCurrent->ptrParent->ptrLeft = ptrTemp;
    }

    // Se o nó atual é o filho direito do pai 
    else 
    {
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

    if (ptrTemp->ptrRight != nullptr) 
    {
        ptrTemp->ptrRight->ptrParent = ptrCurrent;
    }

    ptrTemp->ptrParent = ptrCurrent->ptrParent;

    // Se o nó atual é a raiz
    if (ptrCurrent->ptrParent == nullptr) 
    {
        root = ptrTemp;
    } 
    // Se o nó atual é o filho direito do pai
    else if (ptrCurrent == ptrCurrent->ptrParent->ptrRight) 
    {
        ptrCurrent->ptrParent->ptrRight = ptrTemp;
    } 
    
    // Se o nó atual é o filho esquerdo do pai
    else 
    {
        ptrCurrent->ptrParent->ptrLeft = ptrTemp;
    }

    ptrTemp->ptrRight = ptrCurrent;
    ptrCurrent->ptrParent = ptrTemp;

    return root;
}

template <typename T>
void printGivenLevel(Tree::Node<T>* root, int level, int indentSpace, int spaceBetween) {
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

template <typename T>
void showTree(Tree::Node<T>* root) {
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

template <typename T>
Node<T>* minNode(Node<T>* root)
{
    if(root == nullptr)
    {
        return root;
    }

    Node<T>* current = root;

    // Enquanto houver um nó à esquerda, continue descendo
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

    // Enquanto houver um nó à direita, continue descendo
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
    while (rightCurrent != nullptr && current != nullptr) 
    {
        if (rightCurrent->color == Black) 
        {
            iAmountright++;
        }
        rightCurrent = rightCurrent->ptrRight;

        // Verificar se há dois nós vermelhos consecutivos à direita
        if (rightCurrent != nullptr && rightCurrent->ptrRight != nullptr && rightCurrent->color == Red && rightCurrent->ptrRight->color == Red) 
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
        return root; // Nó não encontrado
    }

    Node<T>* ptrTemp = nodeToDelete;
    Node<T>* ptrSubstitution;
    Color originalColor = ptrTemp->color;

    // Se o nó a ser removido não tem filho à esquerda
    if (nodeToDelete->ptrLeft == nullptr) 
    {
        ptrSubstitution = nodeToDelete->ptrRight;
        root = transplant(root, nodeToDelete, nodeToDelete->ptrRight);
    } 
    
    // Se o nó a ser removido não tem filho à direita
    else if (nodeToDelete->ptrRight == nullptr) 
    {
        ptrSubstitution = nodeToDelete->ptrLeft;
        root = transplant(root, nodeToDelete, nodeToDelete->ptrLeft);
    } 
    
    // Se o nó a ser removido tem dois filhos
    else 
    {
        ptrTemp = minNode(nodeToDelete->ptrRight);
        originalColor = ptrTemp->color;
        ptrSubstitution = ptrTemp->ptrRight;

        // Se o nó a ser removido é o pai do nó a ser substituído
        if (ptrTemp->ptrParent == nodeToDelete) 
        {
            if (ptrSubstitution != nullptr) 
            {
                ptrSubstitution->ptrParent = ptrTemp;
            }
        } 
        
        // Se o nó a ser removido não é o pai do nó a ser substituído
        else 
        {
            root = transplant(root, ptrTemp, ptrTemp->ptrRight);
            ptrTemp->ptrRight = nodeToDelete->ptrRight;
            ptrTemp->ptrRight->ptrParent = ptrTemp;
        }

        root = transplant(root, nodeToDelete, ptrTemp);
        ptrTemp->ptrLeft = nodeToDelete->ptrLeft;
        ptrTemp->ptrLeft->ptrParent = ptrTemp;
        ptrTemp->color = nodeToDelete->color;
    }

    free(nodeToDelete);
    
    // Corrige a árvore vermelha e preta
    if (originalColor == Color::Black) {
        root = fixDelete(root, ptrSubstitution);
    }
    return root;
}

template <typename T>
Node<T>* transplant(Node<T>* root, Node<T>* nodeToReplace, Node<T>* replacementNode) {
    // Se o nó a ser substituído é a raiz
    if (nodeToReplace->ptrParent == nullptr) 
    {
        root = replacementNode;
    }
    // Se o nó a ser substituído é o filho esquerdo do pai
    else if (nodeToReplace == nodeToReplace->ptrParent->ptrLeft) 
    {
        nodeToReplace->ptrParent->ptrLeft = replacementNode;
    } 
    // Se o nó a ser substituído é o filho direito do pai
    else 
    {
        nodeToReplace->ptrParent->ptrRight = replacementNode;
    }
    // Se o nó de substituição não é nulo
    if (replacementNode != nullptr) {
        replacementNode->ptrParent = nodeToReplace->ptrParent;
    }
    return root;
}

template <typename T>
Node<T>* fixDelete(Node<T>* root, Node<T>* nodeToDelete) {
    while (nodeToDelete != root && (nodeToDelete == nullptr || nodeToDelete->color == Color::Black)) 
    {
        // Se o nó a ser deletado é o filho esquerdo do pai
        if (nodeToDelete == nodeToDelete->ptrParent->ptrLeft) 
        {
            Node<T>* sibling = nodeToDelete->ptrParent->ptrRight;
            
            // Se o irmão do nó a ser deletado é vermelho
            if (sibling->color == Color::Red) 
            {
                sibling->color = Color::Black;
                nodeToDelete->ptrParent->color = Color::Red;
                root = leftRotation(root, nodeToDelete->ptrParent);
                sibling = nodeToDelete->ptrParent->ptrRight;
            }

            // Se os filhos do irmão do nó a ser deletado são pretos
            if ((sibling->ptrLeft == nullptr || sibling->ptrLeft->color == Color::Black) && (sibling->ptrRight == nullptr || sibling->ptrRight->color == Color::Black)) 
            {
                sibling->color = Color::Red;
                nodeToDelete = nodeToDelete->ptrParent;
            } 
            else {
                // Se o filho esquerdo do irmão do nó a ser deletado é preto
                if (sibling->ptrRight == nullptr || sibling->ptrRight->color == Color::Black) 
                {
                    if (sibling->ptrLeft != nullptr) 
                    {
                        sibling->ptrLeft->color = Color::Black;
                    }
                    sibling->color = Color::Red;
                    root = rightRotation(root, sibling);
                    sibling = nodeToDelete->ptrParent->ptrRight;
                }
                sibling->color = nodeToDelete->ptrParent->color;
                nodeToDelete->ptrParent->color = Color::Black;

                if (sibling->ptrRight != nullptr) {
                    sibling->ptrRight->color = Color::Black;
                }
                root = leftRotation(root, nodeToDelete->ptrParent);
                nodeToDelete = root;
            }
        } 
        
        else {
            Node<T>* sibling = nodeToDelete->ptrParent->ptrLeft;

            // Se o irmão do nó a ser deletado é vermelho
            if (sibling->color == Color::Red) 
            {
                sibling->color = Color::Black;
                nodeToDelete->ptrParent->color = Color::Red;
                root = rightRotation(root, nodeToDelete->ptrParent);
                sibling = nodeToDelete->ptrParent->ptrLeft;
            }

            // Se os filhos do irmão do nó a ser deletado são pretos
            if ((sibling->ptrLeft == nullptr || sibling->ptrLeft->color == Color::Black) && (sibling->ptrRight == nullptr || sibling->ptrRight->color == Color::Black)) 
            {
                sibling->color = Color::Red;
                nodeToDelete = nodeToDelete->ptrParent;
            } 
            
            else {
                // Se o filho direito do irmão do nó a ser deletado é preto
                if (sibling->ptrLeft == nullptr || sibling->ptrLeft->color == Color::Black) 
                {
                    // Se o filho direito do irmão do nó a ser deletado é preto
                    if (sibling->ptrRight != nullptr) 
                    {
                        sibling->ptrRight->color = Color::Black;
                    }
                    sibling->color = Color::Red;
                    root = leftRotation(root, sibling);
                    sibling = nodeToDelete->ptrParent->ptrLeft;
                }
                sibling->color = nodeToDelete->ptrParent->color;
                nodeToDelete->ptrParent->color = Color::Black;
                
                // Se o filho esquerdo do irmão do nó a ser deletado não é nulo
                if (sibling->ptrLeft != nullptr) 
                {
                    sibling->ptrLeft->color = Color::Black;
                }
                root = rightRotation(root, nodeToDelete->ptrParent);
                nodeToDelete = root;
            }
        }
    }
    if (nodeToDelete != nullptr) {
        nodeToDelete->color = Color::Black;
    }
    return root;
}

template <typename T>
Node<T>* searchNode(Node<T>* root, T data) {
    // Procura o nó com o valor de dados fornecido
    while (root != nullptr && root->data != data) {
        if (data < root->data) {
            root = root->ptrLeft;
        } 
        
        else {
            root = root->ptrRight;
        }
    }
    return root;
}

template <typename T>
int depth(Node<T>* root) {
    if (root == nullptr) return 0;

    // Se o nó tem dois filhos
    if (root->ptrLeft != nullptr && root->ptrRight != nullptr) 
    {
        // Se os filhos têm cores diferentes
        if (root->ptrLeft->color != root->ptrRight->color) 
        {
            // Se o filho esquerdo é vermelho
            if (root->ptrLeft->color == Color::Red) return depth(root->ptrLeft) + 1;
            else return depth(root->ptrRight) + 1;
        }
    }

    // Se o nó tem filhos de cores iguais ou tem um filho
    return std::max(depth(root->ptrLeft), depth(root->ptrRight)) + 1;
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

template int depth(Node<int>*);
template int depth(Node<float>*);
template int depth(Node<double>*);
}