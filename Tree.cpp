#include <iostream>
#include "Tree.h"

using std::cout;
using std::endl;

Tree::Node* Tree::newNode(int iValor)
{
    Tree::Node* ptrTemp = (Node*)malloc(sizeof(Node)); //Criando um nó com o tmanho de um Node

    //Atualizando os parametros
    ptrTemp -> iData = iValor;
    ptrTemp -> color = Red;
    ptrTemp -> ptrLeft = nullptr;
    ptrTemp -> ptrRight = nullptr;
    ptrTemp -> ptrParent = nullptr;

    return ptrTemp;

}

Tree::Node* Tree::insertTreeNode(Node* head, int iValor) {
    Node* ptrTemp = newNode(iValor);

    if (head == nullptr) {
        changeColor(ptrTemp);
        return ptrTemp;
    }

    if (iValor < head->iData) {
        if (head->ptrLeft == nullptr) {
            head->ptrLeft = ptrTemp;
            ptrTemp->ptrParent = head;
        } else {
            head->ptrLeft = insertTreeNode(head->ptrLeft, iValor);
        }
    } else {
        if (head->ptrRight == nullptr) {
            head->ptrRight = ptrTemp;
            ptrTemp->ptrParent = head;
        } else {
            head->ptrRight = insertTreeNode(head->ptrRight, iValor);
        }
    }

    // Call function to regulate color properties of the tree
    // regulatescolor(head);

    return head;
}

Tree::Node* Tree::leftRotation(Node* root) 
{
    if (root == nullptr || root->ptrRight == nullptr) 
    {
        return root;
    }
 
    Node* ptrTemp = root->ptrRight;
    root->ptrRight = ptrTemp->ptrLeft;

    if (ptrTemp->ptrLeft != nullptr) 
    {
        //coso ptrTemp possua filho a esquerda o parametro prtParent é modificado par ser a antiga raiz
        ptrTemp->ptrLeft->ptrParent = root;
    }

    ptrTemp->ptrParent = nullptr;
    ptrTemp->ptrLeft = root;
    root->ptrParent = ptrTemp;

    changeColor(ptrTemp);
    changeColor(ptrTemp->ptrLeft);

    return ptrTemp;
}

Tree::Node* Tree::RightRotation(Node* root) 
{
    if(root == nullptr || root -> ptrLeft == nullptr) return root;

    Node* ptrTemp = root -> ptrLeft;

    root -> ptrLeft = ptrTemp -> ptrRight;
    
    if(ptrTemp -> ptrRight != nullptr) 
    {
        //Caso  ptrTemp tenha filho a direita atualizamos o parametro ptrParent para a antiga raiz
        ptrTemp -> ptrRight -> ptrParent = root;
    }

    ptrTemp -> ptrParent = nullptr;
    ptrTemp -> ptrRight = root;
    root -> ptrParent = ptrTemp;

    changeColor(ptrTemp);
    changeColor(ptrTemp->ptrRight);

    return ptrTemp;
}

void Tree::showTree(Node* head)
{
    if(head == nullptr)
    {
        return;
    }
    
    cout << "Valor do nó = " << head -> iData << " Sua cor é " << (head -> color == Red ? "\033[1;31mRed\033[0m" : "\033[1;30mBlack\033[0m") << endl;
    
    Tree::showTree(head -> ptrLeft);
    Tree::showTree(head -> ptrRight);
}

Tree::Node* Tree::removeNode(Node* head, int ivalor)
{
    if(head == nullptr) return head;

    if(head -> iData < ivalor) head -> ptrLeft = removeNode(head -> ptrLeft , ivalor);

    else if(head -> iData > ivalor) head -> ptrRight = removeNode(head -> ptrRight , ivalor);

    else
    {
        Node* ptrTemp = nullptr;

        //Caso o nó não tenha filho a esquerda
        if(head -> ptrLeft == nullptr)
        {
            ptrTemp = head -> ptrRight;

            ptrTemp -> ptrParent = head -> ptrParent;

            free(head);

            if(ptrTemp ->color == Black) ptrTemp -> color = Red;

            else if(ptrTemp -> color == Red) ptrTemp -> color = Black;

            return ptrTemp;
        }

        //caso o nó não tenha filho a direita
        else if(head -> ptrRight == nullptr)
        {
            ptrTemp = head -> ptrLeft;

            ptrTemp -> ptrParent = head -> ptrParent;

            free(head);
            
            if(ptrTemp ->color == Black) ptrTemp -> color = Red;

            else if(ptrTemp -> color == Red) ptrTemp -> color = Black;

            return ptrTemp;
        }

        //caso tenha os dois filhos
        Node* current = head->ptrRight;

        while (current -> ptrRight != nullptr) current = current -> ptrRight;

        head -> iData = current -> iData;

        head -> ptrRight = removeNode(head ->ptrRight , current -> iData);
    }

    return head;
}

void Tree::changeColor(Node* root)
{
    if(root == nullptr) return;

    if(root -> color == Red) root -> color = Black;

    else root -> color = Red;

}
