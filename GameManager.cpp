/*
 * Kevin Shimizu
 * 3.17.2020
 * Final Project CSC275
 * Game Manager cpp file contains all the methods needed to run the game.
 */

//Preprocessor directives
#include "GameManager.h" // GameManager.h contains the method declarations

// Introduction method that explains the rules of the game
bool GameManager::Introduction()
{
	// Game Introduction
	cout << "Welcome to Super Fighter!" << endl;
	// Game Description
	cout << "******************INSTRUCTIONS********************" << endl;
	cout << "Choose from three different classes to play: Viking, Samurai and Crusader." << endl;
	cout << "Each class has strengths and weaknesses." << endl;
	// Character Description
	cout << "Viking Stats: Health = 150, Armor = 100, Stamina = 90, Base Attack = 8" << endl;
	cout << "Samurai Stats: Health = 90, Armor = 80, Stamina = 120, Base Attack = 15" << endl;
	cout << "Crusader Stats: Health = 100, Armor = 150, Stamina = 80, Base Attack = 10" << endl;
	// Fighting Description
	cout << "Choose between three different options during a fight." << endl;
	cout << "Basic attacks do basic damage, blocking does no damage," << endl;
	cout << "but also prevents enemy damage and your special attack does double damage but costs stamina." << endl;
	cout << "If both the player and opponent kill each other, the opponent wins." << endl;
	cout << "You must fight and win 3 rounds to win the game!" << endl;
	cout << "**************************************************" << endl;
	
	system("pause"); // Pause system to wait for user to proceed

	return true; // Return true to progress the game
}

// Character select method allows user to choose from three playable characters
int GameManager::CharacterSelect()
{
	string cmd; // String variable to hold user input
	
	cout << "\nTo being a new game, please select a character. Press 1 for Viking, 2 for Samurai, 3 for Crusader: ";
	
	getline(cin, cmd); // Accept user input
	int i_cmd = stoi(cmd); // Cast the string cmd as an integer

	// Exception Handling
	try 
	{
		if (i_cmd != 1 && i_cmd != 2 && i_cmd != 3) // Check if the cmd is not 1, 2, or 3 and throw an exception if this is true
		{
			throw "Exception: Invalid entry. Please enter 1, 2 or 3.\n";
		}
		else if (i_cmd == 1) // If the user enters 1...
		{
			system("Color 17"); // Change console color to blue and white
			cout << "You have chosen Thor, the Viking!" << endl;
			return 1; // return the players choice
		}
		else if (i_cmd == 2) // If the user enters 2...
		{
			system("Color 17"); // Change console color to blue and white
			cout << "You have chosen Jack, the Samurai!" << endl;
			return 2; // return the players choice
		}
		else if (i_cmd == 3) // If the user enters 3...
		{
			system("Color 17"); // Change console color to blue and white
			cout << "You have chosen Carl, the Crusader!" << endl;
			return 3; // return the players choice
		}
	}
	catch (const char* errorMsg) // Catch the error message
	{
		system("Color 47"); // Change console to red/white
		cout << errorMsg << endl; // Display error
		CharacterSelect(); // Recursive Function
	}
}

// End game method will determine and display winner
bool GameManager::EndGame()
{
	system("Color 60"); // Change console color to yellow and black on win screen
	cout << "Congratulatons, you have defeated all of your foes. You have been crowned as the Ultimate Champion!" << endl;
	cout << "Enter 1 to restart the game or 2 to quit: ";
	string cmd; // String variable to hold the player's command
	getline(cin, cmd); // Accept user input

	if (cmd == "1") // If the user chooses 1...
	{
		// Restart game
		cout << "You have chosen to restart the game!" << endl;
	}
	else if (cmd == "2")  // If the user chooses 2...
	{
		exit(0); // Quit game
	}
	else // Check if entry is invalid
	{
		cout << "Invalid entry please try again."; 
		EndGame(); // Restart method
	}
	return false;
}

// Pseudo random number generator
int GameManager::RandomNumber(int limit)
{
	return rand() % limit; // Return the modulus of the result from rand()
}

