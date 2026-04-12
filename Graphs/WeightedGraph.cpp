#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>


class WeightedGraph{
public:
	WeightedGraph() {};

	void addVertex(int vertex) {
        m_graph[vertex] = {};
	}

	void addEdge(int vertex1, int vertex2, int weight) {
        m_graph[vertex1].push_back(std::make_pair(vertex2,weight));
        m_graph[vertex2].push_back(std::make_pair(vertex1,weight));
	}

	std::vector<int> AdjustmentVerticies(int vertex) const{

	}

	void showGraph() const{
        std::cout << std::string(10,'=') << "\n";
        for(const auto& vertex : m_graph){
            std::cout << vertex.first << " : ";
            for(auto& neighbor : vertex.second){
                std::cout << neighbor.first << "("<<neighbor.second<<") ";
            }
            std::cout<<"\n";
        }
        std::cout << std::string(10,'=') << "\n";
	}

	void removeVertex(int vertex) {
        m_graph.erase(vertex);

        for(auto& key : m_graph){
            auto& value = key.second;

            value.erase(std::remove_if(value.begin(),value.end(),
                [vertex](const std::pair<int,int>& edge) {
                    return edge.first == vertex;
                }),
            value.end());                
        }
    }

	void removeEdge(int vertex1,int vertex2) {

	}

private:
	std::map<int, std::vector<std::pair<int,int>>> m_graph;
};

int main() {
    // WeightedGraph G1;

    // G1.addVertex(1);
    // G1.addVertex(2);
    // G1.addVertex(3);

    // G1.addEdge(1,2,5);
    // G1.addEdge(1,3,1);
    // G1.addEdge(2,3,4);

    // G1.showGraph();
    // G1.removeVertex(1);
    // G1.showGraph();

    std::map<int, std::vector<std::pair<int,int>>> graph = {
        {1, {{1,2}, {1,5}, {1,8}}},
        {2, {{2,3}, {2,7}, {2,1}}},
        {3, {{3,4}, {3,2}, {3,6}}},
        {4, {{4,1}, {4,9}, {4,3}}}
    };

    int threshold = 5;

    for(auto& element : graph){
        auto& value = element.second;

        value.erase(std::remove_if(value.begin(),value.end(),
            [threshold](const std::pair<int,int>& pair){
                return pair.first > threshold && pair.second > threshold;
            }),
        value.end());
    }
  //training std::remove_if


	return 0;
}
