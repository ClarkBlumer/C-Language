//Name:			Clark Blumer
//PawPrint:		cjbq4f
//Date:			7-22-2014
//Assignment:	Homework 4 - Section A

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "commands.h"
#include "utility.h"

void create_commands_tree(Command **commands, const char *file) 
{
	/* Variable delcarations */
	FILE *commandFile = fopen(file, "r");
	char buffer[MAX_BUFF_SIZE];//buffer array used to hold input
	StringArray *ptr;//StringArray ptr used to hold tokens returned by tokenizer
	if(!commandFile)
	{
		printf("\nFailed to open commands file!\n");
		exit(1);
	}
	
	/*	while fgets doesn't return a NULL value ptr gets the string returned
		by tokenizer. The returned string is then passed to the insert_into_commands_tree
		where it will be placed in the Binary Tree alphabetically.
		Then free the ptr because it is no longer needed.  Continue until fgets return NULL.*/
	while(fgets(buffer, MAX_BUFF_SIZE, commandFile)) {
		ptr = tokenizer(buffer, ",\n");
		//printf("%s %s\n", ptr->strings[0], ptr->strings[1]);
		insert_into_commands_tree(commands, ptr->strings);
		free_string_array(ptr);
	}
	fclose(commandFile);
}

void insert_into_commands_tree(Command** node, char** data) 
{
	//inserts Command nodes into a Binary Tree alphabetically.
	if(*node == NULL)
	{
		//if node is NULL, call create_command to allocate a node
		*node = create_command(data);
	}
	else if(strcmp(data[0],(*node)->name) < 0)
		insert_into_commands_tree(&((*node)->left), data);
	else							
		insert_into_commands_tree(&((*node)->right), data);
}

Command* create_command(char **data) 
{
	//Allocates and initializes values for a Command node
	//to be inserted into a Binary Tree of Command nodes.
	Command *node = malloc(sizeof(Command));
	strcpy(node->name, data[0]);
	node->expected_param_count = atoi(data[1]);
	node->left = NULL;
	node->right = NULL;
	return node;
}

Command* get_command(Command *node, const char *command) 
{
	if(node == NULL)			
		return NULL;
	if(strcmp(node->name, command) == 0)		//if target is equal to node->value, return node->value
		return node;
	if(strcmp(command,node->name) < 0)			//if node->value is greater than target, move to left side of BST
		return get_command(node->left, command);
	else//else node->value is less than target and move to right side of BST
		return get_command(node->right, command);
}

void destroy_commands_tree(Command* node) 
{
	if(node)
	{	
		//recursive call adds nodes to the stack and then
		//frees each node as it goes through the stack.
		destroy_commands_tree(node->left);
		destroy_commands_tree(node->right);
		free(node);
	}
}

void display_commands(Command *node) 
{
	printf("\npickup <item>");
	printf("\nhelp");
	printf("\nquit");
	printf("\nload <file>\n\n");
}
