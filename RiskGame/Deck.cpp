/*
 * Deck.cpp
 *
 */

#include "stdafx.h"
#include <vector>
#include "Deck.h"
#include "Hand.h"

Deck::Deck() {
}

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

int Deck::get_number_of_exchanges() const { return number_of_exchanges; }

vector<int> Deck::get_deck_cards() const { return deck_cards; }

int Deck::get_deck_size() const { return deck_size; }

int Deck::get_number_of_infantry() const { return deck_cards[0]; }

int Deck::get_number_of_artillery() const { return deck_cards[1]; }

int Deck::get_number_of_cavalry() const { return deck_cards[2]; }

int Deck::inc_number_of_exchanges() { return ++number_of_exchanges; }

