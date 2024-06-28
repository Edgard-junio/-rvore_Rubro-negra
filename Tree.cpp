#include <iostream>
#include "Tree.h"

using std::cout;
using std::endl;

Tree::Node* Tree::newNode(int iValor)
{
    Tree::Node* ptrTemp = (Node*)malloc(sizeof(Node)); // Criando um nó com o tamanho de um Node

    // Atualizando os parâmetros
    ptrTemp -> iData = iValor;
    ptrTemp -> color = Red;
    ptrTemp -> ptrLeft = nullptr;
    ptrTemp -> ptrRight = nullptr;
    ptrTemp -> ptrParent = nullptr;

    return ptrTemp;

}

Tree::Node* Tree::insertTreeNode(Node* head, int iValor) 
{
    Node* ptrTemp = newNode(iValor);

    if (head == nullptr) 
    {
        changeColor(ptrTemp);
        return ptrTemp;
    }
    if(head -> iData > iValor)
    {
        if(head -> ptrRight == nullptr && head -> ptrLeft != nullptr)
        {
            head = RightRotation(head);
            head = insertTreeNode(head,iValor);
        }
        else if(head -> ptrRight == nullptr && head -> ptrLeft == nullptr)
        {
            head -> ptrRight =  ptrTemp;
            ptrTemp -> ptrParent = head;
        }
        else
        {
            head -> ptrRight = insertTreeNode(head -> ptrRight, iValor);
        }
    }
    else 
    {
        if(head -> ptrLeft == nullptr && head -> ptrRight != nullptr)
        {
            head = leftRotation(head);
            head = insertTreeNode(head,iValor);
        }
        else if(head -> ptrLeft == nullptr && head -> ptrRight == nullptr)
        {
            head -> ptrLeft =  ptrTemp;
            ptrTemp -> ptrParent = head;
        }
        else
        {
            head -> ptrLeft = insertTreeNode(head -> ptrLeft, iValor);
        }
    }
    head = Tree::regulatescolor(head);

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
        // Caso ptrTemp possua filho à esquerda, o parâmetro ptrParent é modificado para ser a antiga raiz
        ptrTemp->ptrLeft->ptrParent = root;
    }

    // Ajustar o pai de root
    if (root->ptrParent == nullptr) 
    {
        // root era a raiz da árvore
        ptrTemp->ptrParent = nullptr;
    }
    else if (root == root->ptrParent->ptrLeft) 
    {
        root->ptrParent->ptrLeft = ptrTemp;
    } 
    else 
    {
        root->ptrParent->ptrRight = ptrTemp;
    }

    ptrTemp->ptrParent = root->ptrParent;
    ptrTemp->ptrLeft = root;
    root->ptrParent = ptrTemp;

    return ptrTemp;
}

Tree::Node* Tree::RightRotation(Node* root) 
{
    if (root == nullptr || root->ptrLeft == nullptr) 
    {
        return root;
    }

    Node* ptrTemp = root->ptrLeft;

    root->ptrLeft = ptrTemp->ptrRight;
    
    if (ptrTemp->ptrRight != nullptr) 
    {
        // Caso ptrTemp tenha filho à direita, atualizamos o parâmetro ptrParent para a antiga raiz
        ptrTemp->ptrRight->ptrParent = root;
    }

    // Ajustar o pai de root
    if (root->ptrParent == nullptr) 
    {
        // root era a raiz da árvore
        ptrTemp->ptrParent = nullptr;
    }
    else if (root == root->ptrParent->ptrRight) 
    {
        root->ptrParent->ptrRight = ptrTemp;
    } 
    else 
    {
        root->ptrParent->ptrLeft = ptrTemp;
    }

    ptrTemp->ptrParent = root->ptrParent;
    ptrTemp->ptrRight = root;
    root->ptrParent = ptrTemp;

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

        // Caso o nó não tenha filho a esquerda
        if(head -> ptrLeft == nullptr)
        {
            ptrTemp = head -> ptrRight;

            ptrTemp -> ptrParent = head -> ptrParent;

            free(head);

            if(ptrTemp ->color == Black) ptrTemp -> color = Red;

            else if(ptrTemp -> color == Red) ptrTemp -> color = Black;

            return ptrTemp;
        }

        // Caso o nó não tenha filho a direita
        else if(head -> ptrRight == nullptr)
        {
            ptrTemp = head -> ptrLeft;

            ptrTemp -> ptrParent = head -> ptrParent;

            free(head);
            
            if(ptrTemp ->color == Black) ptrTemp -> color = Red;

            else if(ptrTemp -> color == Red) ptrTemp -> color = Black;

            return ptrTemp;
        }

        // Caso tenha os dois filhos
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

Tree::Node* Tree::regulatescolor(Node* root)
{
    if (root == nullptr)
    {
        return root;
    }

    // Corrige a cor da raiz para preto
    if (root->ptrParent == nullptr && root -> color == Red)
    {
        root->color = Black;
    }

    //Quando o nó tem os dois filhos
    if(root -> ptrLeft != nullptr && root -> ptrRight != nullptr)
    {
        //1-No vermelho com um filho preto e outro vermelho
        if(root -> color == Red && root -> ptrLeft -> color == Black && root -> ptrRight -> color == Red)
        {
            root = RightRotation(root);
        }
        else if(root -> color == Red && root -> ptrLeft -> color == Red && root -> ptrRight -> color == Black)
        {
            root = leftRotation(root);
        }
        //2-No preto com dois filhos vermelhos
        else if(root -> color == Black  && root -> ptrLeft -> color == Red && root -> ptrRight -> color == Red)
        {
            changeColor(root);
            changeColor(root->ptrLeft);
            changeColor(root->ptrRight);
        }

        root -> ptrLeft = regulatescolor(root -> ptrLeft);
        root -> ptrRight = regulatescolor(root -> ptrRight);
    }

    //Quando o nó é vermelho e não temos um dos filhos
    else if(root -> color == Red && root -> ptrRight != nullptr)
    {
        if(root -> ptrRight -> color == Red)
        {
            changeColor(root -> ptrRight);
        }
        root -> ptrRight = regulatescolor(root -> ptrRight);
    }

    else if(root -> color == Red && root -> ptrLeft != nullptr)
    {
        if(root -> ptrLeft -> color == Red)
        {
            changeColor(root -> ptrLeft);
        }
        root -> ptrLeft = regulatescolor(root -> ptrLeft);
    }
    return root;
}
