
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int 	data;
    struct 	node* left;
    struct 	node* right;
}	t_node;
 
int maxDepth(t_node *node)
{
	/* NULL error check */
    if (node == NULL)
        return (0);
    else 
	{
		/* Get left and right depths */
        int lDepth = maxDepth(node->left);
        int rDepth = maxDepth(node->right);

		/* If left > right => left + 1 */
        if (lDepth > rDepth)
            return (lDepth + 1);

		/* If left < right => right + 1 */
        else
            return (rDepth + 1);
    }
}

int totalNodes(t_node* node)
{
    if (node == NULL)
        return (0);
    else 
	{
        int lDepth = totalNodes(node->left);
        int rDepth = totalNodes(node->right);
		return (lDepth + rDepth + 1); // for total nodes
    }
}
int searchValue(t_node* node, int value)
{
    if (node == NULL)
        return (0);
    else 
	{
		if (node->data == value)
			return (1);
        int lDepth = searchValue(node->left, value);
        int rDepth = searchValue(node->right, value);
		if (lDepth || rDepth)
			return (1);
		return (0);
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