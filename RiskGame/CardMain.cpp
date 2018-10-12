/*
 * CardMain.cpp
 * 
 */

#include "stdafx.h"
#include "Hand.h"
#include "Deck.h"
#include <ctime>

using namespace std;

//int main(){
//
//	int numberOfCountries = 42;
//
//    Deck game(numberOfCountries);
//    Hand player;
//
//    srand (time(0));
//
//	for(int i = 0; i < numberOfCountries; i++)
//	{
//		game.draw(player.hand);
//
//		//call exchange() for random values
//		if(i ==2 || i == 3 || i == 4)
//
//			cout<<"Number of armies:"<<player.exchange()<<endl;
//
//	}
//
//
//	int infantry = 0, cavalry = 0, artillery = 0;
//
//	for(int i = 0; i < player.hand.size(); i++)
//	{
//		if(player.hand[i] == 1)
//			infantry++;
//
//		else if(player.hand[i] == 2)
//			cavalry++;
//
//		else
//			artillery++;
//
//	}
//
//	cout<< endl<<"There are: "<< infantry << " infantry, "<< artillery<< " artilleries and "
//    << cavalry<<" cavalry."<<endl;
//
//}
