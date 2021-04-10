/*
 * Kevin Shimizu
 * 3.17.2020
 * Final Project CSC275
 *
 * Character header file contains Character base class declarations
 */

//Preprocessor directives
#pragma once
#include <string> // Included to use string type

using namespace std; // Using the standard namespace
class Character
{
public: // Public methods
	void SetName(string n); // Setter method for name property
	void SetHealth(int h); // Setter method for health property
	void SetArmor(int a); // Setter method for armor property
	void SetStamina(int s); // Setter method for stamina property
	string GetName(); // Getter method for name property
	int GetHealth(); // Getter method for health property
	int GetArmor(); // Getter method for armor property
	int GetStamina(); // Getter method for stamina property
	virtual int Attack() = 0; // Pure virtual Attack method
	void SetIsPlayer(bool ip); // Set bool variable to indicate if the instance is the player or opponent
	bool GetIsPlayer(); // Get bool variable to indicate if the instance is the player or opponent
private: // Private properties
	string name; // Character name property
	int health; // Character health property
	int armor; // Character armor property
	int stamina; // Character stamina property
	bool isPlayer; // Character isPlayer bool property
};

