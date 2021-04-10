/*
 * Kevin Shimizu
 * 3.17.2020
 * Final Project CSC275
 * Game Manager header file contains all the method declarations needed to run the game.
 */

#pragma once

// Preprocessor directives
#include <string>
#include <iostream> // iostream for input/output to console

// Need headers for all the playable classes
#include "Viking.h"
#include "Samurai.h"
#include "Crusader.h"

#include <ctime> // Used to create a random seed based on time
#include <cstdlib> // Needed for rand()

using namespace std; // Using the standard namespace

class GameManager
{
public: // Public method declarations
	bool Introduction(); // Introduction for game
	int CharacterSelect(); // Character selection method. Returns an integer that corresponds to a class
	bool EndGame(); // End game method
	int RandomNumber(int limit); // RNG method to have opponents choose a random attack
	void Init_Round(int &round, int &character); // This method runs one round of fighting
	int PlayerAttack(); // Determine which attack the player chooses
	int OpponentAttack(); // Determine the opponent's attack
	float CalculatePlayerAttack(int pAttack, int oAttack); // Calculate the damage done by the player
	float CalculateOpponentAttack(int pAttack, int oAttack); // calculate the damage done by the opponent
	void AttackPhase(float *p_PlayerDamage, float *p_OpponentDamage); // Attack phase method manages each wave of attacks by the player and opponent
	void DisplayStats(int playerHealth, int opponentHealth, int playerAttack, int opponentAttack); // Displays the damage done by player and opponent and their respective health
	void GameOptions(int& round, int& character); // Options displayed when the player loses a round
	void WinRound(int &round, int &character, bool &isFightActive); // Method run when the player wins a round
	void ConsoleColors(int round);
private: // No unique private properties for this class
};


