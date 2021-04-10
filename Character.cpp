/*
 * Kevin Shimizu
 * 3.17.2020
 * Final Project CSC275
 *
 * Character cpp file contains Character base class definitions
 */

// Preprocessor directives
#include "Character.h" // Include the Character header for the class declarations

// Setter method for name property
void Character::SetName(string n)
{
	name = n;
}

// Setter method for health property
void Character::SetHealth(int h)
{
	health = h;
}

// Setter method for armor property
void Character::SetArmor(int a)
{
	armor = a;
}

// Setter method for stamina property
void Character::SetStamina(int s)
{
	stamina = s;
}

// Getter method for name property
string Character::GetName()
{
	return name;
}

// Getter method for health property
int Character::GetHealth()
{
	return health;
}

// Getter method for armor property
int Character::GetArmor()
{
	return armor;
}

// Getter method for stamina property
int Character::GetStamina()
{
	return stamina;
}

// Setter method for isPlayer property
void Character::SetIsPlayer(bool ip)
{
	isPlayer = ip;
}

// Getter method for isPlayer property
bool Character::GetIsPlayer()
{
	return isPlayer;
}
