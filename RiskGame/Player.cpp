#include "stdafx.h"
#include "Player.h"

using std::string;

static int input_check(vector<Vertex> v) {
	int t = 0;
	using namespace std;
	cin >> t;
	while (t < 0 || t >= v.size()) {
		cout << "Please input a number from 0 to " << v.size() - 1 << endl;
		cin >> t;
	}
	return t;
}

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

void Player::attack(Map& map) {
	using namespace std;

	Graph& g = map.get_graph();

	// Printing countries for player
	cout << "Select a country to attack from: " << endl;
	int i = 0;
	vector<Vertex> from_countries = vector<Vertex>();
	for (Vertex v : countries) {
		if (g[v].army_size >= 2) {
			from_countries.push_back(v);
			cout << "  (" << i << ")  " << g[v].country << endl;
			i++;
		}
	}

	// Country choice and checking
	cout << "Country choice: ";
	int from_country_choice = input_check(from_countries);

	// Printing adjacent countries to country choice
	cout << "Select an adjacent country to attack to: " << endl;
	vector<Vertex> adj_countries = map.get_adjacent_countries(from_countries[from_country_choice]);
	for (int i = 0; i < adj_countries.size(); i++) {
		cout << "  (" << i << ")  " << g[adj_countries[i]].country << endl;
	}

	// Country to attack to
	cout << "Country choice: ";
	int to_country_choice = input_check(adj_countries);

	// Attacker rolling chosen number dice for attack per army (army size - 1)
	int const attack_army = g[from_countries[from_country_choice]].army_size - 1;
	int a_max_dice = attack_army >= 3 ? 3 : attack_army;
	int a_num_roll = 0;
	cout << "Player " << name << ", choose number of dice to roll to attack (1-" << a_max_dice << "): ";
	cin >> a_num_roll;
	while (a_num_roll <= 0 || a_num_roll > a_max_dice) {
		cout << "Player " << name << ", choose number of dice to roll to attack (1-" << a_max_dice << ") only: ";
		cin >> a_num_roll;
	}
	vector<int> attack_rolls = dice_rolling_facility.rollDice(a_num_roll);

	// Defender rolling chosen number dice for attack per army (army size)
	const int number_of_defends = g[adj_countries[to_country_choice]].army_size;
	int d_max_dice = number_of_defends >= 2 ? 2 : number_of_defends;
	int d_num_roll = 0;
	Player* p = g[adj_countries[to_country_choice]].player;
	cout << "Player " << p->get_name() << ", choose number of dice to roll to defend (1-" << d_max_dice << "): ";
	cin >> d_num_roll;
	while (d_num_roll <= 0 || d_num_roll > d_max_dice) {
		cout << "Player " << p->get_name() << ", choose number of dice to roll to defend (1-" << d_max_dice << ") only: ";
		cin >> d_num_roll;
	}
	vector<int> defend_rolls = dice_rolling_facility.rollDice(d_num_roll);

	// Before attack
	Player* attacker = g[from_countries[from_country_choice]].player;
	Player* defender = g[adj_countries[to_country_choice]].player;
	cout << "Country : " << g[from_countries[from_country_choice]].country << " owned by " << g[from_countries[from_country_choice]].player->get_name() << " has " << g[from_countries[from_country_choice]].army_size << " armies." << endl;
	cout << "Attacker owns: ";
	for (Vertex v : attacker->get_countries()) {
		cout << g[v].country << " ";
	}
	cout << endl;
	cout << "Country : " << g[adj_countries[to_country_choice]].country << " owned by " << g[adj_countries[to_country_choice]].player->get_name() << " has " << g[adj_countries[to_country_choice]].army_size << " armies." << endl;
	cout << "Defender owns: ";
	for (Vertex v : defender->get_countries()) {
		cout << g[v].country << " ";
	}
	cout << endl;


	// Print the rolls
	cout << "Attack rolls: ";
	for (int v : attack_rolls) {
		cout << v << " ";
	}
	cout << endl;
	cout << "Defend rolls: ";
	for (int v : defend_rolls) {
		cout << v << " ";
	}
	cout << endl;

	// Eliminating army phase
	int max_army = attack_rolls.size() > defend_rolls.size() ? attack_rolls.size() : defend_rolls.size();
	int d_index = 0, a_index = 0;
	bool elimination_phase = true;
	while (elimination_phase) {
		// Ref to army size of attacker and defender
		int& atk_army_size = g[from_countries[from_country_choice]].army_size;
		int& def_army_size = g[adj_countries[to_country_choice]].army_size;
		const int atk_army_size_before = atk_army_size;

		if (d_index < defend_rolls.size() && a_index < attack_rolls.size()) {
			if (defend_rolls[d_index] > attack_rolls[a_index]) {
				atk_army_size--;
			} else if (defend_rolls[d_index] == attack_rolls[a_index]) {
				// Other player dice will not matter, exit elimination phase
				atk_army_size--;
				elimination_phase = false;
			} else {
				def_army_size--;
			}
			d_index++;
			a_index++;
		} else {
			if (def_army_size == 0) {
				int army_to_move = 0;
				cout << "You've successfully defeated " << g[adj_countries[to_country_choice]].player->get_name() << ", how many armies would you like to move from " << g[from_countries[from_country_choice]].country << " : ";
				cin >> army_to_move;
				while (army_to_move <= 0 || army_to_move >= atk_army_size) {
					cout << "Please enter a number of armies from 1 to " << (atk_army_size - 1) << " : ";
					cin >> army_to_move;
				}
				atk_army_size -= army_to_move;
				def_army_size = army_to_move;
				Vertex defeated_country = adj_countries[to_country_choice];
				g[defeated_country].player->remove_country(defeated_country, map);
				this->add_country(defeated_country, map);
			}
			elimination_phase = false;
		}
	}

	// After attack
	cout << "Country : " << g[from_countries[from_country_choice]].country << " owned by " << g[from_countries[from_country_choice]].player->get_name() << " has " << g[from_countries[from_country_choice]].army_size << " armies." << endl;
	cout << "Attacker owns: ";
	for (Vertex v : attacker->get_countries()) {
		cout << g[v].country << " ";
	}
	cout << endl;
	cout << "Country : " << g[adj_countries[to_country_choice]].country << " owned by " << g[adj_countries[to_country_choice]].player->get_name() << " has " << g[adj_countries[to_country_choice]].army_size << " armies." << endl;
	cout << "Defender owns: ";
	for (Vertex v : defender->get_countries()) {
		cout << g[v].country << " ";
	}
	cout << endl;
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
			map.add_armies(v, army);
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

void Player::remove_country(Vertex& country, Map& map) {
	countries.erase(std::remove(countries.begin(), countries.end(), country), countries.end());;
	map.set_country_owner(nullptr, country);
}
