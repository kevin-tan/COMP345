/*
 * Hand.h
 *  
 */

#ifndef HAND_H_
#define HAND_H_

#include <iostream>
#include <vector>

using namespace std;

class Hand{

public:

    vector<int> hand;
	int exchange();
	int timesExchanged = 1;

};
#endif /* HAND_H_ */