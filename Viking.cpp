/*
 * Kevin Shimizu
 * 3.17.2020
 * Final Project CSC275
 * Viking cpp file contains all the Viking class definitions.
 */

// Preprocessor directive
#include "Viking.h" // Viking header needed for declarations

// Viking class constructor
Viking::Viking(string name, int health, int armor, int stamina, bool isPlayer)
{
	SetName(name); // Set name
	SetHealth(health); // Set health
	SetArmor(armor); // Set Armor
	SetStamina(stamina); // Set Stamina
	SetIsPlayer(isPlayer); // Indicate if player or opponent
}

// Returns the basic attack damage for the Viking
int Viking::Attack()
{
	return 8;
}

