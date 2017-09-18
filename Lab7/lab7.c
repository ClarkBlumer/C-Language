/* Name:	Clark Blumer
 * Date:	7-14-2014
 * Subcode:	Dungeon Escape
 * */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

typedef struct TreeNode_ {
	int value;
	struct TreeNode_ *left;
	struct TreeNode_ *right;
}TreeNode;


TreeNode* insert(TreeNode* node, const int value);	//DONE
TreeNode* create_node(const int value);				//DONE
void destroy(TreeNode* node);						//DONE
void display(TreeNode* node);						//DONE
int min_value(TreeNode* node); 						//DONE
int tree_sum(TreeNode* node);						//DONE
void mirror(TreeNode* node);
int search(TreeNode* node, const int target);		//DONE

int main (int argc, char *argv[]) {
		if (argc < 4) {
			printf("%s is missing parameters\nShould be %s <size> <root value> <possible numbers>\n", argv[0]);
			return 0;
		}
		srand(time(NULL));
		const int size = atoi(argv[1]);
		const int root_val = atoi(argv[2]);
		const int possible_numbers = atoi(argv[3]);
		TreeNode* root = NULL;
		int i;
		root = insert(root,root_val);
		printf("Head node is %d\n", root->value);
		for (i = 0; i < size; ++i) {
			int value = rand() % possible_numbers + 1;
			insert(root,value);
		}
		int num;
		int cont;
		do {
			printf("Enter a number to search for: ");
			scanf("%d", &num);
			if (search(root,num)) {
				printf("%d is inside the tree\n");
			}
			else {
				printf("%d is not inside the tree\n");
			}
			printf("continue?(1(yes) or 0(no))");
			scanf("%d", &cont);
		}while (cont);
		display(root);
		printf("The min value of the tree is %d\n", min_value(root));
		printf("Mirroring the tree...\n");
		mirror(root);
		display(root);
		printf("Sum of this tree is %d\n", tree_sum(root));
		destroy(root);

}

/* insert function inserts nodes into the Binary Search Tree based on the node->value */
TreeNode* insert(TreeNode *node, const int value)
{
	if(node == NULL)				//if incoming node is null, return an allocated node
	{								//using the create_node() function.
		return(create_node(value));	//allocated node takes a name from the file and sets
	}								//left and right pointers to null.
	if(value <= node->value)						//if compares the values to determine where in the
		node->left = insert(node->left, value);		//tree to move the node. if incoming value is
	else											//less than the node value, insert into node using left pointer
		node->right = insert(node->right, value);	//else insert into right pointer node
		
	return node;
}

/* create_node function allocates space and sets parameters for new nodes */
TreeNode* create_node(const int value)
{
	TreeNode *currentNode = malloc(sizeof(TreeNode));	//allocate space for newly created node
	currentNode->value = value;							//copy name from file into node
	currentNode->left = NULL;							//set left pointer to null
	currentNode->right = NULL;							//set right pointer to null
	return currentNode;									//returns newly allocated node
}

/* destroy function frees every node in the Binary Search Tree */
void destroy(TreeNode *node)
{
	if(node)					//recursively calls the destroy function
	{							//to free allocated nodes
		destroy(node->left);	//transverses left side to free nodes 
		destroy(node->right);	//transverses right side to free nodes
		free(node);				//once stack is made, free starts freeing nodes
	}
}

/* Display function prints values in order */
void display(TreeNode *node)
{
	if(node == NULL)			//base case, once node is NULL return control to MAIN
		return;
	display(node->left);		//recursive call to display left side.
	printf("%d\n", node->value);
	display(node->right);		//recursive call to display right side.
	
}

/* search function goes through the tree looking for target value */
int search(TreeNode *node, const int target)
{
	if(node == NULL)			
		return;
	if(node->value == target)	//if target is equal to node->value, return node->value
		return node->value;
	if(node->value > target)	//if node->value is greater than target, move to left side of BST
		return search(node->left, target);
	else						//else node->value is less than target and move to right side of BST
		return search(node->right, target);
}

/* min_value function returns the left most value */
int min_value(TreeNode* node)
{
	if(node->left == NULL)	//Once node->left points to NULL, signals left most node
		return node->value; //returns the value of left most node
	min_value(node->left);	//recursive call to continue to move through BST until left pointer points to NULL
}

/* tree_sum returns the value of every node->value added together */ 
int tree_sum(TreeNode* node)
{
	if(node == NULL)//base case, return 0 for a null node
		return 0;
	else
		//returns node value plus recursively call for all nodes left and right
		return node->value + tree_sum(node->left) + tree_sum(node->right);		
}

/* mirror function swaps the order of the numbers */
void mirror(TreeNode* node)
{
	if(node == NULL)
		return;
}