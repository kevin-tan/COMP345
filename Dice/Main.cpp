#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <time.h>
#include "Dice.h"
#include "DiceRollingFacility.h"

using namespace std;

void out(vector<int> MyV);
int main() {
	srand(time(0));	// Unique pattern for the rand() function. MUST BE first statement in main function!
	vector<int> test;

	DiceRollingFacility obj;
	
	for (int i = 0; i < 3; ++i) {
		cout << "Roll" << endl;
		test = obj.rollDice();
		cout << "Sotred container is ";
		out(test);

		cout << " \nPercentage array is: " << endl;
		obj.displayPercentArr();
		cout << endl;
		}
	obj.getPercentRoll(6);
	
	// Test for the equal share of rolls
		for (int i = 0; i < 1000; ++i) {
			obj.rollDice();
		}
		obj.displayPercentArr();
	

	return 0;
}

	// Helper method to display container
	void out(vector<int> MyV){
		for (unsigned int i = 0; i < MyV.size(); ++i) {
			cout << MyV.at(i) << " ";
		}

}
