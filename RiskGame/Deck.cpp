/*
 * Deck.cpp
 *
 */

#include "stdafx.h"
#include <vector>
#include "Deck.h"

Deck::Deck(int number_of_countries) {
	number_of_exchanges = 0;
	
	deck_cards.resize(number_of_countries);

	for (int i = 0; i < number_of_countries / 3; i++) {
		deck_cards[i] = "Infantry";
	}
	for (int i = number_of_countries / 3; i < number_of_countries / 3 * 2; i++) {
		deck_cards[i] = "Artillery";
	}
	for (int i = number_of_countries / 3 * 2; i < number_of_countries; i++) {
		deck_cards[i] = "Cavalry";
	}
}

void Deck::draw(std::vector<std::string>& hand_cards) {
	int randIndex = rand() % deck_cards.size();
	hand_cards.push_back(deck_cards[randIndex]);
	deck_cards.erase(deck_cards.begin() + randIndex);
}