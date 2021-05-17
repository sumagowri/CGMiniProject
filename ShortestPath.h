#include <stdio.h>
#include <limits.h>
#include <vector>

int minDistance(int dist[],
	bool sptSet[], int size){

	int min = INT_MAX, min_index;

	for (int v = 0; v < size; v++)
	if (sptSet[v] == false &&
		dist[v] <= min)
		min = dist[v], min_index = v;

	return min_index;
}

void printPath(int parent[], int j, std::vector<int> &ans){

	if (parent[j] == -1)
		return;

	printPath(parent, parent[j], ans);

	ans.push_back(j);
}

void printSolution(int dist[], int n,
	int parent[], int start, int end, std::vector<int> &ans)
{
	ans.push_back(start);
	printPath(parent, end, ans);
}

void dijkstra(std::vector<std::vector<int>> graph, int start, int end, std::vector<int> &ans)
{

	int size = graph.size();
	int dist[40];
	bool sptSet[40];

	int parent[40];

	parent[start] = -1;
	for (int i = 0; i < size; i++)
	{
		dist[i] = INT_MAX;
		sptSet[i] = false;
	}

	dist[start] = 0;

	for (int count = 0; count < size - 1; count++){
		int u = minDistance(dist, sptSet, size);

		sptSet[u] = true;

		for (int v = 0; v < size; v++)
		if (!sptSet[v] && graph[u][v] &&
			dist[u] + graph[u][v] < dist[v])
		{
			parent[v] = u;
			dist[v] = dist[u] + graph[u][v];
		}
	}

	printSolution(dist, size, parent, start, end, ans);
}

int dist(int x1, int y1, int x2, int y2){
	return ((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}

void calcPath(int node[40][2], int conn[40][40], int len, int start, int end, std::vector<int> &ans){

	 
	std::vector<std::vector<int>> graph(len, std::vector<int>(len, 0));
	
	for (int i = 0; i<len; i++){
		for (int j = i; j<40; j++){
			if (conn[i][j] == 0){
				graph[i][j] = 0;
				graph[j][i] = 0;
			}
			else{
				int d = dist(node[i][0], node[i][1], node[j][0], node[j][1]);
				graph[i][j] = d;
				graph[j][i] = d;
			}
		}
	}

	dijkstra(graph, start, end, ans);
	
}