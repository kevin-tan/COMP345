#pragma once
#include <vector>
class DiceRollingFacility
{
public:
	DiceRollingFacility();

	// Roll 1-3 dices, update percentages and return sorted Container with dice values
	std::vector<int> rollDice();

	// Percentage array
	void displayPercentArr();
	void getPercentRoll(int roll);

	//Getter for total number of dice
	int getTotalDiceRolled();

private:
	// Attributes
	int totalDiceRolled;
	double percentArr[6];

	// Helper methods for the Percent Array
	void addToPercentArr(int value);
	void initalizePercentArr();
};

