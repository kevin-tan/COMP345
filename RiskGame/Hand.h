/*
 * Hand.h
 *
 */

#pragma once

#include <iostream>
#include <vector>

class Hand {

public:
	std::vector<std::string> hand_cards;
	int exchange(int& number_of_exchanges);
};
