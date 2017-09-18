//Name:			Clark Blumer
//Pawprint:		cjbq4f
//Date:			7-07-2014
//Assignment:	Lab 6
//Lab Code: 	List of List

// Libraries 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Structures
typedef struct MatrixNode_
{
	int value;
	struct MatrixNode_ *next_row;
	struct MatrixNode_ *next_col;
}MatrixNode;

// Prototypes
void create_linked_list_matrix(MatrixNode**, const int rows, const int cols);
MatrixNode* create_node();
void display_matrix(MatrixNode*);
void destroy_linked_list_matrix(MatrixNode**);
void add_two_matrices_together(MatrixNode* head_a, MatrixNode* head_b, MatrixNode* result);
int find_total_value_of_the_matrix(MatrixNode* head);
void write_result_to_file(MatrixNode* results);

int main (int argc, char *argv[]) 
{
	if (argc < 3) {
		exit(1);
	}
	srand(time(NULL));
	const int rows = atoi(argv[1]);
	const int cols = atoi(argv[2]);
	MatrixNode* head_a = NULL;
	MatrixNode* head_b = NULL;
	MatrixNode* result = NULL;
	
	printf("Matrix A\n");
	create_linked_list_matrix(&head_a,rows,cols);
	display_matrix(head_a);
	printf("Total value of Matrix A is %d\n",find_total_value_of_the_matrix(head_a));
	printf("Matrix B\n");
	create_linked_list_matrix(&head_b,rows,cols);
	display_matrix(head_b);
	printf("Total value of Matrix B is %d\n",find_total_value_of_the_matrix(head_b));

	create_linked_list_matrix(&result,rows,cols);

	add_two_matrices_together(head_a,head_b,result);
	write_result_to_file(result);

	destroy_linked_list_matrix(&head_a); 
	destroy_linked_list_matrix(&head_b);
	destroy_linked_list_matrix(&result);
}

void create_linked_list_matrix(MatrixNode **head, const int rows, const int cols)
{
	int i, j;
	/* allocates space for the head node  */
	*head = create_node(); 
	
	MatrixNode *currentRow = *head;
	MatrixNode *currentCol = NULL;

	for(i = 1; i < rows; ++i)
	{
		currentRow->next_row = create_node();//creates the link list that holds link lists
		currentRow = currentRow->next_row;
	}
	currentRow = *head; //reset currentRow pointer to point back to head to fill nodes with link lists
	for( ; currentRow != NULL; currentRow = currentRow->next_row)
	{
		currentCol = currentRow; //start at head node
		for(j = 1; j < cols; ++j)
		{
			currentCol->next_col = create_node(); //creates the nodes in the linked lists of the head linked list
			currentCol = currentCol->next_col;
		}
	}
	

}

MatrixNode* create_node()
{
	MatrixNode *newNode = malloc(sizeof(MatrixNode)); //allocates space for new node
	newNode->value = rand() % 100 + 1; //fills value area of node with random number between 1 - 100
	newNode->next_col = NULL; //sets next col pointer to point to null
	newNode->next_row = NULL; //sets next row pointer to point to null
	return newNode; //returns created node with filled elements
}

void display_matrix(MatrixNode *head)
{
	MatrixNode *currentRow = head;
	MatrixNode *currentCol = NULL;
	// Check for empty list
	if(head == NULL)
	{
		printf("List is empty!\n");
		return;
	}
	for(; currentRow != NULL; currentRow = currentRow->next_row)
	{
		printf("%3d ", currentRow->value);//prints row values
		for(currentCol = currentRow->next_col; currentCol != NULL; currentCol = currentCol->next_col)
			printf("%3d ", currentCol->value); //inner for loop to print col values
		printf("\n");//newline after inner for completes
	}
}

void destroy_linked_list_matrix(MatrixNode **head)
{
	MatrixNode *currentRow = *head;
	MatrixNode *currentCol = NULL;
	MatrixNode *freeMe = NULL;// temp variable to hold address to be freed
	
	while(currentRow != NULL)
	{
		currentCol = currentRow->next_col; // currentCol takes the address of the next node
		while(currentCol != NULL)// while currentCol isn't NULL
		{
			freeMe = currentCol;// freeMe takes the address of currentCol
			currentCol = currentCol->next_col;//move currentCol address forward in the list
			free(freeMe);//frees freeMe's address 
		}
		freeMe = currentRow;// freeMe takes the address of currentRow
		currentRow = currentRow->next_row;//currentRow moves to next row node
		free(freeMe);//frees node that was located at currentRow
	}
	
	
}

void add_two_matrices_together(MatrixNode* head_a, MatrixNode* head_b, MatrixNode* result)
{
	
}

int find_total_value_of_the_matrix(MatrixNode* head)
{	
	/* 	function is identical to display function except instead of printing
		the values to screen, add them to total. */
	int total = 0;
	MatrixNode *currentRow = head;
	MatrixNode *currentCol = NULL;

	for(; currentRow != NULL; currentRow = currentRow->next_row)
	{
		total += currentRow->value; // total rows
		for(currentCol = currentRow->next_col; currentCol != NULL; currentCol = currentCol->next_col)
			total += currentCol->value; // total cols
	}
	return total;
}

void write_result_to_file(MatrixNode* results)
{
	FILE *outFile = fopen("results.txt", "w");
	
	
	
	fclose(outFile);
}