/*
 * functions.c
 *
 *  Created on: 4 Mar 2017
 *      Author: aidan
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include "functions.h"
#define MAX_SIZE 50
int i, j, c;

void assignSlots(int numSlots, char* slotsType[], struct slot slots[])
{
	for(i=0; i<numSlots; i++)
	{
		j=rand()%3; // Use a random number between 0 and 2 as these correspond with the entries in the slotsArray array
		slots[i].id=i;
		strcpy(slots[i].type, slotsType[j]);
		slots[i].occupied=false; // Initialise slots as empty, so no two players can be in the same slot
	}
}

void playerPosition(int numPlayers, int numSlots, struct player players[], struct slot slots[])
{
	for(i=0; i<numPlayers; i++)
	{
		j=rand()%numSlots;
		while(slots[i].occupied==true) // Prevents 2 or more players being placed in the same slot
		{
			j=rand()%numSlots;
		}
		players[i].pos=j;
		//slots[j].occupied=true; // Marks the slot as being occupied once a player is in it
	}
}

void playerInit(int numPlayers, struct player players[], char* playerType[])
{
	for(i=0; i<numPlayers; i++)
	{
		printf("Enter the name of player %d: ", i+1);
		scanf(" %[^\n]", players[i].name); // " %[^\n]" scans everything until the enter key is pressed, including spaces and \n characters
		printf("Choose the class for player %d:\n[1] Elf\n[2] Human\n[3] Ogre\n[4] Wizard\n", i+1);
		scanf("%d", &c);
		strcpy(players[i].type, playerType[c-1]); // Take 1 away as this then corresponds with the values of the array pointers for playerType
	}
	playerStats(players, playerType, numPlayers);
}

void playerStats(struct player player[], char* playerType[], int numPlayers)
{
	for(i=0; i<numPlayers; i++)
	{
		for(j=0; j<4; j++) // Checks the class the player has
		{
			if(strcmp(player[j].type, playerType[i])==0) // Chooses the correct case for the player type
			{
				switch(j)
				{
				case 0: // Elf
					player[i].health=100;
					player[i].magic=51+(rand()%29);
					player[i].smartness=70+(rand()%31);
					player[i].strength=1+(rand()%50);
					player[i].dexterity=1+(rand()%100);
					player[i].luck=60+(rand()%41);
					break;

				case 1: // Human
					player[i].health=100;
					player[i].dexterity=1+(rand()%100);
					player[i].luck=1+(rand()%100);
					if(player[i].dexterity+player[i].luck > 102)
					{
						player[i].magic=1+(rand()%100); // Stop the attributes from exceeding the cap for the Human type
					}
					else
					{
						player[i].magic=1+(rand()%98);
					}
					player[i].smartness=1+(rand()%(299-player[i].dexterity-player[i].luck-player[i].magic));
					if(player[i].smartness>100)
					{
						player[i].smartness=100;
					}
					player[i].strength=1+(rand()%(299-player[i].dexterity-player[i].luck-player[i].magic-player[i].smartness));
					if(player[i].strength>100)
					{
						player[i].strength=100;
					}
					break;

				case 2: // Ogre
					player[i].health=100;
					player[i].magic=0;
					player[i].smartness=1+(rand()%20);
					player[i].strength=80+(rand()%21);
					player[i].dexterity=80+(rand()%21);
					player[i].luck=1+(rand()%(50-player[i].smartness));
					break;

				case 3: // Wizards
					player[i].health=100;
					player[i].magic=80+(rand()%21);
					player[i].smartness=90+(rand()%11);
					player[i].strength=1+(rand()%20);
					player[i].dexterity=1+(rand()%100);
					player[i].luck=50+(rand()%51);
					break;
				}
			}
		}
	}
}

void playerMove(struct player players[], struct slot slots[], int numSlots, int *c, int a)
{
	int moveChoice=-1;
	if((slots[players[a].pos-1].occupied==true) && (slots[players[a].pos+1].occupied==true)) // If both adjacent slots are occupied, they can't move
	{
		printf("You are unable to move, you must attack.\n");
		*c=2;
	}
	else if((slots[players[a].pos-1].occupied==true) && (players[a].pos==numSlots-1)) // If the player is on the rightmost side of the board (occupied)
	{
		printf("You are unable to move, you must attack.\n");
		*c=2;
	}
	else if((slots[players[a].pos+1].occupied==true) && (players[a].pos==0)) // If the player is on the leftmost side of the board (occupied)
	{
		printf("You are unable to move, you must attack.\n");
		*c=2;
	}
	else if((slots[players[a].pos-1].occupied==true) || (players[a].pos==0)) // If the player can't move left
	{
		slots[players[a].pos].occupied=false;
		players[a].pos++;
		slots[players[a].pos].occupied=true;
		printf("You have moved to the right as you cannot move to the left.\nYou are now in position %d and type %s.\n", players[a].pos+1, slots[players[a].pos].type);
	}
	else if((slots[players[a].pos+1].occupied==true) || (players[a].pos==numSlots-1)) // If the player can't move right
	{
		slots[players[a].pos].occupied=false;
		players[a].pos--;
		slots[players[a].pos].occupied=true;
		printf("You have moved to the left as you cannot move to the right.\nYou are now in position %d and type %s.\n", players[a].pos+1, slots[players[a].pos].type);
	}
	else
	{
		while(moveChoice<0) // Simple error checking
		{
			printf("Would you like to move to the left[1] (%s) or to the right[2] (%s)?\n", slots[players[a].pos-1].type, slots[players[a].pos+1].type);
			scanf("%d", &moveChoice);
			if(moveChoice==1) // Move to the left
			{
				slots[players[a].pos].occupied=false;
				players[a].pos--;
				slots[players[a].pos].occupied=true;
				printf("You have moved to the left.\nYou are now in position %d and type %s.\n", players[a].pos+1, slots[players[a].pos].type);
			}
			else if(moveChoice==2) // Move to the right
			{
				slots[players[a].pos].occupied=false;
				players[a].pos++;
				slots[players[a].pos].occupied=true;
				printf("You have moved to the right.\nYou are now in position %d and type %s.\n", players[a].pos+1, slots[players[a].pos].type);
			}
			else
			{
				printf("Invalid choice, please try again.\n");
				moveChoice=-1;
			}
		}
	}
}



