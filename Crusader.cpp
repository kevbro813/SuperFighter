/*
 * Kevin Shimizu
 * 3.17.2020
 * Final Project CSC275
 * Crusader cpp file contains all the Crusader class definitions.
 */

 // Preprocessor directive
#include "Crusader.h" // Crusader header needed for declarations

 // Crusader class constructor
Crusader::Crusader(string name, int health, int armor, int stamina, bool isPlayer)
{
	SetName(name); // Set name
	SetHealth(health); // Set health
	SetArmor(armor); // Set Armor
	SetStamina(stamina); // Set Stamina
	SetIsPlayer(isPlayer); // Indicate if player or opponent
}

// Returns the basic attack damage for the Crusader
int Crusader::Attack()
{
	return 10;
}

