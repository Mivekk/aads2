#include "Graph.h"

Graph::Graph(HashMap<String, int>* hashMap, int nodeCount)
	: m_hashMap(hashMap), m_nodeCount(nodeCount)
{
	adj.resize(m_nodeCount);
}

Graph::~Graph()
{
}

void Graph::addEdge(const String& from, const String& to, int weight)
{
	adj[m_hashMap->get(from)].push_back({ m_hashMap->get(to), weight });

	//std::cout << adj[m_hashMap->get(from)][adj[m_hashMap->get(from)].size() - 1].first 
	//	<< " " << adj[m_hashMap->get(from)][adj[m_hashMap->get(from)].size() - 1].second << "\n";
}
