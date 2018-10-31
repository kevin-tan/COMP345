/*
 * Hand.h
 *
 */

#pragma once

#include <iostream>
#include <vector>

class Deck;
using std::vector;

class Hand {
public:
	Hand();
	int exchange(Deck* deck);

	vector<int> get_hand_cards() const { return hand_cards; }
	int get_hand_size() const { return hand_size; }
	int get_number_of_infantry() const { return hand_cards[0]; }
	int get_number_of_artillery() const { return hand_cards[1]; }
	int get_number_of_cavalry() const { return hand_cards[2]; }

	void inc_hand_size() { hand_size++; }
	void inc_hand_card(int index) { hand_cards[index]++; }

private:
	//0:Infantry; 1:Artillery; 2:Cavalry
	vector<int> hand_cards;
	int hand_size;
};
