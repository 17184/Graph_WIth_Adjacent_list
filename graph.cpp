#include <iostream>
#include <stack>
#include <queue>
#include "graph.h"

Graph::Graph(int v) : V(v), adjList(v) {};

void Graph::addEdge(int u, int v) {
	adjList[u].push_back(v);
//	adjList[v].push_back(u);//for undirected graph
}

void Graph::transpose()  {
	Graph newGraph(V);
	for(int i = 0; i < V; ++i) {
		for(const auto& neight : adjList[i]) {
			newGraph.addEdge(neight, i);
		}//uxutyunnery poxuma 
	}
	adjList = newGraph.adjList;//skzbnakany poxum enq
}
void Graph::print() const {
	for(int i = 0; i < V; ++i) {
		std::cout << "Vertex " << i  << "-> ";
		for(const auto & neight : adjList[i]) {
			std::cout << neight << " ";
		}
		std::cout << std::endl;
	}
}

void Graph:: dfs(int start) {
	std::vector<bool> visited (V, false);
	dfsRecursive(start, visited);
}
void Graph::dfsRecursive(int start, std::vector<bool>& visit) {
	visit[start] = true;
	std::cout << start << " " ;

	for(const auto& neight : adjList[start]) {
		if(!visit[neight]) {
			dfsRecursive(neight, visit);
		}
	}
}

void Graph::dfsIterative(int startVertex) {
	std::vector<bool> visited(V, false);
	std::stack<int> s;
	s.push(startVertex);

	while(!s.empty()) {
		int currVertex = s.top();
		s.pop();
		if(!visited[currVertex]) {

			std::cout << currVertex << " ";
			visited[currVertex] = true;
		}
			for(const auto& neight : adjList[currVertex]) {
				if(!visited[neight]) {
					s.push(neight);
				}
			}
		
	}	 
}

void Graph::bfsIterative(int startVertex) {
	std::queue<int> q;
	std::vector<bool> visited(V, false);
	q.push(startVertex);

	while(!q.empty()) {
		int currVertex = q.front();
		q.pop();
		if(!visited[currVertex]) {
			visited[currVertex] = true;
			std::cout << currVertex << " ";
		}
		for(const auto & i : adjList[currVertex]) {
			if(!visited[i]) {
				q.push(i);
			}
		}
	}
}

void Graph::bfs(int startVertex) {
	std::vector<bool> visited(V, false);
	bfsRec(startVertex, visited);
}

void Graph::bfsRec(int start, std::vector<bool>& visited) {
	visited[start] = true;
	std::cout << start << " ";
	for(const auto& i : adjList[start]) {
		if(!visited[i]) {
			bfsRec(i, visited);
		}
	}
}
//if i dont print that path so it not needed parent

int Graph::shortestDistenceInUnweightedGraph(int u, int v) {
		//with bfs we do it
		std::queue<int> q;
		std::vector<bool> visited(V, false);
		std::vector<int> dist (V, 0);
		visited[u]  = true;
		q.push(u);
		while(!q.empty()) {
			int curr = q.front();
			q.pop();
			for(const auto& neight : adjList[curr]) {
				if(!visited[neight]) {
					visited[neight] = true;
					dist[neight] += dist[curr] + 1;
					q.push(neight);

						if(neight == v) {
							return dist[neight];
						}
					}
				}
		}
	return -1;
}
void Graph::dfsAllPaths(int curr, int end, std::list<int>& path, std::vector<std::list<int>>& allPaths, std::vector<bool>& visited) {
	path.push_back(curr);
	visited[curr] = true;
	if(curr == end) {
		allPaths.push_back(path);
	} else {
		for(const auto & neight : adjList[curr]) {
			if(!visited[neight]) {
				dfsAllPaths(neight, end, path, allPaths, visited);
			}
		}
	}
	//backtrack
	path.pop_back();
	visited[curr] = false;
}
std::vector<std::list<int>> Graph::allPaths(int u, int v) {
	std::list<int> path;
	std::vector<std::list<int>> allPaths;
	std::vector<bool> visited(V, false);
	dfsAllPaths(u, v, path, allPaths, visited);
	return allPaths;
}

void Graph::dfs_for_getComponent(int curr, std::vector<bool>& visited) {
    visited[curr] = true;

    for (const auto& neighbor : adjList[curr]) {
        if (!visited[neighbor]) {
            dfs_for_getComponent(neighbor, visited);
        }
    }
}
int Graph::getComponentCount() {
	std::vector<bool> visited(V, false);
	int count{};
	for(int i = 0; i < V; ++i) {
		if(!visited[i]) {
			dfs_for_getComponent(i, visited);
			count++;
		}
	} 
	return count;
}
int main() {  
    Graph g(5);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 0);
    g.addEdge(2, 3);

    std::cout << "Original Graph:" << std::endl;
    g.print();
/*
	g.transpose();
    std::cout << "\nTransposed Graph:" << std::endl;
    g.print();
*/
	std::cout << "Dfs startting from vertex of 0 - " ;
	g.dfs(0);
	
	std::cout << "\nDfs iterative startting from vertex of 0 - " ;
	g.dfsIterative(0); 
	
	std::cout << "\nBfs result from vertex of 1 - ";
	g.bfsIterative(1);
	
	std::cout <<"\nBfsRec result from vertex of 1 - ";
	g.bfs(1);

	std::cout << "\nFind shortest path from 1 to 4 " ;
	int res = g.shortestDistenceInUnweightedGraph(1, 4);
	if(res != -1) {
		std::cout << res << std::endl; 
	}
	


	std::vector<std::list<int>> resAllPath = g.allPaths(1, 4);
	if(!resAllPath.empty()) {
		std::cout << "All poosible pathd from " << 1 << " to " << 4 << " iis " ;
		for(const auto & neight : resAllPath) {
				for(int vertex : neight) {
					std::cout << vertex << " ";	
			}
		std::cout << std::endl;
		}
	} else {
			std::cout << "there is not possible paths \n";	
	}
	Graph	graph(5);
	graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(3, 4);
	std::cout << "Component count is - " << graph.getComponentCount();
	return 0;
}

