/*
 * Kevin Shimizu
 * 3.17.2020
 * Final Project CSC275
 * Samurai cpp file contains all the Samurai class definitions.
 */

 // Preprocessor directive
#include "Samurai.h" // Samurai header needed for declarations

// Samurai class constructor
Samurai::Samurai(string name, int health, int armor, int stamina, bool isPlayer)
{
	SetName(name); // Set name
	SetHealth(health); // Set health
	SetArmor(armor); // Set Armor
	SetStamina(stamina); // Set Stamina
	SetIsPlayer(isPlayer); // Indicate if player or opponent
}

// Returns the basic attack damage for the Samurai
int Samurai::Attack()
{
	return 15;
}

