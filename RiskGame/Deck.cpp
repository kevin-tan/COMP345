/*
 * Deck.cpp
 * 
 */

#include <iostream>
#include "Deck.h"
#include <vector>
#include "Hand.h"
#include <ctime>

using namespace std;

Deck::Deck(int numberOfCountries){

		deck.resize(numberOfCountries);

		for(int i = 0; i < numberOfCountries/3; i++){
		        deck[i]=1;
		}

		for(int i = numberOfCountries/3; i<numberOfCountries/3*2; i++){
				deck[i]=2;
		}
		
		for(int i = numberOfCountries/3*2; i<numberOfCountries; i++){
				deck[i]=3;
		}

}

void Deck:: draw(vector<int>& hand){

		int randIndex = rand() % deck.size();
		hand.push_back(deck[randIndex]);
		deck.erase(deck.begin() + randIndex);
        
}

