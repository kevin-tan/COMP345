#pragma once
#include <vector>
class DiceRollingFacility
{
public:
	DiceRollingFacility();

	// Roll 1-3 dices, store values in container/update percentage
	void rollDice();

	// Sorted Container
	void addToContainer(int value);
	void displayContainer();
	void clearContainer();
	void sortContainer();

	void getTotalDiceRolled();
	// Percentage array
	void initPercentArr();
	void displayPercentArr();
	void getPercentOfValues();
	void addToPercentArr(int value);

private:
	int totalDiceRolled;
	std::vector<int> sortedContainer;
	int percentArr[6];
};

