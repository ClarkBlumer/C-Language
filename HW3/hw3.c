/* Name:		Clark Blumer
 * Section:		A
 * Date:		7-13-2014
 * Assignment: 	Homework 3
 * */
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#define MAX_NAME_LEN 25
#define START_DEPTH 0

/*
 * Basic Tree Node Structure
 * */
typedef struct TreeNode_ {
	char name[MAX_NAME_LEN];
	struct TreeNode_ *left;
	struct TreeNode_ *right;
}TreeNode;

/*
 * Basic Stack Structure
 * */
typedef struct StackNode_ {
	TreeNode *t;
	struct StackNode_ *next;
}StackNode;

/*
 * Binary Tree Prototypes
 * */
TreeNode* read_from_file(const char* file);
TreeNode* insert(TreeNode* node, const char *name);	//DONE
TreeNode* create_node(const char *name);			//DONE
int size(TreeNode* node);
void display_tree(TreeNode* node, int depth);
int search_name(TreeNode* node, const char *target);
int max_depth(TreeNode* node);						//DONE
const char* first_name(TreeNode* node);
void mirror_tree(TreeNode* node);					//DONE
TreeNode* trim_tree(TreeNode* node, const char* start_name, const char* end_name);
void destroy_tree(TreeNode* node);					//DONE
int number_of_leaves(TreeNode* node);
int is_tree_balanced(TreeNode* node);
char** flatten_tree(TreeNode* node, int *len_strings);
/*
 * Stack Prototypes
 * */
void push_node(StackNode** top, TreeNode* t);
TreeNode* pop_node(StackNode** top);

int main (int argc, char *argv[]) {
	/*
	 * Check command line parameters
	 * */
	if (argc < 2) {
		printf("%s is missing parameters to run properly\n", argv[0]);
		return 1;
	}
	TreeNode* root = NULL;
	root = read_from_file(argv[1]);
	char buffer[MAX_NAME_LEN];
	printf("Would you like to search for a name? (yes or no): ");
	scanf("%s", buffer);
	getchar();
	
	/*
	 * Query the databse (binary tree)
	 * */

	while (strcmp(buffer,"yes") == 0) {
		printf("Name: ");
		scanf("%s", buffer);
		getchar();
		int result = search_name(root,buffer);
		if (result) {
			printf("\n%s is present in the database", buffer);
		}
		else {
			printf("\n%s is not present in the database", buffer);
		}
		
		printf("\nWould you like to search for a name? (yes or no): ");
		scanf("%s", buffer);
	}
	
	display_tree(root,START_DEPTH);
	/*
	 * Display information about the database
	 * */

	printf("The number of records in the database is %d", size(root));
	printf("\nThe max depth of the database is %d\n", max_depth(root));
	printf("The number of leaf records are %d\n", number_of_leaves(root));
	printf("Is the database balanced (%s)\n", is_tree_balanced(root) ? "yes" : "no");
	printf("The tree mirrored looks like this\n\n");
	/*
	 * Change or flip databse
	 * */

	mirror_tree(root);
	display_tree(root,START_DEPTH);
	mirror_tree(root);
	char buffer2[MAX_NAME_LEN];
	printf("\n\nEnter the lower bound name and upper bound name: ");
	scanf("%s %s", buffer,buffer2);
	printf("Trimming the database from %s to %s\n\n", buffer, buffer2);
	root = trim_tree(root,buffer,buffer2);
	display_tree(root,START_DEPTH);
	int size = 0;
	char** strings = flatten_tree(root,&size);
	int i = 0;
	printf("\nFlattened databse is:\n");

	/*
	 * Memory deallocations
	 * */
	for (i = 0; i < size; ++i) {
		printf("%s\n", strings[i]);
		free(strings[i]);
	}
	free(strings);
	destroy_tree(root);
	return 0;
}

TreeNode* read_from_file(const char* file) 
{
	/* HINT
	 *	TreeNode *t = NULL;
	 *  t = insert(t,buffer);
	 * loop check the return type on fscanf
	 *  insert(t,buffer);
	 */
	 
	/* open file and check for correct file open */
	FILE *inFile = fopen(file, "r");
	if(inFile == NULL)
	{
		printf("\nUnable to open %s\n", file);
		return;
	}
	TreeNode *t = NULL;
	char buffer[MAX_NAME_LEN];
	fscanf(inFile, "%s", buffer); //initial fscanf to fill buffer and clear garbage value
	t = insert(t, buffer); //initial call to insert, sends a NULL node pointer and a name
	while(fscanf(inFile, " %s ", buffer) != EOF)
	{
		insert(t, buffer);
	}
	
	fclose(inFile);//close name file
	return t;//returns t to main
}
TreeNode* insert(TreeNode* node, const char *name) 
{
	if(node == NULL)					//if incoming node is null, return an allocated node
	{							//using the create_node() function.
		return(create_node(name));			//allocated node takes a name from the file and sets
	}							//left and right pointers to null.
	if(strcmp(node->name, name) > 0)			//if compares names to determine where in the
		node->left = insert(node->left, name);		//tree to move the name. if incoming name is
	else							//less than the name, insert into node using left pointer
		node->right = insert(node->right, name);	//else insert into right pointer node
		
	return(node);//returns node pointer
}
TreeNode* create_node(const char *name) 
{
	//function sets up new nodes to be inserted into the binary search tree
	TreeNode *newNode = malloc(sizeof(TreeNode));	//allocate space for newly created node
	strcpy(newNode->name, name);						//copy name from file into node
	newNode->left = NULL;							//set left pointer to null
	newNode->right = NULL;							//set right pointer to null
	return(newNode);							//returns newly allocated node
}
int size(TreeNode* node) 
{
	if(node == NULL)
		return 0;
	else
		return(size(node->left) + size(node->right) + 1);
}

