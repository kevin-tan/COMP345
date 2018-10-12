/*
 * Hand.cpp
 * 
 */

#include <iostream>
#include "Hand.h"
#include <vector>

using namespace std;

int Hand:: exchange(){

	int numberOfArmies = 0;

	if (hand.size() < 3){
		return 0;
	}
	else {
			int infantry = 0, artillery = 0,cavalry = 0;

			for(int i = 0; i < hand.size(); i++)
			{
				if(hand[i] == 1){
					infantry++;
				}

				else if(hand[i] == 2){
					artillery++;
				}

				else
					cavalry++;
			}

			if(infantry >= 3 || artillery >= 3 || cavalry >= 3 || 
            (cavalry >= 1 && infantry >= 1 && artillery >= 1))
			{

				numberOfArmies += timesExchanged * 5;
				timesExchanged++;
				return numerOfArmies;
			}
			else
				return 0;
		 }


	}