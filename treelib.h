#ifndef TREELIB_H_INCLUDED
#define TREELIB_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
typedef int valueType;

typedef struct Node{
    valueType value;
    int height;
    struct Node *left;
    struct Node *right;
} tree;

void nodeOutput(tree *, valueType); //output in a form of a tree

int getMax(valueType, valueType); //returns higher number

int getHeight(tree *); //returns the height of the current node

tree * initializeNewNode(valueType); //creates/initielizes new node

tree * rotateRight(tree *); //balances the tree

tree * rotateLeft(tree *); //balances the tree

tree * insertNode(tree *, valueType); //adds a node to the tree + balances

void nodeOutput_linear(tree *); //output ("1", "2", "3", ..)

int contains(tree *, valueType); //returns 1 if a tree contains specified value, 0 otherwise

tree * balanceTree(tree *); //balances the tree, called automatically after insertion/removal

tree * removeNode(tree *, valueType); //removes the value given if possible

tree * minValueNode(tree *); //returns the node with lowest value

tree * deleteTree(tree * rootNode); //uses free() method

tree * balanceAfterDeletion(tree * rootNode); //use after deleteTree() was called, iterates through tree and rebalances

#endif // TREELIB_H_INCLUDED
