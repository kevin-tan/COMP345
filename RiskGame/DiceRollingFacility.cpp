#include <iostream>
#include <vector>
#include <algorithm>
#include "DiceRollingFacility.h"

using namespace std;


DiceRollingFacility::DiceRollingFacility(){
	totalDiceRolled = 0;
	double percentArr[6]; 
	initalizePercentArr();
}

/*  Main method of the Dice Rolling Facility object.
	It enables player to decide how many dice are being rolled (from 1 to 3).
	Returns sorted container with dice values and updates percentages.
*/
vector<int> DiceRollingFacility::rollDice(int numberOfDice) {
	int roll;
	vector <int> sortContainer;

	// Get values of dice and store in the Sorted Container/Update percentage array
	for (int i = 0; i < numberOfDice; i++) {
		// Update total number of dice rolled
		totalDiceRolled++;

		// Roll individual dice
		roll = rand() % 6 + 1;

		// Stor result of the roll in container and update percentages
		sortContainer.push_back(roll);
		addToPercentArr(roll);
	}
	// Sort container and return it
	std::sort(sortContainer.begin(), sortContainer.end());
	return sortContainer;
}

// Display percentage array
void DiceRollingFacility::displayPercentArr() {
	for (int i = 0; i < 6; ++i) {
		cout << i + 1 << " was rolled " << percentArr[i] << " % of the time." << endl;
	}
}

// Get percentage of the specific value of dice
void DiceRollingFacility::getPercentRoll(int roll) {
	if (roll > 6 || roll < 1) {
		cout << "Dice roll must be between 1 and 6" << endl;
		exit(1);
	}
	cout << roll << " was rolled " << percentArr[roll-1] << " % of the time." << endl;
}

// Initialize percentage array
void DiceRollingFacility::initalizePercentArr() {
	for (int i = 0; i < 6; ++i)
		percentArr[i] = 0.0;
}

// Update percentage array
void DiceRollingFacility::addToPercentArr(int value) {
	// Get from % to Double
	if (getTotalDiceRolled() > 1) {
		for (int i = 0; i < 6; ++i) {
			percentArr[i] = percentArr[i] / 100 * (getTotalDiceRolled() - 1);
		}
	}
	// Update roll and convert back to %
	percentArr[value - 1]++;
	for (int i = 0; i < 6; ++i) {
		percentArr[i] = percentArr[i] / getTotalDiceRolled() * 100;
	}
}
// Get total number of dice rolled
int DiceRollingFacility::getTotalDiceRolled() { return totalDiceRolled; }
