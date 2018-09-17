#pragma once
class Dice
{
public:
	Dice();

	int getDiceValue();
	void setDiceValue(int value);

private:
	int diceValue;
};

