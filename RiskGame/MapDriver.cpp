#include "stdafx.h"
#include "Map.h"
#include <iostream>


// Driver for Map implementation

int main()
{
	Map map;

	std::vector<std::string> map_string = {
		"Alaska,North America,Northwest Territory,Alberta,Kamchatka",
		"Northwest Territory,North America,Alaska,Alberta,Ontario,Greenland",
		"Alberta,North America,Alaska,Northwest Territory,Ontario,Western United States",
		"Greenland,North America,Northwest Territory,Ontario,Quebec,Iceland",
		"Ontario,North America,Northwest Territory,Alberta,Greenland,Quebec,Western United States,Eastern United States",
		"Quebec,North America,Greenland,Ontario,Eastern United States",
		"Western United States,North America,Alberta,Ontario,Eastern United States,Central America",
		"Eastern United States,North America,Ontario,Quebec,Western United States,Central America",
		"Central America,North America,Western United States,Eastern United States,Venezuala",
		"Venezuala,South America,Central America,Peru,Brazil",
		"Peru,South America,Venezuala,Brazil,Argentina",
		"Argentina,South America,Peru,Brazil",
		"Brazil,South America,Venezuala,Peru,Argentina,North Africa",
		"North Africa,Africa,Brazil,Western Europe,Southern Europe,Egypt,East Africa,Congo",
		"Congo,Africa,North Africa,East Africa,South Africa",
		"South Africa,Africa,Congo,East Africa,Madagascar",
		"Madagascar,Africa,East Africa,South Africa",
		"East Africa,Africa,Egypt,Middle East,Congo,North Africa,South Africa,Madagascar",
		"Egypt,Africa,Southern Europe,North Africa,Middle East,East Africa",
		"Iceland,Europe,Greenland,Great Britain,Scandinavia",
		"Great Britain,Europe,Iceland,Scandinavia,Western Europe,Northern Europe",
		"Western Europe,Europe,Great Britain,Northern Europe,Southern Europe,North Africa",
		"Scandinavia,Europe,Iceland,Great Britain,Northern Europe,Ukraine",
		"Northern Europe,Europe,Great Britain,Scandinavia,Ukraine,Southern Europe,Western Europe",
		"Southern Europe,Europe,Northern Europe,Ukraine,Middle East,Egypt,North Africa,Western Europe",
		"Ukraine,Europe,Ural,Afghanistan,Middle East,Southern Europe,Northern Europe,Scandinavia",
		"Middle East,Asia,Ukraine,Afghanistan,India,Southern Europe,Egypt,East Africa",
		"Ural,Asia,Siberia,China,Afghanistan,Ukraine",
		"Afghanistan,Asia,Ural,China,India,Middle East,Ukraine",
		"India,Asia,China,Siam,Afghanistan,Middle East",
		"Siberia,Asia,Yatusk,Irkutsk,Mongolia,China,Ural",
		"China,Asia,Ural,Siberia,Mongolia,Siam,India,Afghanistan",
		"Siam,Asia,China,India,Indonesia",
		"Mongolia,Asia,Siberia,Irkutsk,Japan,China,Kamchatka",
		"Irkutsk,Asia,Siberia,Yatusk,Kamchatka,Mongolia",
		"Yatusk,Asia,Siberia,Irkutsk,Kamchatka",
		"Kamchatka,Asia,Yatusk,Irkutsk,Japan,Alaska,Mongolia",
		"Japan,Asia,Kamchatka,Mongolia",
		"Indonesia,Australia,Siam,New Guinea,Western Australia",
		"New Guinea,Australia,Indonesia,Western Australia,Eastern Australia",
		"Western Australia,Australia,Indonesia,New Guinea,Eastern Australia",
		"Eastern Australia,Australia,Western Australia,New Guinea"
	};

	map.generate_map(map_string);
	map.getAllVertices();
	map.printAllEdges();

	// Temp
	int x;
	std::cin >> x;

	return 0;
}
