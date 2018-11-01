#pragma once

#include <iostream>
#include <vector>

class Hand;
using std::vector;

class Deck {
public:
	Deck(int number_of_countries);
	void draw(Hand* hand);

	int get_number_of_exchanges() const { return number_of_exchanges; }
	vector<int> get_deck_cards() const { return deck_cards; }
	int get_deck_size() const { return deck_size; }
	int get_number_of_infantry() const { return deck_cards[0]; }
	int get_number_of_artillery() const { return deck_cards[1]; }
	int get_number_of_cavalry() const { return deck_cards[2]; }

	int inc_number_of_exchanges() { return ++number_of_exchanges; }

private:
	//0:Infantry; 1:Artillery; 2:Cavalry
	vector<int> deck_cards;
	int number_of_exchanges;
	int deck_size;
};