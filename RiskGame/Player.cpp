#include "stdafx.h"
#include "Player.h"
#include "Game.h"
#include "Human.h"

using std::string;

Player::Player() {
	countries = std::vector<Vertex>();
	dice_rolling_facility = DiceRollingFacility();
	hand = Hand();
	name = "";
}

Player::Player(string name, PlayerStrategy player_strategy) {
	countries = std::vector<Vertex>();
	dice_rolling_facility = DiceRollingFacility();
	hand = Hand();
	this->name = name;
	this->player_strategy = player_strategy;
}

void Player::reinforce(Game* game) {
	player_strategy.execute_reinforcement_strategy(game, this);
}

void Player::attack(Game* game) {
	player_strategy.execute_attack_strategy(game, this);
}

void Player::fortify(Game* game) {
	player_strategy.execute_fortify_strategy(game, this);
}

vector<Vertex> Player::get_countries() const { return countries; }

DiceRollingFacility* Player::get_dice_rolling_facility() { return &dice_rolling_facility; }

Hand* Player::get_hand() { return &hand; }

string Player::get_name() const {
	return name;
}

void Player::add_country(Vertex& country, Map& map) {
	countries.push_back(country);
	map.set_country_owner(this, country);
}

void Player::clear_countries_temp() {
	countries.clear();
}

void Player::remove_country(Vertex& country, Map& map) {
	countries.erase(std::remove(countries.begin(), countries.end(), country), countries.end());
	map.set_country_owner(nullptr, country);
}

// Get armies from all the continents owned by the player
int Player::armies_from_continents(Map* map) {
	int armies = 0;
	std::vector<std::string> continent_countries;
	std::vector<std::string> owned_countries;

	// Get list of countries owned by a player
	for (Vertex v : get_countries())
		owned_countries.push_back(map->get_graph()[v].country);

	// Loop for each continent on the map
	for (std::string continent : map->get_continents()) {
		// Get list of contries from the continent
		continent_countries = map->get_countries_in_continent(map->get_graph(), continent);

		// Check if continent_countries is a substet of owned_coutries
		std::sort(owned_countries.begin(), owned_countries.end());
		std::sort(continent_countries.begin(), continent_countries.end());

		if (includes(owned_countries.begin(), owned_countries.end(), continent_countries.begin(), continent_countries.end())) {
			if (continent.compare("Asia") == 0)
				armies += 7;
			else if (continent.compare("North America") == 0)
				armies += 5;
			else if (continent.compare("Europe") == 0)
				armies += 5;
			else if (continent.compare("Africa") == 0)
				armies += 3;
			else if (continent.compare("South America") == 0)
				armies += 2;
			else if (continent.compare("Australia") == 0)
				armies += 2;
		}

		continent_countries.clear();
	}
	return armies;
}

bool Player::is_human() {
	Human* h = dynamic_cast<Human*> (player_strategy.get_strategy());
	if(h != nullptr) {
		return true;
	}

	return false;
}
