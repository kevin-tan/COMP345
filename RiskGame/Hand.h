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

	vector<int> get_hand_cards() const;
	int get_hand_size() const;
	int get_number_of_infantry() const;
	int get_number_of_artillery() const;
	int get_number_of_cavalry() const;

	void inc_hand_size();
	void inc_hand_card(int index);

private:
	//0:Infantry; 1:Artillery; 2:Cavalry
	vector<int> hand_cards;
	int hand_size;
};
