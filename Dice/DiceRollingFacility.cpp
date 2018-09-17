#include <iostream>
#include <vector>
#include <algorithm>
#include "DiceRollingFacility.h"
#include "Dice.h"

using namespace std;


DiceRollingFacility::DiceRollingFacility(){
	totalDiceRolled = 0;
	std::vector<int> sortedContainer;
	int percentArr[6]; 
	initPercentArr();
}

/*  Main function of the Dice Rolling Facility object.
	It enables player to decide how many dice are being rolled (from 1 to 3).
	Retuns values of the dice to the sorted container and updates percentages of all individual rolles.
*/
void DiceRollingFacility::rollDice() {
	int numberOfDice;

	cout << "How many dice you would like to roll (from 1 to 3 dice)? ";

	// Number of dice user wants to roll
	do {
		cin >> numberOfDice;
		if (numberOfDice < 1 || numberOfDice > 3)
			cout << "Number of dice must be betwen 1 and 3 ";
	} while (numberOfDice < 1 || numberOfDice > 3);

	// Update total number of dice rolled
	totalDiceRolled += numberOfDice;

	// Get values of dice and store in the Sorted Container/Update percentage array
	for (int i = 0; i < numberOfDice; i++) {
		Dice obj;
		addToContainer(obj.getDiceValue());
		addToPercentArr(obj.getDiceValue());
	}
	sortContainer();
}

// Percentage array
void DiceRollingFacility::initPercentArr() {
	for (int i = 0; i < 6; ++i)
		percentArr[i] = 0;
}
void DiceRollingFacility::getPercentOfValues() {
	for (int i = 0; i < 6; ++i) {
		cout << i + 1 << " was rolled " << (double) percentArr[i] / totalDiceRolled * 100 << " % of the time." << endl;
	}
}
void DiceRollingFacility::displayPercentArr() {
	for (int i = 0; i < 6; ++i) {
		cout << percentArr[i] << endl;
	}
}
void DiceRollingFacility::addToPercentArr(int value) {
	percentArr[value - 1]++;
}

// Sorted Container
void DiceRollingFacility::addToContainer(int value) {
	sortedContainer.insert(sortedContainer.begin(), value);
}
void DiceRollingFacility::displayContainer() {
	for (const int &number : sortedContainer) {
		cout << number << endl;
	}
}
void DiceRollingFacility::clearContainer() {
	sortedContainer.clear();
}
void DiceRollingFacility::sortContainer() {
	std::sort(sortedContainer.begin(), sortedContainer.end());
}

// Total number of rolled dice
void DiceRollingFacility::getTotalDiceRolled() { cout << "Total number of dice rolled is: " << totalDiceRolled << endl; }
