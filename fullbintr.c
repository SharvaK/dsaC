#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>

struct Node {
    int item;
    struct Node *left, *right;
 };

 //Creation of new node
 struct  Node *createNode(char k)
 {
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->item = k;
    node->right = node->left = NULL;
    return node;
}
 
bool isFullBinaryTree(struct Node *root){
    //Checking tree emptiness
    if(root->left == NULL && root->right == NULL)
        return true;

    if((root->left) && (root->right))
        return (isFullBinaryTree(root->left) && isFullBinaryTree(root->right));    
    return false;
}

int main(){
struct Node *root = NULL;
root = createNode(1);
root->left = createNode(2);
root->right = createNode(3);

root->left->left = createNode(4);
root->left->right = createNode(5);

root->left->right->left = createNode(6);
root->left->right->right = createNode(7);

if(isFullBinaryTree(root)){
    printf("It is full binary tree");
}else{
    printf("It is not a full binary tree");
}
}