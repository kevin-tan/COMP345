 #include "stdafx.h"
#include <cstdlib>
#include <time.h>

#include "DiceRollingFacility.h"
#include "MapLoader.h"
#include "Player.h"
#include "Hand.h"
#include "Deck.h"

void display_player_data(Map&, Deck&, Player*);
void no_countries_no_cards(Map&, Deck&, Player*);
void four_countries_no_cards(Map&, Deck&, Player*);
void four_countries_three_cards(Map&, Deck&, Player*);
void one_continent_four_cards(Map&, Deck&, Player*);
void two_continents_five_cards(Map&, Deck&, Player*);

int main() {
	srand(time(0));
	Map map = read_map_file("Maps/World.map");
	Deck deck(42);
	Player *player = new Player();
	int choice;
	do {
		std::cout << "\n--------------------------------------------\n";
		std::cout << "1. Player has no countries and no cards\n";
		std::cout << "2. Player has four countries and no cards\n";
		std::cout << "3. Player has four countries and three cards\n";
		std::cout << "4. Player has one continent and four cards\n";
		std::cout << "5. Player has two continents and five cards\n";
		std::cout << "0. Exit\n";
		std::cout << "Choose a case: ";
		std::cin >> choice;
		switch (choice) {
		case 1:
			no_countries_no_cards(map, deck, player); break;
		case 2:
			four_countries_no_cards(map, deck, player); break;
		case 3:
			four_countries_three_cards(map, deck, player); break;
		case 4:
			one_continent_four_cards(map, deck, player); break;
		case 5:
			two_continents_five_cards(map, deck, player); break;
		default: break;
		}
		// Refresh player to avoid countries/cards stacking between multiple cases
		delete player;
		player = new Player();
	} while (choice != 0);

	return 0;
}


void no_countries_no_cards(Map& map, Deck& deck, Player* player) {
	display_player_data(map, deck, player);
	player->reinforce(map, deck);
}

void four_countries_no_cards(Map& map, Deck& deck, Player* player) {
	Vertex x = map.find_country_vertex("Congo");
	player->add_country(x, map);
	x = map.find_country_vertex("Madagascar");
	player->add_country(x, map);
	x = map.find_country_vertex("East Africa");
	player->add_country(x, map);
	x = map.find_country_vertex("Egypt");
	player->add_country(x, map);

	display_player_data(map, deck, player);
	player->reinforce(map, deck);
}

void four_countries_three_cards(Map& map, Deck& deck, Player* player) {
	Vertex x = map.find_country_vertex("Alaska");
	player->add_country(x, map);
	x = map.find_country_vertex("Alberta");
	player->add_country(x, map);
	x = map.find_country_vertex("Ontario");
	player->add_country(x, map);
	x = map.find_country_vertex("Northwest Territory");
	player->add_country(x, map);

	deck.draw(player->get_hand());
	deck.draw(player->get_hand());
	deck.draw(player->get_hand());

	display_player_data(map, deck, player);
	player->reinforce(map, deck);
}

void one_continent_four_cards(Map& map, Deck& deck, Player* player) {
	// South America
	Vertex x = map.find_country_vertex("Venezuala");
	player->add_country(x, map);
	x = map.find_country_vertex("Peru");
	player->add_country(x, map);
	x = map.find_country_vertex("Argentina");
	player->add_country(x, map);
	x = map.find_country_vertex("Brazil");
	player->add_country(x, map);

	deck.draw(player->get_hand());
	deck.draw(player->get_hand());
	deck.draw(player->get_hand());
	deck.draw(player->get_hand());

	display_player_data(map, deck, player);
	player->reinforce(map, deck);
}

void two_continents_five_cards(Map& map, Deck& deck, Player* player) {
	// Asia
	Vertex x = map.find_country_vertex("Middle East");
	player->add_country(x, map);
	x = map.find_country_vertex("Kamchatka");
	player->add_country(x, map);
	x = map.find_country_vertex("Japan");
	player->add_country(x, map);
	x = map.find_country_vertex("Ural");
	player->add_country(x, map);
	x = map.find_country_vertex("Afghanistan");
	player->add_country(x, map);
	x = map.find_country_vertex("India");
	player->add_country(x, map);
	x = map.find_country_vertex("Siberia");
	player->add_country(x, map);
	x = map.find_country_vertex("China");
	player->add_country(x, map);
	x = map.find_country_vertex("Siam");
	player->add_country(x, map);
	x = map.find_country_vertex("Mongolia");
	player->add_country(x, map);
	x = map.find_country_vertex("Irkutsk");
	player->add_country(x, map);
	x = map.find_country_vertex("Yatusk");
	player->add_country(x, map);
	// Australia
	x = map.find_country_vertex("Western Australia");
	player->add_country(x, map);
	x = map.find_country_vertex("Indonesia");
	player->add_country(x, map);
	x = map.find_country_vertex("New Guinea");
	player->add_country(x, map);
	x = map.find_country_vertex("Eastern Australia");
	player->add_country(x, map);

	deck.draw(player->get_hand());
	deck.draw(player->get_hand());
	deck.draw(player->get_hand());
	deck.draw(player->get_hand());
	deck.draw(player->get_hand());

	display_player_data(map, deck, player);
	player->reinforce(map, deck);
}

void display_player_data(Map& map, Deck& deck, Player* player) {
	std::cout << "\nCountries: \n";
	if (player->get_countries().size() == 0)
		std::cout << "Player does not have countries\n";
	for (Vertex x : player->get_countries())
		std::cout << map.get_graph()[x].country << std::endl;

	std::cout << "\nCards: \n";
	player->get_hand()->display_hand();
}