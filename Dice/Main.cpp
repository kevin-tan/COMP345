#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <time.h>
#include "DiceRollingFacility.h"

using namespace std;

void printContainer(vector<int> &MyV);
int main() {
	srand(time(0));	// Unique pattern for the rand() function. MUST BE first statement in main function!
	
	// Two Dice Rolling objects with respective containers
	DiceRollingFacility obj1, obj2;
	vector <int> container1, container2;
	char repeat;
	do {
		// Test object 1
		cout << "\nTest for the first object" << endl;
		container1 = obj1.rollDice();
		cout << "Container values: ";
		printContainer(container1);
		cout << "Percentage of rolls " << endl;
		obj1.displayPercentArr();

		// Test object 2
		cout << "\nTest for the second object" << endl;
		container2 = obj2.rollDice();
		cout << "Container values: ";
		printContainer(container2);
		cout << "Percentage of rolls: " << endl;
		obj2.displayPercentArr();

		// Run test again
		cout << "\nRepeat test? (y/n): ";
		cin >> repeat;
	} while (repeat != 'n');

	/* Test for the equal share of rolls
	for(int i = 0; i < 500; ++i){
		obj1.rollDice();
	}
	obj1.displayPercentArr();
	*/
	return 0;
}

	// Helper method to display container
	void printContainer(vector<int> &MyV){
		for (unsigned int i = 0; i < MyV.size(); ++i) {
			cout << MyV.at(i) << " ";
		}
		cout << endl;
}
