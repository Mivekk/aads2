#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <chrono>

#include "String.h"
#include "Vector.h"
#include "Pair.h"
#include "Graph.h"
#include "HashMap.h"
#include "Queue.h"
#include "PriorityQueue.h"

void readString(String& string) {
	char letter = (char)_getchar_nolock();
	while (letter != ' ' && letter != '\n') {
		string += letter;

		letter = (char)_getchar_nolock();
	}
}

void readInt(int& value) {
	String tmp;

	char letter = (char)_getchar_nolock();
	while (letter != ' ' && letter != '\n') {
		tmp += letter;

		letter = (char)_getchar_nolock();
	}

	value = 0;
	for (int i = 0; i < tmp.length; i++) {
		value += (tmp[tmp.length - i - 1] - '0') * pow(10, i);
	}
}

bool isLetter(int x, int y, const Vector<Vector<char>>& board) {
	if ((board[y][x] >= 'A' && board[y][x] <= 'Z') || (board[y][x] >= '0' && board[y][x] <= '9')) {
		return true;
	}

	return false;
}

bool isBorderChar(int x, int y, const Vector<Vector<char>>& board) {
	if (!isLetter(x, y, board)) {
		return false;
	}

	if (x - 1 == -1 || (x - 1 >= 0 && !isLetter(x - 1, y, board))) {
		return true;
	}
	else if (x + 1 == board[0].size() || (x + 1 < board[0].size() && !isLetter(x + 1, y, board))) {
		return true;
	}

	return false;
}

String getFullName(int x, int y, const Vector<Vector<char>>& board) {
	String res = "";

	// beggining of a name
	if (x + 1 < board[0].size() && isLetter(x + 1, y, board)) {
		int i = 0;
		while (isLetter(x + i, y, board) && x + i < board[0].size()) {
			res += board[y][x + i];

			i++;
		}
	}
	else {
		int i = 0;
		while (isLetter(x - i, y, board) && x - i >= 0) {
			res += board[y][x - i];

			i++;
		}

		// reverse
		for (int j = 0; j < res.length / 2; j++) {
			char tmp = res[j];
			res[j] = res[res.length - 1 - j];
			res[res.length - 1 - j] = tmp;
		}
	}

	return res;
}

String findCityName(int x, int y, const Vector<Vector<char>>& board) {
	if (isLetter(x, y, board)) {
		return "null";
	}

	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (x + i < 0 || x + i >= board[0].size() ||
				y + j < 0 || y + j >= board.size()) {
				continue;
			}

			if (isBorderChar(x + i, y + j, board)) {
				return getFullName(x + i, y + j, board);
			}
		}
	}

	return "null";
}

void bfs(Graph& graph, Pair<int, int> startPos, const String& startName,
	bool* vis, const Vector<Vector<char>>& board) {
	struct {
		int a, b;
	} directions[] = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };

	Queue<Pair<Pair<int, int>, int>> queue;

	Vector<int> visPos;

	vis[startPos.second * board[0].size() + startPos.first] = true;
	visPos.push_back(startPos.second * board[0].size() + startPos.first);

	queue.push({ { startPos.first, startPos.second }, 1 });

	while (queue.size()) {
		Pair<Pair<int, int>, int> curIdx = queue.front();
		queue.pop();

		int x = curIdx.first.first;
		int y = curIdx.first.second;

		for (auto dir : directions) {
			int newX = x + dir.a;
			int newY = y + dir.b;

			if (newX < 0 || newX >= board[0].size() ||
				newY < 0 || newY >= board.size()) {
				continue;
			}

			if (!vis[newY * board[0].size() + newX] && board[y + dir.b][x + dir.a] == '*') {
				vis[newY * board[0].size() + newX] = true;
				visPos.push_back(newY * board[0].size() + newX);

				graph.addEdge(startName, findCityName(x + dir.a, y + dir.b, board), curIdx.second);
			}
			else if (!vis[newY * board[0].size() + newX] && board[y + dir.b][x + dir.a] == '#') {
				vis[newY * board[0].size() + newX] = true;
				visPos.push_back(newY * board[0].size() + newX);

				queue.push({ { x + dir.a, y + dir.b }, curIdx.second + 1 });
			}
		}
	}

	for (int i = 0; i < visPos.size(); i++) {
		vis[visPos[i]] = false;
	}
}

void buildGraph(Graph& graph, const Vector<Pair<Pair<int, int>, String>>& nodes,
	const Vector<Vector<char>>& board) {

	std::size_t visSize = board.size() * board[0].size();

	bool* vis = new bool[visSize];
	memset(vis, false, visSize);

	for (int i = 0; i < nodes.size(); i++) {
		bfs(graph, { nodes[i].first.first, nodes[i].first.second },
			nodes[i].second, vis, board);
	}

	delete[] vis;
}

void dijkstra(Graph& graph, HashMap<String, int>* hashMap, Vector<Pair<Pair<int, int>, String>> nodes,
	const String& start, const String& end, int nodeCount, int type) {
	PriorityQueue<Pair<int, int>> pq;

	Vector<int> dist(nodeCount, INT_MAX);
	Vector<int> prev(nodeCount, -1);

	int startIndex = hashMap->get(start);
	int endIndex = hashMap->get(end);
	dist[startIndex] = 0;

	pq.push({ dist[startIndex], startIndex });

	while (pq.size()) {
		int u = pq.top().second;
		pq.pop();

		if (u == endIndex) {
			break;
		}

		for (int i = 0; i < graph.adj[u].size(); i++) {
			int vIndex = graph.adj[u][i].first;
			int weight = graph.adj[u][i].second;

			if (dist[vIndex] > dist[u] + weight) {
				dist[vIndex] = dist[u] + weight;
				prev[vIndex] = u;

				pq.push({ dist[vIndex], vIndex });
			}
		}
	}

	std::cout << dist[endIndex] << " ";

	if (type == 1) {
		Vector<String> path;

		while (prev[endIndex] >= 0 && prev[endIndex] != startIndex) {
			path.push_back(nodes[prev[endIndex]].second);

			endIndex = prev[endIndex];
		}

		for (int i = path.size() - 1; i >= 0; i--) {
			std::cout << path[i] << " ";
		}
	}

	std::cout << "\n";
}

void read() {
	int w, h;
	readInt(w);
	readInt(h);

	Vector<Vector<char>> board(h, Vector<char>(w));

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			board[i][j] = _getchar_nolock();
		}
		_getchar_nolock();
	}

	HashMap<String, int>* hashMap = new HashMap<String, int>;
	Vector<Pair<Pair<int, int>, String>> nodes;

	String cityName;
	int nodeCount = 0;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (board[i][j] == '*') {
				cityName = findCityName(j, i, board);

				nodes.push_back({ { j, i }, cityName });
				hashMap->set(cityName, nodeCount);

				nodeCount++;
			}
		}
	}

	Graph graph(hashMap, nodeCount);
	buildGraph(graph, nodes, board);

	int k, time = 0;
	String a, b;
	readInt(k);
	for (int i = 0; i < k; i++) {
		a.length = 0;
		b.length = 0;

		readString(a);
		readString(b);
		readInt(time);

		graph.addEdge(a, b, time);
	}

	int q, type = 0;
	readInt(q);
	for (int i = 0; i < q; i++) {
		a.length = 0;
		b.length = 0;

		readString(a);
		readString(b);
		readInt(type);


		dijkstra(graph, hashMap, nodes, a, b, nodeCount, type);
	}

	delete hashMap;
}

int main() {
	read();

	return 0;
}