
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int 	data;
    struct 	node* left;
    struct 	node* right;
}	t_node;
 
int maxDepth(t_node* root) {
    if (root == NULL) {
        return 0;
    } else {
        int leftDepth = maxDepth(root->left);
        int rightDepth = maxDepth(root->right);
        return 1 + (leftDepth > rightDepth ? leftDepth : rightDepth);
    }
}

int searchValue(t_node* root, int target) {
    if (root == NULL) {
        return 0; // Value not found
    } else if (root->data == target) {
        return 1; // Value found
    } else {
        return searchValue(root->left, target) || searchValue(root->right, target);
    }
}

int totalNodes(t_node* root) {
    if (root == NULL) {
        return 0;
    } else {
        return 1 + totalNodes(root->left) + totalNodes(root->right);
    }
}
 
t_node* newNode(int data)
{
    t_node* node;
    node = malloc(sizeof(t_node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return (node);
}
 
int main()
{
    t_node *root;
	
	root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
	root->left->right->left = newNode(6);
	root->right->right = newNode(7);
	root->right->right->left = newNode(8);
	root->right->right->left->right = newNode(9);
    printf("Max depth: %d\n", maxDepth(root));
	printf("Total amount of nodes: %d\n", totalNodes(root));
	printf("Search result: %d\n", searchValue(root, 0));
    return (0);
}