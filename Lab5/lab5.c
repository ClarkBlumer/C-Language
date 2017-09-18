//Name:		Clark Blumer
//Pawprint:	cjbq4f
//Date:		6-30-2014
//LabCode:	bombastic
/* Implement a singular circle linked list. Practice more with
   Linked lists and begin to tunderstand the Queue (ADT) */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_PLAYERS 9
#define MAX_STR_LEN 25

typedef struct Player_{
	char name[MAX_STR_LEN];
	int number_of_hits;
	int number_of_outs;
	struct Player_ *next;
}Player;

int batting(Player *player); 
int pitch_result(void); 
Player* add_player(Player *first_player, const char *name);
Player* pull_player(Player *first_player);
void destroy_team(Player *first_player,Player* next); 
void display_lineup(Player* first, Player* next);
void readFile(Player** lineup, const char* file);
void update_player_stats(Player *lineup, Player *target); 
void display_player_stats(Player* first); 

int main (int argc, char *argv[]) {
	if (argc < 2){
		exit(1);	
	}
	srand(time(NULL));
	int outs = 0;
	int hits = 0;
	Player *lineup = NULL;
	readFile(&lineup,argv[1]);
	printf("\nLine up for this team is: \n");
	display_lineup(lineup,lineup);
	
	for (; outs < 27; ) {
			
		Player * player = pull_player(lineup);
		int result = batting(player);
		if (result) {
			player->number_of_hits++;
			++hits;
		}
		else{
			player->number_of_outs++;
			++outs;
		}
		//update_player_stats(lineup,player); REQUIRED FOR BONUS if attempting
		//free(player);
		
	}
	//display_player_stats(lineup); REQUIRED FOR BONUS uncomment if attempting
	printf("\nScore of game was: %d \n", hits/4);
	destroy_team(lineup,lineup);
	
	return 0;
}

void readFile(Player** lineup, const char* file) {
	
	int i = 0;
	char player_name[MAX_STR_LEN];
	FILE *playerFile = fopen(file, "r");
	if(!playerFile)
	{
	/* Check to make sure the file is not NULL -- fail to open */
		printf("Failed to open stats.txt!\n");
		exit(1);
	}
	/* Loops through number of players and adds players to linked list */
	for(i = 0; i < MAX_PLAYERS; ++i)
	{
		/* Since file is formated with underscores instead of spaces
			used fscanf to get the single line */
		fscanf(playerFile, "%s", player_name);
		*lineup = add_player(*lineup, player_name); //lineup gets the returned value of add_player which is a pointer
	}		
	
	fclose(playerFile);
}

void display_lineup(Player* first,Player* next) {

	printf("%s \n", first->name); 		//prints name at first->name
	if(first->next == next)				//check to see if first->next is equal to head
		return; //when they are equal return control to function that called display_lineup
	display_lineup(first->next, next);	//recursive call with next node and compares to head again
}

int batting(Player *player) {
	
	printf("\n%s is now batting\n",player->name);
	int strikes = 0;
	int result = 0;
	int walks = 0;
	for ( ;strikes < 3;) {
		result = pitch_result();
		if (result == 0)
			++strikes;
		else if (result == 2) {
			return 1;
		}
		else if (result == 1 && walks == 3){
			printf("Walked!\n");
			return 1;
		}
		else if (result == 1) {
			++walks;
		}

	}
	
	return 0;
}

int pitch_result(void) {
	//Create random value that allows for 50% strikes, 25% hit
	// and 25% ball
	int result = rand() % 4; //value between 0 - 3
	if(result >= 2)
	{
		printf("Strike!\n");
		return(0);
	}
	else if(result >= 1)
	{
		printf("Ball!\n");
		return(1);
	}
	printf("Hit!\n");
	return(2);
}


Player* add_player(Player *first_player, const char *player_name){
	
	Player *currentNode;
	
	currentNode = first_player;
	// Check to see if there is a list. first_player will be null if list is empty
	// Adds a node to an empty list
	Player *newNode = malloc(sizeof(Player)); // currentNode holds the address of created node
	strcpy(newNode->name, player_name); // copies name from *name into currentNode->name
	newNode->number_of_hits = 0; // sets player's #of hits to 0
	newNode->number_of_outs = 0; // sets player's # of outs to 0
	if(first_player == NULL)// Lose the if statement for always adding at beginning of link list
	{
		newNode->next = newNode;// node takes the NULL pointer from first_player
		return newNode;// returns new updated value of first_player
	}
	else
	{
		while(currentNode->next != first_player)// Transverse the link list until we get to the last node
		{
			currentNode = currentNode->next;
		}	
	}
	currentNode->next = newNode;
	newNode->next=first_player;
	return first_player;
	
} 

Player* pull_player(Player *first_player){
	

}

void destroy_team(Player *first, Player* next) {	
	Player *ptr;
	ptr = first;
	free(ptr);
	if(first->next == next)//check to see if first->next is equal to head
		return;
	destroy_team(first->next, next);
}

/*BONUS PART*/
void update_player_stats(Player *lineup, Player *target) {


}
/* BONUS PART*/
void display_player_stats(Player* first) {


}
