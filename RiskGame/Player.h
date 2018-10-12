#pragma once

#include "Map.h"

class Player: public PlayerAbstract
{
	std::vector<Vertex> countries;
public:
	Player(std::string name);

	// Override method
	void reinforce() override;
	void attack() override;
	void fortify() override;

	std::string getName() override;

	std::vector<Vertex> getCountries();
	void add_country(Vertex& country, Map& map);
	
};

