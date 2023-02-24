#include "treelib.h"

void nodeOutput(tree * rootNode, valueType spacing){
    if (rootNode == NULL)
        return;

    spacing += 10;

    nodeOutput(rootNode->right, spacing);

    printf("\n");
    for (int i = 10; i < spacing; i++)
        printf(" ");
    printf("%d\n", rootNode->value);

    nodeOutput(rootNode->left, spacing);
}

int getMax(valueType num1, valueType num2){
    return (num1 > num2) ? num1 : num2;
}

int getHeight(tree * node){
    if(node == NULL)
        return 0;
    return node->height;
}

tree * initializeNewNode(valueType value){
    struct Node* newNode = (tree *) malloc(sizeof(tree));
    if(newNode == NULL)
        return newNode;
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

tree * rotateRight(tree * rootNode){

    tree * child_Left;
    tree * child_Right;

    child_Left = rootNode->left;
    child_Right = rootNode->right;

    rootNode->left = child_Left->right;
    child_Left->right = rootNode;
    rootNode = child_Left;

    //update height
    rootNode->right->height = getMax(getHeight(child_Right), getHeight(rootNode->right->left)) + 1;
    rootNode->height = getMax(getHeight(rootNode->left), getHeight(rootNode->right)) + 1;

    return rootNode;
}

tree * rotateLeft(tree * rootNode){
    tree * child_Right;
    tree * child_Left;

    child_Right = rootNode->right;
    child_Left = rootNode->left;

    rootNode->right = child_Right->left;
    child_Right->left = rootNode;
    rootNode = child_Right;

    //update height
    rootNode->left->height = getMax(getHeight(child_Left), getHeight(rootNode->left->right)) + 1;
    rootNode->height = getMax(getHeight(rootNode->right), getHeight(rootNode->left)) + 1;

    return rootNode;
}

tree * insertNode(tree * rootNode, valueType value){
    if(rootNode == NULL) //create new tree
        return initializeNewNode(value);

    if(value < rootNode->value){ //insert to the left (recursion)
        rootNode->left = insertNode(rootNode->left, value);
    }
    else if(value > rootNode->value){ //insert to the right (recursion)
        rootNode->right = insertNode(rootNode->right, value);
    }
    else if(value == rootNode->value){ //do not insert
        return rootNode;
    }

    return (rootNode = balanceTree(rootNode));
};

void nodeOutput_linear(tree * rootNode){
    if(rootNode != NULL){
        printf("%d, ", rootNode->value);
        nodeOutput_linear(rootNode->left);
        nodeOutput_linear(rootNode->right);
    }
};

int contains(tree * node, valueType value){
    if(node == NULL)
        return 0;
    if(node->value == value)
        return 1;
    if(node->value < value)
        return contains(node->right, value);

    return contains(node->left, value);
};

//function taken from the internet for testing purposes, mine was too inefficient
tree * removeNode(tree * rootNode, valueType value){
    if(rootNode == NULL) //create new tree
        return rootNode;
    if(value < rootNode->value){ //search to the left (recursion)
        rootNode->left = removeNode(rootNode->left, value);
    }
    else if(value > rootNode->value){ //search to the right (recursion)
        rootNode->right = removeNode(rootNode->right, value);
    }
    else{ //value found
        //0-1 children:
        if((rootNode->left == NULL) || (rootNode->right == NULL)){
            tree * temp = rootNode->left ? rootNode->left : rootNode->right;

            //no children:
            if(temp == NULL){
                temp = rootNode;
                rootNode = NULL;
            }
            else
                *rootNode = *temp;
            free(temp);
        }
        else{//2 children
            tree* temp = minValueNode(rootNode->right);

            rootNode->value = temp->value;

            rootNode->right = removeNode(rootNode->right, temp->value);
        }
    }

    if(rootNode == NULL)
        return rootNode;

    return (rootNode = balanceTree(rootNode));
};

tree * minValueNode(tree * node){
    tree * current = node;

    while (current->left != NULL)
        current = current->left;

    return current;
}

tree * balanceTree(tree * rootNode){
    //check height difference
    rootNode->height = getMax(getHeight(rootNode->left), getHeight(rootNode->right)) + 1;
    int height_diff = getHeight(rootNode->right) - getHeight(rootNode->left);

    //if tree is unbalanced, check for 4 possible ways to rotate
    //left right case
    if(height_diff < -1 && (getHeight(rootNode->left->left) > getHeight(rootNode->left->right))){
        rootNode = rotateLeft(rootNode->left);
        rootNode = rotateRight(rootNode);
        return rootNode;
    }

    //left left case
    if(height_diff < -1 && (getHeight(rootNode->left->left) < getHeight(rootNode->left->right))){
        rootNode = rotateRight(rootNode);
        return rootNode;
    }

    //right right case
    if(height_diff > 1 && (getHeight(rootNode->right->left) < getHeight(rootNode->right->right))){
        rootNode = rotateLeft(rootNode);
        return rootNode;
    }

    //right left case
    if(height_diff > 1 && (getHeight(rootNode->right->left) > getHeight(rootNode->right->right))){
        rootNode = rotateRight(rootNode->right);
        rootNode = rotateLeft(rootNode);
        return rootNode;
    }

    if(height_diff > 1 && (getHeight(rootNode->right->left) == getHeight(rootNode->right->right))){
        //checks an entire tree (used after a node is deleted)
        rootNode = rotateLeft(rootNode);

        if(rootNode->right != NULL)
            rootNode->right = balanceTree(rootNode->right);
        if(rootNode->left != NULL)
            rootNode->left = balanceTree(rootNode->left);
    }

    if(height_diff < -1 && (getHeight(rootNode->right->left) == getHeight(rootNode->right->right))){
        //checks an entire tree (used after a node is deleted)
        rootNode = rotateRight(rootNode);

        if(rootNode->right != NULL)
            rootNode->right = balanceTree(rootNode->right);
        if(rootNode->left != NULL)
            rootNode->left = balanceTree(rootNode->left);
    }

    return rootNode;
};

tree * deleteTree(tree * rootNode){
    if(rootNode == NULL)
        return NULL;

    if((rootNode->right == NULL) && (rootNode->left == NULL)){
        free(rootNode);
        return NULL;
    }
    rootNode->left = deleteTree(rootNode->left);
    rootNode->right = deleteTree(rootNode->right);
    rootNode = deleteTree(rootNode);

    return NULL;
}

tree * balanceAfterDeletion(tree * rootNode){
    if(rootNode == NULL){
        return rootNode;
    }

    rootNode = balanceTree(rootNode);

    rootNode->left = balanceAfterDeletion(rootNode->left);
    rootNode->right = balanceAfterDeletion(rootNode->right);

    return rootNode;
}

