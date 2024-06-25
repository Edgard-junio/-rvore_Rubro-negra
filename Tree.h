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

Node* newNode(int iValor, Color color);

void insertTreeNode(Node** head, int iValor);

void showTree(Node* head);

Node searchNode(Node* head, int Ivalor);

}