// This method is used to initialize a round
void GameManager::Init_Round(int &round, int &character) // References with the round and character are passed to this method
{
	bool isFightActive = true; // Boolean to keep player in a fight while the fight is active
	bool &r_isFightActive = isFightActive;
	float playerDmg = 0; // Integer to hold the player's damage output
	float opponentDmg = 0; // Integer to hold the opponent's damage output
	float* p_PlayDmg = &playerDmg; // Pointer to the playerDmg integer variable
	float* p_OppDmg = &opponentDmg; // Pointer to the opponentDmg integer variable
	srand(static_cast<unsigned int>(time(0))); // This sets the random number seed based on the date and time.
 
	ConsoleColors(round);
	
	// Initialize Player and Opponent
	if (character == 1) // If the player selects 1...
	{
		unique_ptr<Viking> p_Viking = make_unique<Viking>("Thor", 150, 100, 90, true); // Initialize a Viking for the player
		if (round == 1) // If the current round is round 1...
		{
			cout << "\n***Begin round 1***" << endl;
			cout << "Viking vs. Samurai\n\n";
			unique_ptr<Samurai> o_Samurai = make_unique<Samurai>("Jack", 90, 80, 120, false); // Initialize a Samurai as the opponent
			
			while (isFightActive) // While in a fight...
			{
				AttackPhase(p_PlayDmg, p_OppDmg); // Run the AttackPhase method to determine player and opponent attacks
				float opponentDmg = *p_OppDmg * o_Samurai->Attack(); // Calculate opponentDmg
				float playerDmg = *p_PlayDmg * p_Viking->Attack(); // Calculate playerDmg

				p_Viking->SetHealth(p_Viking->GetHealth() - opponentDmg); // Update the player's (viking) health
				o_Samurai->SetHealth(o_Samurai->GetHealth() - playerDmg); // Update the opponent's (samurai) health

				// If the players health is 0 and the opponent's health is greater than 0, or both the player and opponent's health is less than or equal to 0...
				if (p_Viking->GetHealth() <= 0 && o_Samurai->GetHealth() > 0 || p_Viking->GetHealth() <= 0 && o_Samurai->GetHealth() <= 0)
				{
					// Present options after loss
					GameOptions(round, character);
					
				}
				// If the player has greater than 0 health and the opponent has less than or equal to 0 health...
				else if (o_Samurai->GetHealth() <= 0 && p_Viking->GetHealth() > 0)
				{
					// The player wins!
					WinRound(round, character, r_isFightActive);
				}
				// If both player and opponent still have health...
				else
				{
					// Display the current fight stats
					DisplayStats(p_Viking->GetHealth(), o_Samurai->GetHealth(), playerDmg, opponentDmg);
				}
			}
		}
		else if (round == 2) // If the current round is round 2...
		{
			cout << "\n***Begin round 2***" << endl;
			cout << "Viking vs. Crusader\n\n";
			unique_ptr<Crusader> o_Crusader = make_unique<Crusader>("Carl", 100, 150, 80, false); // Initialize a Crusader as the opponent
			
			while (isFightActive) // While in a fight...
			{
				AttackPhase(p_PlayDmg, p_OppDmg); // Run the AttackPhase method to determine player and opponent attacks
				float opponentDmg = *p_OppDmg * o_Crusader->Attack(); // Calculate opponentDmg
				float playerDmg = *p_PlayDmg * p_Viking->Attack(); // Calculate playerDmg
				
				p_Viking->SetHealth(p_Viking->GetHealth() - opponentDmg);	 // Update the player's (viking) health
				o_Crusader->SetHealth(o_Crusader->GetHealth() - playerDmg); // Update the opponent's (crusader) health
				 
				// If the players health is 0 and the opponent's health is greater than 0, or both the player and opponent's health is less than or equal to 0...
				if (p_Viking->GetHealth() <= 0 && o_Crusader->GetHealth() > 0 || p_Viking->GetHealth() <= 0 && o_Crusader->GetHealth() <= 0)
				{
					GameOptions(round, character);
				}
				// If the player has greater than 0 health and the opponent has less than or equal to 0 health...
				else if (o_Crusader->GetHealth() <= 0 && p_Viking->GetHealth() > 0)
				{
					// The player wins!
					WinRound(round, character, r_isFightActive);
				}
				// If both player and opponent still have health...
				else
				{
					// Display the current fight stats
					DisplayStats(p_Viking->GetHealth(), o_Crusader->GetHealth(), playerDmg, opponentDmg);
				}
			}
		}
		else if (round == 3) // If the current round is round 3...
		{
			cout << "\n***Begin round 3***" << endl;
			cout << "For the final round you must fight your brother!\n\n";
			
			unique_ptr<Viking> o_Viking = make_unique<Viking>("Thor", 150, 100, 90, false); // Initialize a Viking as the opponent
			while (isFightActive) // While in a fight...
			{
				AttackPhase(p_PlayDmg, p_OppDmg); // Run the AttackPhase method to determine player and opponent attacks
				float opponentDmg = *p_OppDmg * o_Viking->Attack(); // Calculate opponentDmg
				float playerDmg = *p_PlayDmg * p_Viking->Attack(); // Calculate playerDmg
				
				p_Viking->SetHealth(p_Viking->GetHealth() - opponentDmg); // Update the player's (viking) health
				o_Viking->SetHealth(o_Viking->GetHealth() - playerDmg); // Update the opponent's (viking) health

				// If the players health is 0 and the opponent's health is greater than 0, or both the player and opponent's health is less than or equal to 0...
				if (p_Viking->GetHealth() <= 0 && o_Viking->GetHealth() > 0 || p_Viking->GetHealth() <= 0 && o_Viking->GetHealth() <= 0)
				{
					GameOptions(round, character);
				}
				// If the player has greater than 0 health and the opponent has less than or equal to 0 health...
				else if (o_Viking->GetHealth() <= 0 && p_Viking->GetHealth() > 0)
				{
					// The player wins!
					isFightActive = EndGame(); // Run the end game method
					round = 0; // Integer to hold the current round number
				}
				// If both player and opponent still have health...
				else
				{
					// Display the current fight stats
					DisplayStats(p_Viking->GetHealth(), o_Viking->GetHealth(), playerDmg, opponentDmg);
				}
			}
		}
	}
	else if (character == 2) // If the player selects 2...
	{
		unique_ptr<Samurai> p_Samurai = make_unique<Samurai>("Jack", 90, 80, 120, true); // Initialize a Samurai for the player
		if (round == 1) // If the current round is round 1...
		{
			cout << "\n***Begin round 1***" << endl;
			cout << "Samurai vs. Crusader\n\n";
			
			unique_ptr<Crusader> o_Crusader = make_unique<Crusader>("Carl", 100, 150, 80, false); // Initialize a Crusader as the opponent
			while (isFightActive) // While in a fight...
			{
				AttackPhase(p_PlayDmg, p_OppDmg); // Run the AttackPhase method to determine player and opponent attacks
				float opponentDmg = *p_OppDmg * o_Crusader->Attack(); // Calculate opponentDmg
				float playerDmg = *p_PlayDmg * p_Samurai->Attack(); // Calculate playerDmg
				
				p_Samurai->SetHealth(p_Samurai->GetHealth() - opponentDmg); // Update the player's (samurai) health
				o_Crusader->SetHealth(o_Crusader->GetHealth() - playerDmg); // Update the opponent's (crusader) health

				// If the players health is 0 and the opponent's health is greater than 0, or both the player and opponent's health is less than or equal to 0...
				if (p_Samurai->GetHealth() <= 0 && o_Crusader->GetHealth() > 0 || p_Samurai->GetHealth() <= 0 && o_Crusader->GetHealth() <= 0)
				{
					GameOptions(round, character);
				}
				// If the player has greater than 0 health and the opponent has less than or equal to 0 health...
				else if (o_Crusader->GetHealth() <= 0 && p_Samurai->GetHealth() > 0)
				{
					// The player wins!
					WinRound(round, character, r_isFightActive);
				}
				// If both player and opponent still have health...
				else
				{
					// Display the current fight stats
					DisplayStats(p_Samurai->GetHealth(), o_Crusader->GetHealth(), playerDmg, opponentDmg);
				}
			}
		} 
		else if (round == 2) // If the current round is round 2...
		{
			cout << "\n***Begin round 2***" << endl;
			cout << "Samurai vs. Viking\n\n";
			
			unique_ptr<Viking> o_Viking = make_unique<Viking>("Thor", 150, 100, 90, false); // Initialize a Crusader as the opponent
			while (isFightActive) // While in a fight...
			{
				AttackPhase(p_PlayDmg, p_OppDmg); // Run the AttackPhase method to determine player and opponent attacks
				float opponentDmg = *p_OppDmg * o_Viking->Attack(); // Calculate opponentDmg
				float playerDmg = *p_PlayDmg * p_Samurai->Attack(); // Calculate playerDmg
				
				p_Samurai->SetHealth(p_Samurai->GetHealth() - opponentDmg); // Update the player's (samurai) health
				o_Viking->SetHealth(o_Viking->GetHealth() - playerDmg); // Update the opponent's (viking) health

				// If the players health is 0 and the opponent's health is greater than 0, or both the player and opponent's health is less than or equal to 0...
				if (p_Samurai->GetHealth() <= 0 && o_Viking->GetHealth() > 0 || p_Samurai->GetHealth() <= 0 && o_Viking->GetHealth() <= 0)
				{
					GameOptions(round, character);
				}
				// If the player has greater than 0 health and the opponent has less than or equal to 0 health...
				else if (o_Viking->GetHealth() <= 0 && p_Samurai->GetHealth() > 0)
				{
					// The player wins!
					WinRound(round, character, r_isFightActive);
				}
				// If both player and opponent still have health...
				else
				{
					// Display the current fight stats
					DisplayStats(p_Samurai->GetHealth(), o_Viking->GetHealth(), playerDmg, opponentDmg);
				}
			}
		}
		else if (round == 3) // If the current round is round 3...
		{
			cout << "\n***Begin round 3***" << endl;
			cout << "For the final round you must fight your brother!\n\n";
			
			unique_ptr<Samurai> o_Samurai = make_unique<Samurai>("Jack", 90, 80, 120, false); // Initialize a Samurai as the opponent
			while (isFightActive) // While in a fight...
			{
				AttackPhase(p_PlayDmg, p_OppDmg); // Run the AttackPhase method to determine player and opponent attacks
				float opponentDmg = *p_OppDmg * o_Samurai->Attack(); // Calculate opponentDmg
				float playerDmg = *p_PlayDmg * p_Samurai->Attack(); // Calculate playerDmg
				
				p_Samurai->SetHealth(p_Samurai->GetHealth() - opponentDmg); // Update the player's (samurai) health
				o_Samurai->SetHealth(o_Samurai->GetHealth() - playerDmg); // Update the opponent's (samurai) health

				// If the players health is 0 and the opponent's health is greater than 0, or both the player and opponent's health is less than or equal to 0...
				if (p_Samurai->GetHealth() <= 0 && o_Samurai->GetHealth() > 0 || p_Samurai->GetHealth() <= 0 && o_Samurai->GetHealth() <= 0)
				{
					GameOptions(round, character);
				}
				// If the player has greater than 0 health and the opponent has less than or equal to 0 health...
				else if (o_Samurai->GetHealth() <= 0 && p_Samurai->GetHealth() > 0)
				{
					// Player wins
					isFightActive = EndGame(); // Run the end game method
					round = 0; // Integer to hold the current round number
				}
				// If both player and opponent still have health...
				else
				{
					// Display the current fight stats
					DisplayStats(p_Samurai->GetHealth(), o_Samurai->GetHealth(), playerDmg, opponentDmg);
				}
			}
		}
	}
	else if (character == 3) // If the player selects 3...
	{
		unique_ptr<Crusader> p_Crusader = make_unique<Crusader>("Carl", 100, 150, 80, true); // Initialize a Crusader as the player
		if (round == 1) // If the current round is round 1...
		{
			cout << "\n***Begin round 1***" << endl;
			cout << "Crusader vs. Viking\n\n";
			
			unique_ptr<Viking> o_Viking = make_unique<Viking>("Thor", 150, 100, 90, false); // Initialize a Viking as the opponent
			
			while (isFightActive)  // While in a fight...
			{
				AttackPhase(p_PlayDmg, p_OppDmg); // Run the AttackPhase method to determine player and opponent attacks
				float opponentDmg = *p_OppDmg * o_Viking->Attack(); // Calculate opponentDmg
				float playerDmg = *p_PlayDmg * p_Crusader->Attack(); // Calculate playerDmg
				
				p_Crusader->SetHealth(p_Crusader->GetHealth() - opponentDmg); // Update the player's (crusader) health
				o_Viking->SetHealth(o_Viking->GetHealth() - playerDmg); // Update the opponent's (viking) health

				// If the players health is 0 and the opponent's health is greater than 0, or both the player and opponent's health is less than or equal to 0...
				if (p_Crusader->GetHealth() <= 0 && o_Viking->GetHealth() > 0 || p_Crusader->GetHealth() <= 0 && o_Viking->GetHealth() <= 0)
				{
					GameOptions(round, character);
				}
				// If the player has greater than 0 health and the opponent has less than or equal to 0 health...
				else if (o_Viking->GetHealth() <= 0 && p_Crusader->GetHealth() > 0)
				{
					// The player wins!
					WinRound(round, character, r_isFightActive);
				}
				// If both player and opponent still have health...
				else
				{
					// Display the current fight stats
					DisplayStats(p_Crusader->GetHealth(), o_Viking->GetHealth(), playerDmg, opponentDmg);
				}
			}
		}
		else if (round == 2) // If the current round is round 2...
		{
			cout << "\n***Begin round 2***" << endl;
			cout << "Crusader vs. Samurai\n\n";
			unique_ptr<Samurai> o_Samurai = make_unique<Samurai>("Jack", 90, 80, 120, false); // Initialize a Samurai as the opponent
			while (isFightActive) // While in a fight...
			{
				AttackPhase(p_PlayDmg, p_OppDmg); // Run the AttackPhase method to determine player and opponent attacks
				float opponentDmg = *p_OppDmg * o_Samurai->Attack(); // Calculate opponentDmg
				float playerDmg = *p_PlayDmg * p_Crusader->Attack(); // Calculate playerDmg
				
				p_Crusader->SetHealth(p_Crusader->GetHealth() - opponentDmg); // Update the player's (crusader) health
				o_Samurai->SetHealth(o_Samurai->GetHealth() - playerDmg); // Update the opponent's (samurai) health

				// If the players health is 0 and the opponent's health is greater than 0, or both the player and opponent's health is less than or equal to 0...
				if (p_Crusader->GetHealth() <= 0 && o_Samurai->GetHealth() > 0 || p_Crusader->GetHealth() <= 0 && o_Samurai->GetHealth() <= 0)
				{
					GameOptions(round, character);
				}
				// If the player has greater than 0 health and the opponent has less than or equal to 0 health...
				else if (o_Samurai->GetHealth() <= 0 && p_Crusader->GetHealth() > 0)
				{
					// The player wins!
					WinRound(round, character, r_isFightActive);
				}
				// If both player and opponent still have health...
				else
				{
					// Display the current fight stats
					DisplayStats(p_Crusader->GetHealth(), o_Samurai->GetHealth(), playerDmg, opponentDmg);
				}
			}
		}
		else if (round == 3) // If the current round is round 3...
		{
			cout << "\n***Begin round 3***" << endl;
			cout << "For the final round you must fight your brother!\n\n";
			unique_ptr<Crusader> o_Crusader = make_unique<Crusader>("Carl", 100, 150, 80, false); // Initialize a Crusader as the opponent
			while (isFightActive) // While in a fight...
			{ 
				AttackPhase(p_PlayDmg, p_OppDmg); // Run the AttackPhase method to determine player and opponent attacks
				float opponentDmg = *p_OppDmg * o_Crusader->Attack(); // Calculate opponentDmg
				float playerDmg = *p_PlayDmg * p_Crusader->Attack(); // Calculate playerDmg
				
				p_Crusader->SetHealth(p_Crusader->GetHealth() - opponentDmg); // Update the player's (crusader) health
				o_Crusader->SetHealth(o_Crusader->GetHealth() - playerDmg); // Update the opponent's (crusader) health
				// 
				// If the players health is 0 and the opponent's health is greater than 0, or both the player and opponent's health is less than or equal to 0...
				if (p_Crusader->GetHealth() <= 0 && o_Crusader->GetHealth() > 0 || p_Crusader->GetHealth() <= 0 && o_Crusader->GetHealth() <= 0)
				{
					GameOptions(round, character);
				}
				// If the player has greater than 0 health and the opponent has less than or equal to 0 health...
				else if (o_Crusader->GetHealth() <= 0 && p_Crusader->GetHealth() > 0)
				{
					// Opponent loses
					isFightActive = EndGame(); // Run the end game method
					round = 0; // Integer to hold the current round number
				}
				// If both player and opponent still have health...
				else
				{
					// Display the current fight stats
					DisplayStats(p_Crusader->GetHealth(), o_Crusader->GetHealth(), playerDmg, opponentDmg);
				}
			}
		}
	}
}
// Method to determine the player's attack
int GameManager::PlayerAttack()
{
	// Choose attack, defend or special
	string cmd; // String to hold the user's command input
	cout << "Press 1 for basic attack, 2 for block or 3 for special attack: ";
	getline(cin, cmd); // Accept user input

	if (cmd == "1")
	{
		// Basic attack
		cout << "Player uses a basic attack!" << endl;
		return 1;
	}
	else if (cmd == "2")
	{
		// Block attack
		cout << "Player blocks!" << endl;
		return 2;
	}
	else if (cmd == "3")
	{
		// Special Attack
		cout << "Player uses a special attack!" << endl;
		return 3;
	}
	else
	{
		// Invalid Entry.
		cout << "Error: Invalid Entry." << endl;
		PlayerAttack();
	}
}
// Method used to determine the opponent's attack based on RNG
int GameManager::OpponentAttack()
{
	// Generate a random number between 1-100
	int rand = RandomNumber(100);

	// If the number is between 1 and 33...
	if (rand <= 33)
	{
		cout << "Opponent uses a basic attack!" << endl; // Basic attack, return 1
		return 1;
	}
	// If the number is between 33 and 66...
	else if (rand <= 66)
	{
		cout << "Opponent blocks!" << endl; // block, return 2
		return 2;
	}
	// If the number is between 66 and 100...
	else
	{
		cout << "Opponent uses a special attack!" << endl; // Special attack, return 3
		return 3;
	}
}
// Method used to determine the player's attack modifier based on combination of player and opponent attacks
// This modifier will be multiplied by a class's attack damage to determine actual damage
float GameManager::CalculatePlayerAttack(int pAttack, int oAttack)
{
	if (pAttack == 1) // Player basic attack
	{
		if (oAttack == 1) // Opponent basic attack
		{
			// Player and Opponent Basic Attacks
			return 1.0f; // return a modifier of 1
		}
		else if (oAttack == 2) // Opponent blocks
		{
			// Player Basic, opponent block
			return 0.0f; // Return 0 since block negates all player damage
		}
		else if (oAttack == 3) // Opponent special
		{
			// Player basic, opponent special
			return 0.5f; // Return 0.5 which halves the basic attack damage
		}
	}
	else if (pAttack == 2) // Player blocks
	{
		if (oAttack == 1) // Opponent basic attack
		{
			// Player block, opponent basic
			return 0.0f; // Blocks all incoming damage
		}
		else if (oAttack == 2) // Opponent blocks
		{
			// Player block, opponent block
			return 0.0f; // Blocks all incoming damage
		}
		else if (oAttack == 3) // Opponent special attack
		{
			// Player block, opponent Special
			return 0.0f; // Blocks all incoming damage
		}
	}
	else if (pAttack == 3) // Player special attack
	{
		if (oAttack == 1) // Opponent basic attack
		{
			// Player special, opponent basic
			return 2.0f; // Special attack modifier is 2x the normal attack damage if the opponent uses basic attack
		}
		else if (oAttack == 2) // Opponent blocks
		{
			// Player special, opponent block
			return 0.0f; // Opponent negates all damage done by special
		}
		else if (oAttack == 3) // Opponent uses special attack
		{
			// Player special, opponent special
			return 1.5f; // Both player and opponent use special which means damage is 1.5x base attack for both player and opponent
		}
	}
}

