#pragma once

#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/named_function_params.hpp>
#include <sstream>

// Defining properties for Graph provided by Boost
struct VertexProperty {
	// Node info
	std::string continent;
	std::string country;

	// Player info
	std::string player; //Player type should replace string
	int army_size;
};

// Define the type of Graph and its properties we want
typedef boost::adjacency_list<boost::vecS, boost::vecS,
	boost::directedS,
	VertexProperty,
	boost::no_property> Graph;
// Type aliasing with Vertex for vertex_descriptor
typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;
typedef boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

class Map {
	std::unordered_set<std::string> continents;
	const char DELIM = ',';
	const signed int NULL_VERTEX = -1;
	Vertex find_country_vertex(Graph graph, std::string country) const;
	Graph graph;
public:
	Map();
	Graph get_graph() const;
	std::unordered_set<std::string> get_continents() const;
	void print_subgraph_continent(const Graph graph, std::string continent) const;
	void print_all_edges(const Graph graph) const;
	void get_all_vertices(const Graph graph) const;

	Vertex add_territory(const std::string territory);
	void add_continent_to_territory(Vertex territory, const std::string continent);
	void add_adjacency(Vertex territory, const std::string adj_territory);
	void add_continents(const std::string continent);

	Graph generate_map(std::vector<std::string>); // Temporary
	// bool generateMap(std::string fileName); // Generating map with the file
};
