
#include <stdio.h>
#include <stdlib.h>
 
typedef struct node {
    int 	data;
    struct 	node* left;
    struct 	node* right;
}	t_node;
 
int maxDepth(t_node* node)
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
    printf("Depth of Btree is %d\n", maxDepth(root));
    return (0);
}
