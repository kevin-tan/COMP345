#include <iostream>
#include <cstdlib>
#include <time.h>
#include "Dice.h"


using namespace std;



Dice::Dice(){
	int x = rand() % 6 + 1;
	setDiceValue(x);
}

// Getters and Setters
int Dice::getDiceValue() { return diceValue; }
void Dice::setDiceValue(int value) { diceValue = value; }
