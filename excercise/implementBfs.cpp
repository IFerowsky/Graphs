/*
=============================================
Write a program that determines the shortest path between two vertices in a graph (we need to find the minimum number of vertices that must be visited to get from vertex A to vertex B).

Input

In the first line, two numbers n and p are given, representing respectively the number of vertices in the graph and the number of connections between them (n < 1001, p < n · n).

In the next p lines, each line contains two distinct numbers a and b, defining a connection between these vertices.

Then two numbers A and B are given, where A, B ∈ [1..n], representing the starting and ending vertex.

Output

A single number representing the minimum number of steps from vertex A to B, or the text "No connection" if no path exists.

Example

input:                          Output:
10 11                           2
1 2
2 3
3 4
2 4
1 5
1 9
9 10
5 6
5 7
5 8
8 10
1 7
=============================================
*/
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <unordered_set>

class Graph{
public:
	Graph() {};

	void addVertex(int vertex) {
		if (m_graph.find(vertex) != m_graph.end()) {
			std::cout << "Vertex already exists\n";
			return;
		}
		m_graph[vertex] = {};
	}

	void addEdge(int vertex1, int vertex2) {
		
		if (m_graph.find(vertex1) == m_graph.end() || m_graph.find(vertex2) == m_graph.end()) {
			std::cout << "Invalid vertex\n";
			return;
		}

		if (vertex1 == vertex2) {
			m_graph[vertex1].push_back(vertex2);
			return;
		}

		auto& v1 = m_graph[vertex1];
		if (std::find(v1.begin(), v1.end(), vertex2) != v1.end()) {
			std::cout << "Edge already exists\n";
			return;
		}

		m_graph[vertex1].push_back(vertex2);
		m_graph[vertex2].push_back(vertex1);
	}

	std::vector<int> AdjustmentVerticies(int vertex) const{
		if(m_graph.find(vertex)==m_graph.end()){
			std::cout << "Vertex does not exists\n";
			return {};
		}else{
			return m_graph.at(vertex);			
		}
    }

	void showGraph() const{
		std::cout << std::string(10,'=') << "\n";
		for (const auto& element : m_graph) {
			std::cout << element.first << " : ";
			
			for (const auto& connectedTo : element.second) {
				std::cout << connectedTo << " ";
			}

			std::cout << "\n";
		}
		std::cout << std::string(10, '=') << "\n";
	}

	void removeVertex(int vertex) {
		if (m_graph.find(vertex) == m_graph.end()) {
			
			std::cout << "Invalid vertex\n";
			return;
		}
		
		m_graph.erase(vertex);

		for (auto& element : m_graph) {

			auto& value = element.second;

			value.erase(std::remove(value.begin(),value.end(),vertex),value.end());
		}
	}

	void removeEdge(int vertex1,int vertex2) {
		if (m_graph.find(vertex1) == m_graph.end() || m_graph.find(vertex2) == m_graph.end()) {
			std::cout << "Invalid vertex\n";
			return;
		}
		auto& v1 = m_graph[vertex1];
		auto& v2 = m_graph[vertex2];

		v1.erase(std::remove(v1.begin(), v1.end(), vertex2), v1.end());
		v2.erase(std::remove(v2.begin(), v2.end(), vertex1), v2.end());
	}

private:
	std::map<int, std::vector<int>> m_graph;
};

void BFS(Graph& G,int start,int end);

int main() {
	Graph G1;

    int n=0,p=0,a=0,b=0;

    std::cin >> n >> p;
    for (int i = 1; i <= n; i++)
    {
        G1.addVertex(i);
    }
    for (int i = 0; i < p; i++)
    {
        std::cin >> a >> b;
        G1.addEdge(a,b);
    }
    
    std::cin >> a >> b;
    BFS(G1,a,b);


	return 0;
}

void BFS(Graph& G,int start,int end){
	std::queue<int> q;
	std::map<int, int> distance;

	q.push(start);
    distance[start] = 0;

	while(!q.empty()){

		int n = q.front();
        q.pop();

        if(n==end){
            std::cout << distance[n];
            return;        
        }

		for(auto nextVertex : G.AdjustmentVerticies(n)){
			if(distance.count(nextVertex)){
				continue;
			}

            distance[nextVertex] = distance[n] + 1;
            q.push(nextVertex);
		}
	}
    std::cout << "No connection\n";
}
