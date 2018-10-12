/*
 * Deck.h
 *
 */

#pragma once

#include <iostream>
#include <vector>

class Deck {

public:
	std::vector<int> deck;
	Deck(int numberOfCountries);
	void draw(std::vector<int>&);
};