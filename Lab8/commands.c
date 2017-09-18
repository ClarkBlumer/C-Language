//Name:			Clark Blumer
//PawPrint:		cjbq4f
//Date:			7-21-2014
//Assignment:	Lab8 - A
//LabCode:		Last Lab

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "commands.h"
#include "utility.h"

void create_commands_tree(Command **commands, const char *file) 
{
	FILE *commandFile = fopen(file, "r");
	char buffer[MAX_BUFF_SIZE];
	StringArray *ptr;
	if(!commandFile)
	{
		printf("\nFailed to open commands file!\n");
		exit(1);
	}
	
	while(fgets(buffer, MAX_BUFF_SIZE, commandFile)) {
		ptr = tokenizer(buffer, ",\n");
		printf("%s %s\n", ptr->strings[0], ptr->strings[1]);
		insert_into_commands_tree(commands, ptr->strings);
		free_string_array(ptr);
	}
	fclose(commandFile);
}

void insert_into_commands_tree(Command** node, char** data) 
{
	if(*node == NULL)
	{
		*node = create_command(data);
	}
	else if(strcmp(data[0],(*node)->name) < 0)
		insert_into_commands_tree(&((*node)->left), data);
	else							
		insert_into_commands_tree(&((*node)->right), data);
	
}

//Creates nodes for a Binary Tree
Command* create_command(char **data) 
{
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
		destroy_commands_tree(node->left);
		destroy_commands_tree(node->right);
		free(node);
	}
}

int number_of_commands(Command *node)
{
	if(node == NULL)
		return 0;
	else
		return(number_of_commands(node->left) + number_of_commands(node->right) + 1);
}

void display_commands(Command *node) 
{
	printf("\npickup <item>");
	printf("\nhelp");
	printf("\nquit");
	printf("\nload <file>\n\n");
}
