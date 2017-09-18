#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "commands.h"
#include "utility.h"

void create_commands_tree(Command **commands, const char *file) 
{
	FILE *commandFile = fopen(file, "r");
	StringArray *buffer;
	StringArray *buffer2;
	if(!commandFile)
	{
		printf("\nFailed to open commands file!\n");
		exit(1);
	}
	int i = 0;

}

void insert_into_commands_tree(Command** node, char** data) 
{

}

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

}

void destroy_commands_tree(Command* node) 
{

}

void display_commands(Command *node) 
{

}
