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

void Player::fortify(Map& map) {
	using namespace std;

	Graph& g = map.get_graph();
	std::cout << "Printing from inside Player's fortify() method." << std::endl;

	//print players countries and armies
	cout << "Select a country to move army from: " << "/n" << endl;
	int i = 0;
	vector<Vertex> from_countries = vector<Vertex>();
	for (Vertex v : countries) {
		cout << "Country: " << i << g[v].country << "- Number of armies: " << g[v].army_size << endl;
		i++;
	}

	//select country to move army from 
	int from_country_choice;
	cin >> from_country_choice;

	//print adjacent countries
	cout << "Select an adjacent country to move army to: " << "/n" << endl;
	vector<Vertex> adj_countries = map.get_adjacent_countries(from_countries[from_country_choice]);
	for (int i = 0; i < adj_countries.size(); i++) {
		cout << "  (" << i << ")  " << g[adj_countries[i]].country << endl;
	}

	//select country to move army to
	int to_country_choice;
	cin >> to_country_choice;

	//select number of armies to move and validate that number of armies is > 1 but less than source country - 1
	int moveArmies;
	cin >> moveArmies;

	//assign number of armies after fortification
	int armiesFrom = g[from_countries[from_country_choice]].army_size;
	int armiesTo = g[adj_countries[to_country_choice]].army_size;
	g[from_countries[from_country_choice]].army_size = armiesFrom - moveArmies;
	g[adj_countries[to_country_choice]].army_size = armiesTo + moveArmies;
}

vector<Vertex> Player::get_countries() const { return countries; }

DiceRollingFacility* Player::get_dice_rolling_facility() { return &dice_rolling_facility; }

Hand* Player::get_hand() { return &hand; }

void Player::add_country(Vertex& country, Map& map) {
	countries.push_back(country);
	map.set_country_owner(this, country);
}
