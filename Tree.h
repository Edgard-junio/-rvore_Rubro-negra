#pragma once

namespace Tree 
{

enum Color { Black, Red };

struct Node 
{
    int data;
    Color color;
    Node* ptrLeft;
    Node* ptrRight;
    Node* ptrParent;
};

Node* newNode(int iValor); 

Node* insertTreeNode(Node* head, int iValor);

Node* fixInsert(Node*, Node*);

Node* leftRotation(Node*, Node*);

Node* rightRotation(Node* root, Node* ptrTemp);

// void showTree(Node* head);

// Node* removeNode(Node* head, int ivalor);

}