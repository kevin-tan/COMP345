#include "stdafx.h"
#include "Player.h"

Player::Player() {
	countries = std::vector<Vertex>();
	dice_rolling_facility = DiceRollingFacility();
	hand = Hand();
}

Player::Player(string name) {
	countries = std::vector<Vertex>();
	dice_rolling_facility = DiceRollingFacility();
	hand = Hand();
	this->name = name;
}

void Player::reinforce() {
	std::cout << "Printing from inside Player's reinforce() method." << std::endl;
}

void Player::attack() {
	std::cout << "Printing from inside Player's attack() method." << std::endl;
}

void Player::fortify() {
	std::cout << "Printing from inside Player's fortify() method." << std::endl;
}

vector<Vertex> Player::get_countries() const { return countries; }

DiceRollingFacility* Player::get_dice_rolling_facility() { return &dice_rolling_facility; }

Hand* Player::get_hand() { return &hand; }

string Player::get_name() {
	return name;
}

void Player::add_country(Vertex& country, Map& map) {
	countries.push_back(country);
	map.set_country_owner(this, country);
}
