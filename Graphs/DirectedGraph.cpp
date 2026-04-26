#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

class DirectedGraph{
public:
	DirectedGraph() {};

	void addVertex(int vertex) {
		if (m_graph.find(vertex) != m_graph.end()) {
			std::cerr << "Vertex already exists\n";
			return;
		}
		m_graph[vertex] = {};
	}

	void addEdge(int vertex1, int vertex2) {
		
		if (m_graph.find(vertex1) == m_graph.end() || m_graph.find(vertex2) == m_graph.end()) {
			std::cerr << "Invalid vertex\n";
			return;
		}

		auto& v1 = m_graph[vertex1];
		if (std::find(v1.begin(), v1.end(), vertex2) != v1.end()) {
			std::cerr << "Edge already exists\n";
			return;
		}

		m_graph[vertex1].push_back(vertex2);
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
			std::cerr << "Invalid vertex\n";
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
			std::cerr << "Invalid vertex\n";
			return;
		}
		
        auto& v1 = m_graph[vertex1];

        if (std::find(v1.begin(), v1.end(), vertex2) == v1.end()) {
            std::cerr << "Edge does not exist\n";
            return;
        }

		v1.erase(std::remove(v1.begin(), v1.end(), vertex2), v1.end());
	}

	std::vector<int> getNeighbours(int vertex) const{
		if(m_graph.find(vertex)==m_graph.end()){
			std::cerr << "Vertex does not exists\n";
			return {};
		}else{
			return m_graph.at(vertex);			
		}
	}

    std::vector<int> allVertices() const{
        std::vector<int> ans;
        for(auto element : m_graph){
            ans.push_back(element.first);
        }
        return ans;
    }

    std::map<int, int> enteringEdges() const{
        std::map<int, int> ans;

        for(auto element : allVertices()){
            ans[element] = 0;
        }

        for(auto element : m_graph){

            for( auto vertex : element.second){
                ans[vertex]++;
            }
        }
        return ans;
    }

private:
	std::map<int, std::vector<int>> m_graph;
};

int main() {
	DirectedGraph G1;

	G1.addVertex(1);
	G1.addVertex(2);
	G1.addVertex(3);

	G1.addEdge(1,2);
	G1.addEdge(1,3);
	G1.addEdge(2,3);

	G1.showGraph();

	return 0;
}
