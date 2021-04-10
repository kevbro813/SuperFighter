/*
 * Kevin Shimizu
 * 3.17.2020
 * Final Project CSC275
 * Samurai cpp file contains all the Samurai class definitions.
 */

// Preprocessor directives
#pragma once
#include "Character.h" // Requires the Character header file for inheritance
#include <iostream>

// Samurai class inherits from Character base class
class Samurai : public Character
{
public: // Public methods
	Samurai(string name, int health, int armor, int stamina, bool isPlayer); // Constructor
	int Attack() override; // Attack method overrides a pure virtual method contained in Character class
private: // No private properties for this class
};

