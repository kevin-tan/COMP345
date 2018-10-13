#pragma once

#include "Map.h"
#include "DiceRollingFacility.h"
#include "Hand.h"

class Player: public PlayerAbstract
{
	std::vector<Vertex> countries;
	DiceRollingFacility dice_rolling_facility;
	Hand hand;

public:
	Player(std::string name);

	// Override method
	void reinforce() override;
	void attack() override;
	void fortify() override;

	std::string getName() override;
	std::vector<Vertex> getCountries();
	DiceRollingFacility& getDiceRollingFacility();
	Hand& getHand();
	
	void add_country(Vertex& country, Map& map);
};