int search_name(TreeNode* node, const char *target) 
{
	if(node == NULL)			
		return 0;
	if(strcmp(node->name, target) == 0)		//if target is equal to node->value, return node->value
		return 1;
	if(strcmp(node->name, target) > 0)		//if node->value is greater than target, move to left side of BST
		return search_name(node->left, target);
	else						//else node->value is less than target and move to right side of BST
		return search_name(node->right, target);
}
int max_depth(TreeNode* node) 
{
	if(node == NULL)
		return 0;
	else
	{
		int leftDepth = max_depth(node->left);	//Calls max_depth until the node is NULL along the left path
		int rightDepth = max_depth(node->right);//Calls max_depth until the node is NULL along the right path
		if(leftDepth > rightDepth) //once stack is filled compares the value of both sides and returns the greater one
			return (leftDepth + 1);
		else
			return (rightDepth + 1);
	}
}

void mirror_tree(TreeNode* node) 
{
	if(node == NULL)
		return;
	else
	{
		TreeNode *temp = NULL;		//temp variable used in swap
		mirror_tree(node->left);	//recursive call to fill stack
		mirror_tree(node->right);
		
		temp = node->left;		//temp takes left node
		node->left = node->right;	//left node takes right node
		node->right = temp;		//right node takes temp
	}
}
TreeNode* trim_tree(TreeNode* node, const char* start_name, const char* end_name) 
{	
	//Base case
	if(node == NULL)
		return NULL;
	
	node->left = trim_tree(node->left, start_name, end_name);  //loading the stack with left tree values
	node->right = trim_tree(node->right, start_name, end_name);//loading the stack with right tree values

	if(strcmp(node->name, start_name) < 0)	//compares node name to start_name. If node->name is less than start_name
	{					//right takes the value of node->right
		TreeNode *right = node->right;	//free the previous node
		free(node);			//returns right's value to be compared to next name on stack
		return(right);
	}
	if(strcmp(node->name, end_name) > 0)	
	{
		TreeNode *left = node->left;
		free(node);
		return(left);
	}
	return node;
}
void destroy_tree(TreeNode* node) 
{
	if(node)
	{					//transvers tree until at the end nodes for
		destroy_tree(node->left);	//left and right trees, then begins to free nodes
		destroy_tree(node->right);
		free(node);
	}
}
int number_of_leaves(TreeNode* node) 
{
	if(node == NULL)
		return 0;
	else if(node->left == NULL && node->right == NULL)	//if left and right pointers of first node are null
		return 1;					//only one node
	else
	{	//recursive calls that either return 0 or 1 for values. Added together to get total number of leafs
		return (number_of_leaves(node->left) + number_of_leaves(node->right));
	}
}

int is_tree_balanced(TreeNode* node) 
{
	int leftHeight;		//holds left value
	int rightHeight;	//holds right value
	
	if(node == NULL)	//one node tree is balanced, returns 1 for true
		return 1;
	leftHeight = max_depth(node->left);		//adds values to stack
	rightHeight = max_depth(node->right);
	
	//check the absolute value of the difference between the left and right sides.
	if(abs(leftHeight - rightHeight) <= 1 && is_tree_balanced(node->left) && is_tree_balanced(node->right))
		return 1;//return 1 for true of tree is balanced (within 1)
	
	//this return signals an unbalanced BST
	return 0;
}

char** flatten_tree(TreeNode* node, int *len_strings)
{
		
}

void push_node(StackNode** top, TreeNode* t) 
{
	StackNode *newNode = malloc(sizeof(StackNode));		
	if(newNode == NULL)
	{
		printf("Unable to allocate StackNode node\n");
		return;
	}
	
	newNode->t = t;		//StackNode newNode->t takes the value of pointer to TreeNode t
	newNode->next = (*top);	//newNode->next gets the deref address of top
	(*top) = newNode;	//top gets the newNode.  
}

TreeNode* pop_node(StackNode** top_ref) 
{
	TreeNode *result;			
	StackNode *top;
	
	if(*top_ref == NULL)			//if top_ref is NULL print error message and return
	{
		printf("top_ref error\n");
		return;
	}
	else					//else top gets value at top_ref
	{					//result gets top->t information
		top = *top_ref;			//top_ref takes top->next info
		result = top->t;		//free top node
		*top_ref = top->next;		//and then return result.  Pops a node off the tree
		free(top);
		return result;
	}
}

/*
 * Used only for padding in the display tree, makes it look pretty
 * */
void padding (char ch, int n)
{

    	int i;
    	for (i = 0; i < n; i++)
        	printf("%c%c%c%c", ch, ch ,ch, ch);

}

/*
 * A Beautiful way to display various sorts of trees, passing this from one generation of students
 * to the next.
 * */
void display_tree (TreeNode *root, int depth) 
{
	TreeNode *current = root;
	if (root == NULL) {
        	padding (' ', depth);
        	printf("-\n");
    	}
    else {
		display_tree(current->left, depth+1);
       	padding(' ', depth);
       	printf ( "%s\n", root->name);
       	display_tree(current->right, depth+1);
    }
}
