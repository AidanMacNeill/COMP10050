/*
 * main.c
 *
 *  Created on: 4 Mar 2017
 *      Author: aidan
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include "functions.h" //

int main(void)
{
	setbuf(stdout, NULL); // Allows scanf statements to work with Eclipse
	srand(time(NULL));

	printf("Welcome to CrossFire, the multiplayer board game! Have Fun!\n");
	int numPlayers=-1, numSlots, a, c=-1; // Number of players and slots for the game, a counter and a choice
	printf("How many players will be playing the game? Max: 6\n");
	while(numPlayers<0)
	{
		scanf("%d", &numPlayers);
		if(numPlayers<2 || numPlayers>6)
		{
			printf ("This is an invalid number, please try again.\n");
			numPlayers=-1;
		}
	}

	printf("How many game slots would you like to use? Min: %d, Max: 20\n", numPlayers);
	scanf("%d", &numSlots);
	if(numPlayers > numSlots)
	{
		numSlots=numPlayers;
		printf("The number of slots was set to the minimum to allow all players to play\n"); // Prevents there being too few slots for number of players chosen
	}
	if (numSlots > 20)
	{
		numSlots=20;
		printf("The number of slots was sent to the maximum allowed value of 20");
	}
	printf("\n");

	struct player players[numPlayers]; // Declare structure for each of the players in the game
	struct slot slots[numSlots]; // Declare structure for the slots in the game
	char* playerType[4]={"Elf", "Human", "Ogre", "Wizard"}; // Declare pointer arrays for each of the player types and slot types to be assigned later
	char* slotsType[3]={"Level Ground", "Hill", "City"};

	assignSlots(numSlots, slotsType, slots); // Assigns slot type randomly to each slot

	playerPosition(numPlayers, numSlots, players, slots); // Assigns players randomly to unique positions

	playerInit(numPlayers, players, playerType); // Sets up each player type


	printf("All Players\n");
	for(a=0; a<numPlayers; a++)
	{
		printf("\nPlayer %d\nName: %s\nClass: %s\n", a+1, players[a].name, players[a].type); // Refer to values in each variable in the struct
		printf("---Stats---\nHealth: %d\nMagic: %d\nSmartness: %d\nStrength: %d\nDexterity: %d\nLuck: %d\n", players[a].health, players[a].magic, players[a].smartness, players[a].strength, players[a].dexterity, players[a].luck);
		printf("---Slots---\nStarting Position: %d\n", players[a].pos+1);
	}

	printf("\n---Let the game begin!---\n");
	for(a=0; a<numPlayers; a++)
	{
		printf("\n%s, would you like to:\n[1]Move\n[2]Attack\n", players[a].name);

		while(c<0)
		{
			scanf("%d", &c);
			if(c==1)
			{
				playerMove(players, slots, numSlots, &c, a);
			}
			if(c==2)
			{
				playerAttack(players, slots, &c, a, numPlayers);
				if(c==6424) // If the player can't attack in the playerAttack function, let them choose again
				{
					a--;
				}
			}
			else
			{
				printf("Invalid choice, please try again.\n");
			}
		}
		c=-1;
	}
	printf("\nThe game has finished!\n---Final Stats---\n\n");
	for(a=0; a<numPlayers; a++)
	{
		printf("%s (%s, %d)\n", players[a].name, players[a].type, players[a].health);
	}
}
