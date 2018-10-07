#include "stdafx.h"
#include "MapLoader.h"
#include <fstream>
#include <sstream>

Map read_map_file(std::string map_file) {
	using namespace std;

	const int TERRITORY_POS = 0;
	const int CONTINENT_POS = 3;
	const int ADJACENCIES_POS = 4;
	const string TERRITORIES_HEADER = "[Territories]";
	const string CONTINENTS_HEADER = "[Continents]";

	string line;
	string delimited_line;
	int position_counter;
	bool territories_flag = false;
	bool continent_flag = false;

	ifstream input(map_file);

	Map map;

	while (getline(input, line)) {
		//NOT USED YET
		if (line == CONTINENTS_HEADER) {
			continent_flag = true;
		}
		else if (continent_flag && !line.empty() && !territories_flag && line != TERRITORIES_HEADER) {
			stringstream ss(line);
			position_counter = 0;
			while (getline(ss, delimited_line, '=')) {
				if (position_counter == 0) {
					cout << "Top Continent: " << delimited_line;
					map.add_continents(delimited_line);
					position_counter++;
				}
				else if (position_counter == 1) {
					cout << "=" << delimited_line << endl;
				}
			}
		}

		if (line == TERRITORIES_HEADER) {
			territories_flag = true;
		}
		else if (territories_flag && !line.empty()) {
			stringstream ss(line);
			position_counter = 0;
			Vertex node;
			while (getline(ss, delimited_line, ',')) {
				if (position_counter == TERRITORY_POS) {
					node = map.add_territory(delimited_line);
				}
				else if (position_counter == CONTINENT_POS) {
					map.add_continent_to_territory(node, delimited_line);
				}
				else if (position_counter >= ADJACENCIES_POS) {
					map.add_adjacency(node, delimited_line);
				}
				position_counter++;
			}
		}
	}

	return map;
}
