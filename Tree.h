#pragma once
#include <string>
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

Node* newNode(int); 

Node* insertTreeNode(Node*, int);

Node* fixInsert(Node*, Node*);

Node* leftRotation(Node*, Node*);

Node* rightRotation(Node*, Node*);

void showTree(Node*);

//Node* removeNode(Node*, int);

Node* minNode(Node*);

Node* maxNode(Node*);

void inorderTraversal(Node* root);

bool isValidRedBlackTree(Node* root);
}