// Method used to determine the opponent's attack modifier based on combination of player and opponent attacks
float GameManager::CalculateOpponentAttack(int pAttack, int oAttack)
{
	if (oAttack == 1) // Opponent basic attack
	{ 
		if (pAttack == 1) // Player basic attack 
		{
			// Opponent basic, player basic
			return 1.0f; // return a modifier of 1
		}
		else if (pAttack == 2) // Player blocks
		{
			// Opponent basic, player block
			return 0.0f; // Return 0 since block negates all player damage
		}
		else if (pAttack == 3) // Player special attack
		{
			// Opponent basic, player special
			return 0.5f; // Return 0.5 which halves the basic attack damage
		}
	}
	else if (oAttack == 2) // Opponent blocks
	{
		if (pAttack == 1) // Player basic attack
		{
			// Opponent block, player basic
			return 0.0f; // Blocks all incoming damage
		}
		else if (pAttack == 2) // Player blocks
		{
			// Opponent block, player block
			return 0.0f; // Blocks all incoming damage
		}
		else if (pAttack == 3) // Player uses special attack
		{
			// Opponent block, player special
			return 0.0f; // Blocks all incoming damage
		}
	}
	else if (oAttack == 3) // Opponent uses special
	{
		if (pAttack == 1) // Player basic attack
		{
			// Opponent special, player basic
			return 2.0f;// Special attack modifier is 2x the normal attack damage if the player uses basic attack
		}
		else if (pAttack == 2) // Player blocks 
		{
			// Opponent special, player block
			return 0.0f; // Blocks all incoming damage
		}
		else if (pAttack == 3) // Player uses special
		{
			// Opponent special, player special
			return 1.5f; // Both player and opponent use special which means damage is 1.5x base attack for both player and opponent
		}
	}
}

