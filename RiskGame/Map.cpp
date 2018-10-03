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
						cout << "Country : " << graph[main_vertex].country << " already has continent " << graph[main_vertex].continent << endl;
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

Vertex Map::find_country_vertex(std::string country)
{
	for (auto i = vertices(graph); i.first != i.second; ++i.first)
	{
		if (graph[*i.first].country.compare(country) == 0)
			return *i.first;
	}
	return NULL_VERTEX;
}


void Map::printAllEdges()
{
	auto pairs = edges(graph);
	for (auto i = pairs.first; i != pairs.second; ++i)
	{
		std::cout << "Edge : Country=" << graph[source(*i, graph)].country << " & Continent=" << graph[source(*i, graph)].continent << " --> Country="
			<< graph[target(*i, graph)].country << " & Continent=" << graph[target(*i, graph)].continent << std::endl;
	}
}

void Map::getAllVertices()
{
	typedef boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;
	typedef boost::graph_traits<Graph>::vertex_iterator vertex_iter;

	// Index map to get the index of the current vertex in the vector set
	IndexMap index = get(boost::vertex_index, graph);
	// The vertex iterator pair
	std::pair<vertex_iter, vertex_iter> vp;

	std::cout << "vertices(g) = " << std::endl;
	for (vp = vertices(graph); vp.first != vp.second; ++vp.first)
		std::cout << index[*vp.first] << " : " << graph[*vp.first].country << " with continent " << graph[*vp.first].continent
			<< std::endl;
	std::cout << std::endl;
}


Graph Map::get_generated_map() const
{
	return graph;
}
