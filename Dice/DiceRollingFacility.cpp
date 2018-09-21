#include <iostream>
#include <vector>
#include <algorithm>
#include "DiceRollingFacility.h"
#include "Dice.h"

using namespace std;


DiceRollingFacility::DiceRollingFacility(){
	totalDiceRolled = 0;
	double percentArr[6]; 
	initalizePercentArr();
}

/*  Main method of the Dice Rolling Facility object.
	It enables player to decide how many dice are being rolled (from 1 to 3).
	Retuns sorted container(vector) with dice values and updates percentages.
*/
vector<int> DiceRollingFacility::rollDice() {
	int numberOfDice = 3;	
	vector <int> sortContainer;

	// Number of dice user wants to roll
	cout << "How many dice you would like to roll (from 1 to 3 dice)? ";
	do {
		cin >> numberOfDice;
	//	if (numberOfDice < 1 || numberOfDice > 3)
			cout << "Number of dice must be betwen 1 and 3 ";
	} while (numberOfDice < 1 || numberOfDice > 3);

	// Get values of dice and store in the Sorted Container/Update percentage array
	for (int i = 0; i < numberOfDice; i++) {
		// Update total number of dice rolled
		totalDiceRolled++;

		// Create dice object and roll it
		Dice obj;
		// Stor result of the roll in container and update percentages
		sortContainer.push_back(obj.getDiceValue());
		addToPercentArr(obj.getDiceValue());
	}
	// Sort container
	std::sort(sortContainer.begin(), sortContainer.end());
	return sortContainer;
}

// Percentage array
void DiceRollingFacility::displayPercentArr() {
	for (int i = 0; i < 6; ++i) {
		cout << i + 1 << " was rolled " << percentArr[i] << " % of the time." << endl;
	}
}
void DiceRollingFacility::getPercentRoll(int roll) {
	if (roll > 6 || roll < 1) {
		cout << "Dice roll must be between 1 and 6" << endl;
		exit(1);
	}
	cout << roll << " was rolled " << percentArr[roll-1] << " % of the time." << endl;
}
void DiceRollingFacility::initalizePercentArr() {
	for (int i = 0; i < 6; ++i)
		percentArr[i] = 0.0;
}
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
// Total number of rolled dice
int DiceRollingFacility::getTotalDiceRolled() { return totalDiceRolled; }
