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

	std::vector<int> AdjustmentVerticies(int vertex){
		if(m_graph.find(vertex)==m_graph.end()){
			std::cout << "Vertex does not exists\n";
		}else{
			auto v1 = m_graph[vertex];
			return v1;			
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

void BFS(Graph& G,int n);
void DFS(Graph& G,int n);

int main() {
	Graph G1;

	for (size_t i = 1; i <= 10; i++)
	{
		G1.addVertex(i);
	}
	

	G1.addEdge(1,2);
	G1.addEdge(1,5);
	G1.addEdge(1,9);

	G1.addEdge(2,3);
	G1.addEdge(2,4);
	
	G1.addEdge(4,3);

	G1.addEdge(5,7);
	G1.addEdge(5,8);
	G1.addEdge(5,6);

	G1.addEdge(8,10);
	
	G1.addEdge(9,10);

	BFS(G1,1);

	return 0;
}

void BFS(Graph& G,int n){
	std::queue<int> q;
	std::unordered_set<int> visted;

	q.push(n);

	while(!q.empty()){

		n = q.front();
		visted.insert(n);

		std::cout << "Odwiedzono: "<< n << "\n";

		for(auto nextVertex : G.AdjustmentVerticies(n)){
			if(visted.count(nextVertex)){
				continue;
			}
			q.push(nextVertex);
			visted.insert(nextVertex);	
			std::cout << "Dodadno: "<< nextVertex << "\n";
		}
		q.pop();
	}
}
