#pragma once
#include "Vector.h"
#include "String.h"
#include "HashMap.h"
#include "Pair.h"

class Graph
{
public:
	Graph(HashMap<String, int>* hashMap, int nodeCount);
	~Graph();

	void addEdge(const String& from, const String& to, int weight);

	Vector<Vector<Pair<int, int>>> adj;

private:
	HashMap<String, int>* m_hashMap;

	int m_nodeCount;
};

