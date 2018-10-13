/*
 * Deck.h
 *
 */

#pragma once

#include <iostream>
#include <vector>

class Deck {

public:
	Deck(int number_of_countries);
	
	std::vector<std::string> deck_cards;
	int number_of_exchanges;
	
	void draw(std::vector<std::string>& hand_cards);
};