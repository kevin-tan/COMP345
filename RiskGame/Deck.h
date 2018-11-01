/*
 * Deck.h
 *
 */

#pragma once

#include <iostream>
#include <vector>

class Hand;
using std::vector;

class Deck {
public:
	Deck();
	Deck(int number_of_countries);
	void draw(Hand* hand);

	int get_number_of_exchanges() const;
	vector<int> get_deck_cards() const;
	int get_deck_size() const;
	int get_number_of_infantry() const;
	int get_number_of_artillery() const;
	int get_number_of_cavalry() const;

	int inc_number_of_exchanges();

private:
	//0:Infantry; 1:Artillery; 2:Cavalry
	vector<int> deck_cards;
	int number_of_exchanges;
	int deck_size;
};
