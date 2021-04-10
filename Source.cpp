/*
 * Kevin Shimizu
 * 3.17.2020
 * Final Project CSC275
 *
 * Source cpp file contains the main game loop for the final project
 */

// Prepreocessor directives
#include <iostream> // iostream needed for console input/output
#include <string> // String required to use string types
#include "GameManager.h" // GameManager header file contains all the GameManager class method declarations
#include "Crusader.h" // Header for the Crusader class
#include "Samurai.h" // Header for the Samurai class
#include "Viking.h" // Header for the Viking class
#include <thread> // Thread used to split each round into separate threads

using namespace std; // Using the standard namespace

int main()
{
	bool activeGame = false; // Bool used for game loop
	unique_ptr<GameManager> gm = make_unique<GameManager>(); // Initialize a unique pointer for the GameManager class

	// Introduction
	activeGame = gm->Introduction();

	while (activeGame) // Main game loop
	{
		int round = 0; // Integer to hold the current round number
		int character; // Integer to hold the character selected by the player. 1 for Viking, 2 for Samurai, 3 for Crusader
		int &r_character = character; // Reference to the character int
		int &r_round = round; // Reference to the round int
		
		// Character Select
		character = gm->CharacterSelect();

		round++; // Increment to round #1

		// Fight round 1
		thread round1(&GameManager::Init_Round, GameManager(), ref(r_round), ref(r_character)); // Create a thread for round 1, passing in references to round and character integers
		round1.join(); // Join round1 thread to main thread

		// Fight round 2
		thread round2(&GameManager::Init_Round, GameManager(), ref(r_round), ref(r_character)); // Create a thread for round 2, passing in references to round and character integers
		round2.join(); // Join round2 thread to main thread

		// Fight round 3
		thread round3(&GameManager::Init_Round, GameManager(), ref(r_round), ref(r_character)); // Create a thread for round 3, passing in references to round and character integers
		round3.join(); // Join round3 thread to main thread
	}
}