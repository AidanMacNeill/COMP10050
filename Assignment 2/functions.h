/*
 * functions.h
 *
 *  Created on: 4 Mar 2017
 *      Author: aidan
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_
#define MAX_SIZE 50
#include <stdbool.h>

struct player
{
	char name[MAX_SIZE];
	char type[MAX_SIZE];
	int health;
	int magic;
	int smartness;
	int strength;
	int dexterity;
	int luck;
	int pos;
};

struct slot
{
	int id;
	char type[MAX_SIZE];
	_Bool occupied;
};

void assignSlots(int numSlots, char* slotsType[], struct slot slots[]); // Assign slot types to each slot

void playerPosition(int numPlayers, int numSlots, struct player players[], struct slot slots[]); // Assign players to unique positions

void playerInit(int numPlayers, struct player players[], char* playerType[]); // Setup for player names and types

void playerStats(struct player player[], char* playerType[], int numPlayers); // Initialise player stats

void playerMove(struct player players[], struct slot slots[], int numSlots, int *c, int a); // Move players

void playerMoveStats(struct player players[], struct slot slots[], char* slotsType[], int a); // Change stats depending on slot types

void playerStatsBoundary(int *x); // Stops stats from going over threshold

void playerAttack(struct player players[], struct slot slots[], int *c, int a, int numPlayers, int numSlots); // Player Attack function

void playerHealth(int *x); // Resets player health to 0 if drops below
#endif /* FUNCTIONS_H_ */
