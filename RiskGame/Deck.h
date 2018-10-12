/*
 * Deck.h
 * 
 */

#ifndef DECK_H_
#define DECK_H_

#include <iostream>
#include <vector>

using namespace std;

class Deck{

	public:

		vector<int> deck;
		Deck(int numberOfCountries);
		void draw(vector<int>&);

};


#endif /* DECK_H_ */