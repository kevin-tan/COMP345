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

	graph& g = map.get_graph();
	std::cout << "Printing from inside Player's fortify() method." << std::endl;

	//print players countries and armies
	cout << "Select a country to move army from: " << endl;
	int i = 0;
	vector<Vertex> from_countries = vector<Vertex>();
	for (Vertex v : countries) {
			cout << "Country: " << i << g[v].country << "- Number of armies: " << g[v].army_size << endl;
			i++;
	}

	//print adjacent countries
	cout << "Select an adjacent country to move army to: " << endl;
	vector<Vertex> adj_countries = map.get_adjacent_countries(from_countries[from_country_choice]);
	for (int i = 0; i < adj_countries.size(); i++) {
		cout << "  (" << i << ")  " << g[adj_countries[i]].country << endl;
	}
	
	//select country to move army from 
	int from_country_choice = input_check(from_countries);
	cin >> from_country_choice;

	//select country to move army to
	int to_country_choice = input_check(adj_countries);
	cin >> to_country_choice;

	//select number of armies to move
	int moveArmies;
	cin >> moveArmies;

	//assign number of armies after fortification
	int armiesFrom = from_country_choice[from_countries - 1]->g[v].army_size;
	int armiesTo = to_country_choice[adj_countries]->g[v].army_size;
	from_countries[from_country_choice]->g[v].army_size (armiesFrom - moveArmies);
	adj_countries[to_country_choice]->g[v].army_size (armiesTo + moveArmies);
}

vector<Vertex> Player::get_countries() const { return countries; }

DiceRollingFacility* Player::get_dice_rolling_facility() { return &dice_rolling_facility; }

Hand* Player::get_hand() { return &hand; }

void Player::add_country(Vertex& country, Map& map) {
	countries.push_back(country);
	map.set_country_owner(this, country);
}
