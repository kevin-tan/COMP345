/*
 * Hand.h
 *
 */

#pragma once

#include <iostream>
#include <vector>

class Hand {

int timesExchanged = 1;

public:
	std::vector<int> hand;
	int exchange();

};