// The attack phase method determines which attack the player and opponent uses and calculates the damage output for both
void GameManager::AttackPhase(float *p_Damage, float *o_Damage)
{
	// Determine player attack
	int p_Attack = PlayerAttack();
	// Determine opponent attack
	int o_Attack = OpponentAttack();
	
	// Calculate Damage Modifier
	*p_Damage = CalculatePlayerAttack(p_Attack, o_Attack); // Use p_Damage pointer to update the damage amount
	*o_Damage = CalculateOpponentAttack(p_Attack, o_Attack); // Use o_Damage pointer to update the damage amount
}

// Method that displays the damage and current health for both the player and opponent
void GameManager::DisplayStats(int playerHealth, int opponentHealth, int playerAttack, int opponentAttack) // Pass in player/opponent health and player/opponent attack
{
	cout << "Your opponent has dealt " << opponentAttack << " damage. You have " << playerHealth << " remaining." << endl;

	cout << "You have dealt " << playerAttack << " damage. Your opponent has " << opponentHealth << " remaining.\n\n";
}

// This method displays the options for the user after they lose a round 
void GameManager::GameOptions(int &round, int &character) // Pass in the round, character selected and the player's score
{
	cout << "Sorry, you lose the round!" << endl;
	cout << "Press 1 to restart the round, press 2 to restart the game, press 3 to quit: ";
	string cmd; // String variable to hold the player's command
	getline(cin, cmd); // Accept user input

	if (cmd == "1") // If the user chooses 1...
	{
		// Restart round
		Init_Round(round, character);
	}
	else if (cmd == "2")  // If the user chooses 2...
	{
		round = 1; // Reset round to 1
		Init_Round(round, character);
	}
	else if (cmd == "3")  // If the user chooses 3...
	{
		exit(0); // Quit game
	}
}

void GameManager::WinRound(int &round, int &character, bool &isFightActive)
{
	// The player wins!
	cout << "\n****Congratulations, you have won the round!****" << endl;
	isFightActive = false; // Set isFightActive to false to end the current round
	round++; // Increment round count
	Init_Round(round, character); // Recursive function, it will advance to next round on this play through
}

// Change the console colors depending on the current round
void GameManager::ConsoleColors(int round)
{
	if (round == 1)
	{
		system("Color 17"); // Change console color to blue and white during round 1
	}
	else if (round == 2)
	{
		system("Color 57"); // Change console color to purple and white during round 2
	}
	else if (round == 3)
	{
		system("Color 47"); // Change console color to red and white during round 3
	}
}

