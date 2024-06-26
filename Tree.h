#pragma once

namespace Tree 
{

enum Color { Black, Red };

struct Node 
{
    int iData;
    Color color;
    Node* ptrLeft;
    Node* ptrRight;
    Node* ptrParent;
};

Node* newNode(int iValor); 

Node* insertTreeNode(Node* head, int iValor);

Node* leftRotation(Node* root);

Node* RightRotation(Node* root);

void showTree(Node* head);

Node* removeNode(Node* head, int ivalor);

void changeColor(Node* root); 

}