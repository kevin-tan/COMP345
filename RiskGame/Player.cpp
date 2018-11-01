#include "stdafx.h"
#include "Player.h"

Player::Player() {
	countries = std::vector<Vertex>();
	dice_rolling_facility = DiceRollingFacility();
	hand = Hand();
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

std::vector<Vertex> Player::getCountries() {
	return countries;
}

void Player::add_country(Vertex& country, Map& map) {
	countries.push_back(country);
	map.set_country_owner(this, country);
}

DiceRollingFacility& Player::getDiceRollingFacility() {
	return dice_rolling_facility;
}

Hand& Player::getHand() {
	return hand;
}
