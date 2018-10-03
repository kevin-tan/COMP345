#include "stdafx.h"
#include "Map.h"


//Map class implementation
Map::Map()
{
	graph = Graph();
};

bool Map::generate_map(std::vector<std::string> map_info)
{
	using namespace boost;
	using namespace std;

	for (string info : map_info)
	{
		stringstream ss(info);
		string token;

		// Country with the out-edges
		Vertex main_vertex;

		// i == 0 is country name for node, i == 1 is continent for node
		int i = 0;
		bool vertexFound = true;
		while (getline(ss, token, DELIM))
		{
			if (i == 0)
			{
				main_vertex = find_country_vertex(token);
				if (main_vertex == NULL_VERTEX)
				{
					vertexFound = false;
					main_vertex = add_vertex(graph);
					graph[main_vertex].country = token;
				}
				i++;
			}
			else if (i == 1)
			{
				if (graph[main_vertex].continent.empty())
				{
					graph[main_vertex].continent = token;
				}
				else
				{
					if (vertexFound)
					{
						cout << "Country : " << graph[main_vertex].country << " already has continent " << graph[main_vertex].continent <<
							endl;
						graph = Graph(); // Return empty graph
						return false;
					}
				}
				i++;
			}
			else
			{
				// Find a vertext to see if it exists already
				Vertex v = find_country_vertex(token);
				if (v == NULL_VERTEX)
				{
					// Create new vertex
					v = add_vertex(graph);
					graph[v].country = token;
				}
				add_edge(main_vertex, v, graph);
			}
		}
	}

	return true;
}

Vertex Map::find_country_vertex(std::string const country)
{
	for (auto i = vertices(graph); i.first != i.second; ++i.first)
	{
		if (graph[*i.first].country.compare(country) == 0)
			return *i.first;
	}
	return NULL_VERTEX;
}

void Map::print_subgraph_continent(std::string const continent) const
{
	using namespace std;

	cout << "Printing subgraph for continent " << continent << endl;

	auto pairs = edges(graph);
	for (auto i = pairs.first; i != pairs.second; ++i)
	{
		if (graph[source(*i, graph)].continent.compare(continent) == 0)
		{
			cout << "Edge : Country=" << graph[source(*i, graph)].country <<
				" & Continent=" << graph[source(*i, graph)].continent << " --> Country=" << graph[target(*i, graph)].country <<
				" & Continent=" << graph[target(*i, graph)].continent << endl;
		}
	}
}

void Map::print_all_edges() const
{
	using namespace std;

	// Index map to get the index of the current vertex in the vector set
	IndexMap index = get(boost::vertex_index, graph);

	auto pairs = edges(graph);
	for (auto i = pairs.first; i != pairs.second; ++i)
	{
		cout << "Edge : index=" << index[source(*i, graph)] << " Country=" << graph[source(*i, graph)].country <<
			" & Continent=" << graph[source(*i, graph)].continent << " --> index=" << index[target(*i, graph)] << " Country="
			<< graph[target(*i, graph)].country << " & Continent=" << graph[target(*i, graph)].continent << endl;
	}
	cout << endl;
}

void Map::get_all_vertices() const
{
	// Index map to get the index of the current vertex in the vector set
	IndexMap index = get(boost::vertex_index, graph);

	std::cout << "vertices(g) = " << std::endl;
	for (auto pair = vertices(graph); pair.first != pair.second; ++pair.first)
		std::cout << index[*pair.first] << " : " << graph[*pair.first].country << " with continent " << graph[*pair.first].
			continent << std::endl;
	std::cout << std::endl;
}


Graph Map::get_generated_map() const
{
	return graph;
}
