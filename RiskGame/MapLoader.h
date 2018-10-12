#pragma once
#include "Map.h"
#include <string>

/* 
   Responsible for reading an input "Map" file and parsing the relevant details 
   which are: Continents, continent bonuses, territory, territory's continent, territory's adjacencies
   Rejects unreadable/invalid map files. 
*/
Map read_map_file(std::string map_file);