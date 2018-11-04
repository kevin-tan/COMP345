#pragma once
#include <vector>
class DiceRollingFacility
{
public:
	DiceRollingFacility();

	// Roll 1-3 dices, update percentages and return sorted Container with dice values
	std::vector<int> rollDice(int numberOfDice);

	// Percentage array
	void displayPercentArr();						// Display percentages for the all possible values(1-6)
	void getPercentRoll(int roll);					// Get percentage of the specific value of dice

	//Getter for total number of dice
	int getTotalDiceRolled();						

private:		
	// Attributes
	int totalDiceRolled;							// Total number of dice rolled
	double percentArr[6];							// Keeps percentages of the rolls from 1-6

	// Helper methods for the Percent Array
	void addToPercentArr(int value);				// Update percentage array
	void initalizePercentArr();	
};

