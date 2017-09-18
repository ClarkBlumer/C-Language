#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

typedef struct TreeNode_ {
	int value;
	struct TreeNode_ *left;
	struct TreeNode_ *right;
}TreeNode;


TreeNode* insert(TreeNode* node, const int value);
TreeNode* create_node(const int value);
void destroy(TreeNode* node);
void display(TreeNode* node);

int main (int argc, char *argv[]) {
		if (argc < 3) {
			printf("%s is missing parameters\n", argv[0]);
			return 0;
		}
		const int size = atoi(argv[1]);
		const int root_val = atoi(argv[2]);
		TreeNode* root = NULL;
		int i;
		root = insert(root,root_val);
		printf("Head node is %d\n", root->value);
		for (i = 0; i < size; ++i) {
			int value = rand() % 10 + 1;
			insert(root,value);
		}
		display(root);
		destroy(root);

}

TreeNode* insert(TreeNode *node, const int value)
{
	if(node == NULL)
	{
		return(create_node(value));
	}
	if(value <= node->value)
		node->left = insert(node->left, value);
	else
		node->right = insert(node->right, value);
		
	return(node);
}

TreeNode* create_node(const int value)
{
	TreeNode *currentNode = malloc(sizeof(TreeNode));
	currentNode->value = value;
	currentNode->left = NULL;
	currentNode->right = NULL;
	return(currentNode);
}

void destroy(TreeNode *node)
{
	if(node)
	{
		destroy(node->left);
		destroy(node->right);
		free(node);
	}
}

/* Display function prints values in order */
void display(TreeNode *node)
{
	if(node == NULL)
		return;
	display(node->left);
	printf("%d\n", node->value);
	display(node->right);
	
}

/*void post_order(TreeNode *node)
{
	if(node == NULL)
		return;
	post_order(node->left);
	post_order(node->right);
	printf("%d\n", node->value);
}*/

/*TreeNode* tree_search(TreeNode *node, int value)
{
	if(node == NULL)
		return NULL;
	if(node->value == value)
		return node;
	if(node->value > value)
		return tree_search(node->left, value);
	else
		return tree_search(node->right, value);
}*/
