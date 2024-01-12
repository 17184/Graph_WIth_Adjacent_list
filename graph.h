#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <list>
#include <vector>

//impl graph with adj list
class Graph {
public:
	Graph(int);
	void addEdge(int, int);
	void transpose() ;//it has meaning only directed graph
	void print() const;
	void dfs(int);
	void dfsRecursive(int, std::vector<bool>&);
	void dfsIterative(int);
	void bfsIterative(int);
	void bfs(int);
	void bfsRec(int, std::vector<bool>&);
	int shortestDistenceInUnweightedGraph(int, int);
//	void printShortestPathInUnwightedGraph(int, int);
	std::vector<std::list<int>> allPaths(int, int);
	void dfsAllPaths (int,  int , std::list<int> &, std::vector<std::list<int>>& , std::vector<bool>& );
	int getComponentCount();
	void dfs_for_getComponent(int i, std::vector<bool>&);

private:
	int V;//count of vertex
	std::vector<std::list<int>> adjList;
};

#endif //GRAPH_H
