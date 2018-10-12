#include "stdafx.h"
#include "Player.h"

Player::Player(std::string name) {
	this->name = name;
	countries = std::vector<Vertex>();
	dice_rolling_facility = DiceRollingFacility();
}

void Player::reinforce() {
	std::cout << "Player's reinforce() method has been called." << std::endl;
}

void Player::attack() {
	std::cout << "Player's attack() method has been called." << std::endl;
}

void Player::fortify() {
	std::cout << "Player's fortify() method has been called." << std::endl;
}

std::vector<Vertex> Player::getCountries() {
	return countries;
}

std::string Player::getName() {
	return name;
}

void Player::add_country(Vertex& country, Map& map) {
	countries.push_back(country);
	map.set_country_owner(this, country);
}
