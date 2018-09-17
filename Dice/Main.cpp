#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <time.h>
#include "Dice.h"
#include "DiceRollingFacility.h"

using namespace std;

int main() {
	srand(time(0));

	DiceRollingFacility obj;

	obj.rollDice();
	obj.displayContainer();

	obj.rollDice();
	obj.displayContainer();

	obj.getTotalDiceRolled();
	obj.getPercentOfValues();







	return 0;
}