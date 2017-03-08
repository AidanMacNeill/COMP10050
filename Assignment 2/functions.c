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
		slots[j].occupied=true; // Marks the slot as being occupied once a player is in it
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
		strcpy(players[i].type, playerType[c-1]);

	}
}





