#include "stdafx.h"
#include "Player.h"

Player::Player() {
	countries = std::vector<Vertex>();
	dice_rolling_facility = DiceRollingFacility();
	hand = Hand();
	name = "";
}

Player::Player(string name) {
	countries = std::vector<Vertex>();
	dice_rolling_facility = DiceRollingFacility();
	hand = Hand();
	this->name = name;
}

void Player::reinforce(Map& map, Deck& deck) {
	if (countries.size() == 0) {
		std::cout << "\nYou don't have countries to reinforce!";
	}
	else {
		int total_army, country_armies, continent_armies, exchange_armies = 0;
		std::string want_change;

		// Get part of reinforcement based on owned countries
		if (countries.size() / 3 <= 3)
			country_armies = 3;
		else
			country_armies = countries.size() / 3;

		// Get part of reinforcement based on owned continents
		continent_armies = armies_from_continents(map);

		// Get part of reinforcement from the card exchange
		if (hand.get_hand_size() >= 5) {
			std::cout << "You have more than 4 cards in your hand, time to exchange" << std::endl;
			while (hand.get_hand_size() >= 5)
				exchange_armies += hand.exchange(&deck);
		}
		if (hand.can_exchange()) {
			std::cout << "You have cards for exchange, would you like to do it now? (y/n) ";
			std::cin >> want_change;
			if (want_change.compare("y") == 0 || want_change.compare("Y") == 0) {
				exchange_armies += hand.exchange(&deck);
			}
		}
		total_army = country_armies + continent_armies + exchange_armies;

		// Place armies on the map
		do {
			total_army = choose_country_to_add_army(map, total_army);
		} while (total_army != 0);
		display_countries_and_armies(map);
		std::cout << "\nYou have successfully placed all the units\n";
	}
}

void Player::part3_reinforce() {
	std::cout << "Printing from inside Player " << name << "'s reinforce() method." << std::endl;
}

void Player::part3_attack() {
	std::cout << "Printing from inside Player " << name << "'s attack() method." << std::endl;
}

void Player::part3_fortify() {
	std::cout << "Printing from inside Player " << name << "'s fortify() method." << std::endl;
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

// Get amries from all the continents owned by the player
int Player::armies_from_continents(Map& map){
	int armies = 0;
	std::vector<std::string> continent_countries;
	std::vector<std::string> owned_countries;

	// Get list of countries owned by a player
	for (Vertex v : countries)
		owned_countries.push_back(map.get_graph()[v].country);

	// Loop for each continent on the map
	for (std::string continent : map.get_continents()) {
		// Get list of contries from the continent
		continent_countries = map.get_countries_in_continent(map.get_graph(), continent);

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
// Add army to the country 
int Player::choose_country_to_add_army(Map& map, int total_army) {
	int index, index_chosen, army;

	// Print all the options
	std::cout << "\nNumber of units that you can place is: " << total_army;
	index = display_countries_and_armies(map);

	// Choose country to add army
	std::cout << "\nChoose index of the country to which you would like to add armies: ";
	do {
		std::cin >> index_chosen;
		if (index_chosen > index || index_chosen < 1) {
			std::cout << "The index must be more than zero and less than " << (index+1) << "!\nEnter new value:";
		}
	} while (index_chosen > index || index_chosen < 1);
	index = 0;

	// Choose how many units to add
	std::cout << "How many units you want to add: ";
	do {
		std::cin >> army;
		if (army < 1 || army > total_army) {
			std::cout << "Number of units should be more than zero and less than " << (total_army + 1) << "!\nEnter new value:";
		}
	} while (army < 1 || army > total_army);
	
	for (Vertex v : countries) {
		if ((index_chosen - 1) == index) {
			map.add_army_to_country(map.get_graph(), map.get_graph()[v].country, army);
			break;
		}
		index++;
	}
	return total_army - army;
}
	// Print all counties and corresponding units
int Player::display_countries_and_armies(Map& map) {
	int index = 0;
	std::cout << "\nCountries and armies that you possess:\n\n";
	std::cout << boost::format("%-10s %-20s %-8s\n") % "Index" % "Country name" % "Army size";
	for (Vertex v : countries) {
		std::cout << boost::format("%-10s %-20s %-8s\n") % (index + 1) % map.get_graph()[v].country % map.get_graph()[v].army_size;
		index++;
	}
	return index;
}

void Player::clear_countries_temp() {
	countries.clear();
}
