#include "stdafx.h"
#include "GameStatsViewer.h"


void GameStatsViewer::update() {
	get_game_stats();
}
GameStatsViewer::~GameStatsViewer() {
}

GameStatsViewer::GameStatsViewer(ISubject* subject) : IObserver(subject) {
}

// Main function that display game information
void GameStatsViewer::get_game_stats() const {
	Graph g = dynamic_cast<Map*>(subject)->get_graph();
	bool player_in_vector;

	// Get number of countries on the map
	int numb_of_countries = dynamic_cast<Map*>(subject)->get_countries().size();
	vector<Player*> list_of_players;

	// Get all players on the map
	for (Vertex v : dynamic_cast<Map*>(subject)->get_countries()) {
		player_in_vector = false;
		for (vector<Player*>::iterator i = list_of_players.begin(); i != list_of_players.end(); ++i) {
			if (g[v].player->get_name().compare((*i)->get_name()) == 0)
				player_in_vector = true;
		}
		// Add player to the vector if he/she was not there before
		if (!player_in_vector)
			list_of_players.push_back(g[v].player);
	}
	std::cout << "----------------------------------Game Statistics-----------------------------------------\n";
	if (list_of_players.size() == 1) {
		std::string message = "\n\t\tCongratulations! Player " + list_of_players[0]->get_name() + " has won the game!!!!\n\n";
		std::cout << message;
	}
	else {
		
		std::cout << boost::format("%+16s %+32s %+20s %20s\n") % "Player" % "Countries owned" % "Percentage" % "Armies owned";
		for (Player* p : list_of_players) {
			int armies_owned = 0;
			for (Vertex v : p->get_countries()) {
				armies_owned += g[v].army_size;
			}
			std::cout << boost::format("%+16s %+25s %25.2f %18.0f\n") % p->get_name() % p->get_countries().size() % (p->get_countries().size() * 100 / (double)numb_of_countries) % armies_owned;
		}

	}
	std::cout << "------------------------------------------------------------------------------------------\n";
}
