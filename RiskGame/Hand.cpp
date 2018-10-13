/*
 * Hand.cpp
 *
 */

#include "stdafx.h"
#include "Hand.h"
#include <vector>

int Hand::exchange(int& number_of_exchanges) {
	int get_number_of_armies(int number_of_exchanges);
	void remove_cards(std::vector<std::string>& hand_cards, std::string army, int army_count);

	const std::string INFANTRY = "Infantry";
	const std::string ARTILLERY = "Artillery";
	const std::string CAVALRY = "Cavalry";

	int number_of_armies = 0;

	if (hand_cards.size() < 3) {
		return 0;
	}

	int number_of_infantry = 0, number_of_artillery = 0, number_of_cavalry = 0;

	for (int i = 0; i < hand_cards.size(); i++) {
		if (hand_cards[i] == INFANTRY)
			number_of_infantry++;
		else if (hand_cards[i] == ARTILLERY)
			number_of_artillery++;
		else if (hand_cards[i] == CAVALRY)
			number_of_cavalry++;
	}

	if (number_of_infantry >= 3) {
		number_of_armies = get_number_of_armies(number_of_exchanges);
		remove_cards(hand_cards, INFANTRY, 3);
	} else if (number_of_artillery >= 3) {
		number_of_armies = get_number_of_armies(number_of_exchanges);
		remove_cards(hand_cards, ARTILLERY, 3);
	} else if (number_of_cavalry >= 3) {
		number_of_armies = get_number_of_armies(number_of_exchanges);
		remove_cards(hand_cards, CAVALRY, 3);
	} else if (number_of_cavalry >= 1 && number_of_infantry >= 1 && number_of_artillery >= 1) {
		number_of_armies = get_number_of_armies(number_of_exchanges);
		remove_cards(hand_cards, INFANTRY, 1);
		remove_cards(hand_cards, ARTILLERY, 1);
		remove_cards(hand_cards, CAVALRY, 1);
	} else {
		return 0;
	}

	number_of_exchanges++;
	return number_of_armies;
}

void remove_cards(std::vector<std::string>& hand_cards, std::string army, int army_count) {
	for (int i = 0; i < hand_cards.size() && army_count > 0; i++) {
		if (hand_cards[i] == army) {
			hand_cards.erase(hand_cards.begin() + i);
			i--;
			army_count--;
		}
	}
}

int get_number_of_armies(int number_of_exchanges) {
	const int INITIAL_ARMIES = 4;
	const int SIXTH_SET_ARMIES = 15;

	if (number_of_exchanges == 0) {
		return INITIAL_ARMIES;
	} else if (number_of_exchanges < 5) {
		return INITIAL_ARMIES + (2 * number_of_exchanges);
	} else if (number_of_exchanges == 5) {
		return SIXTH_SET_ARMIES;
	} else {
		return SIXTH_SET_ARMIES + (5 * (number_of_exchanges - 5));
	}
}
