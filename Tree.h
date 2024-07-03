#pragma once
#include <string>

namespace Tree 
{

    enum Color { Black, Red };

    template <typename T>
    struct Node 
    {
        int data;
        Color color;
        Node<T>* ptrLeft;
        Node<T>* ptrRight;
        Node<T>* ptrParent;
    };

    template <typename T>
    Node<T>* newNode(T); 

    template <typename T>
    Node<T>* insertTreeNode(Node<T>*, T);

    template <typename T>
    Node<T>* fixInsert(Node<T>*, Node<T>*);

    template <typename T>
    Node<T>* leftRotation(Node<T>*, Node<T>*);

    template <typename T>
    Node<T>* rightRotation(Node<T>*, Node<T>*);

    template <typename T>
    void showTree(Node<T>*);

    template <typename T>
    Node<T>* minNode(Node<T>*);

    template <typename T>
    Node<T>* maxNode(Node<T>*);

    template <typename T>
    void inorderTraversal(Node<T>* root);

    template <typename T>
    bool isValidRedBlackTree(Node<T>* root);

    template <typename T>
    Node<T>* removeNode(Node<T>*, T);

    template <typename T>
    Node<T>* transplant(Node<T>*, Node<T>*, Node<T>*);

    template <typename T>
    Node<T>* fixDelete(Node<T>*, Node<T>*);

    template <typename T>
    Node<T>* searchNode(Node<T>*, T);
}