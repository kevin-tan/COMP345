/*
 * Deck.cpp
 *
 */

#include "stdafx.h"
#include <vector>
#include "Deck.h"
#include "Hand.h"

Deck::Deck(int number_of_countries) {
	number_of_exchanges = 0;
	deck_size = number_of_countries;
	deck_cards = vector<int>(3);

	deck_cards[0] = number_of_countries / 3;
	deck_cards[1] = number_of_countries / 3;
	deck_cards[2] = number_of_countries - deck_cards[1] - deck_cards[0];
}

void Deck::draw(Hand* hand) {
	if (deck_size > 0) {
		int randIndex = rand() % deck_cards.size();
		while (deck_cards[randIndex] == 0) {
			randIndex = rand() % deck_cards.size();
		}

		hand->inc_hand_card(randIndex);
		hand->inc_hand_size();
		deck_cards[randIndex]--;
		deck_size--;
	}
	else {
		std::cout << "Deck is empty." << std::endl;
	}
}

