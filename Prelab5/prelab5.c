

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_PLAYERS 9
#define MAX_STR_LEN 25

typedef struct Player_
{
	char name[MAX_STR_LEN];
	int number_of_hits;
	int number_of_strikes;
	struct Player_ *next;
}Player;

int pitch_result(void);
Player* add_player(Player *first_player, const char *name);
void destroy_team(Player *first_player);
void display_line_up(Player *first);
void readFile(Player **lineup, const char *file);

int main(int argc, char *argv[])
{
	if(argc < 2)
		exit(1);

	srand(time(NULL));
	int strikes = 0;
	int hits = 0;
	Player *lineup = NULL; //Pointer to link list *head*
	readFile(&lineup, argv[1]);
	printf("\nLine up for this team is: \n");
	display_line_up(lineup);

	printf("\n\n%s is batting\n", lineup->name);
	for(; strikes < 3; )
	{
		int result = pitch_result();
		if(result) //if 1 ++hits, if 0 ++strikes
		{
			++hits;
			printf("Hit!\n");
		}
		else
		{
			++strikes;
			printf("Strike!\n");
		}
	}
	
	printf("\nScore of game was: %d \n", hits / 4);
	
	destroy_team(lineup);
	free(lineup);	
	return(0);
}

int pitch_result(void)
{
	return(rand() % 2); //return value between 0 and 1
}

Player* add_player(Player *first_player, const char *name)
{
	Player *currentNode = NULL, *ptr = NULL, *newNode = NULL, *temp = NULL;
	// Check to see if there is a list. first_player will be null if list is empty
	// Adds a node to an empty list
	if(first_player == NULL)// Lose the if statement for always adding at beginning of link list
	{
		currentNode = malloc(sizeof(Player)); // currentNode holds the address of created node
		strcpy(currentNode->name, name); // copies name from *name into currentNode->name
		currentNode->next = first_player;// node takes the NULL pointer from first_player
		first_player = currentNode;// first_player then points to current location instead of NULL
		return first_player;// returns new updated value of first_player
	}
	else // append a newly created node at the end of the linked list, then points to the first
	{
		temp = malloc(sizeof(Player));// Allocates memory for a new node
		strcpy(temp->name, name);// Copies string name from *name into temp->name
		currentNode = first_player;
		while(currentNode->next != NULL)// Transverse the link list until we get to the last node
		{
			currentNode = currentNode->next;
		}
		temp->next = NULL;
		currentNode->next = temp;
	}
}


void destroy_team(Player *first_player)
{
	Player *temp = NULL, *ptr = NULL;
	ptr = first_player;
	while(ptr->next != NULL)
	{
		temp = ptr->next;
		ptr->next = temp->next;
	//	free(temp->name);
		free(temp);
		ptr = ptr->next;
	}
	//free(first_player);
}

void display_line_up(Player *first)
{
	Player *ptr = NULL;
	
	// Check for empty list
	if(first == NULL)
	{
		printf("List is empty!\n");
		return;
	}
	// if first isnt null, ptr will store the address of the first node
	ptr = first;
	while(ptr != NULL)
	{
		printf(" %s \n", ptr->name);
		ptr = ptr->next; // ptr will move to next node, if first->next is NULL, NULL condition
	}			 // will be met and break the while loop
	
}

void readFile(Player **lineup, const char *file)
{
	int i = 0;
	char name[MAX_STR_LEN];
	FILE *playerFile = fopen(file, "r");
	if(!playerFile)
	{
	/* Check to make sure the file is not NULL -- fail to open */
		printf("Failed to open stats.txt!\n");
		exit(1);
	}

	for(i = 0; i < MAX_PLAYERS; ++i)
	{
		fscanf(playerFile, "%s", name);
		*lineup = add_player(*lineup, name);
	}
}
