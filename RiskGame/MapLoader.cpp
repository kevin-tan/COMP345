#include "stdafx.h"
#include "MapLoader.h"
#include <fstream>
#include <sstream>

Map read_map_file(std::string map_file) {
	using namespace std;

	const string TERRITORIES_HEADER = "[Territories]";
	const string CONTINENTS_HEADER = "[Continents]";

	Map map;
	string line;
	string delimited_line;
	int position_counter;
	bool territories_flag = false;
	bool continent_flag = false;

	ifstream input(map_file);

	if (input.good()) {
		while (getline(input, line)) {
			if (line == CONTINENTS_HEADER) {
				continent_flag = true;
			}
			else if (continent_flag && !line.empty() && !territories_flag && line != TERRITORIES_HEADER) {
				stringstream ss(line);
				position_counter = 0;

				while (getline(ss, delimited_line, '=')) {
					if (position_counter == 0) {
						map.add_continents(delimited_line);
					}
					else if (position_counter == 1) {
						//Continent bonus
					}
					position_counter++;
				}

				if (position_counter < 2) {
					throw exception(("Invalid Map file. Line \"" + line + "\" is not in the correct format of: 'Continent'='Bonus'").c_str());
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
					if (position_counter == 0) {
						node = map.add_territory(delimited_line);
					}
					else if (position_counter == 3) {
						map.add_continent_to_territory(node, delimited_line);
					}
					else if (position_counter >= 4) {
						map.add_adjacency(node, delimited_line);
					}
					position_counter++;
				}

				if (position_counter < 5) {
					throw  exception(("Invalid Map file. Line \"" + line +
						"\" is not in the correct format of: 'Territory','x-coord','y-coord','Continent','Adjacencies',...").c_str());
				}
			}
		}
	}
	else {
		throw exception("Input file cannot be read");
	}

	return map;
}