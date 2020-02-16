//Implementation by marcobaga
//This solution achieves 100 points

#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/max_cardinality_matching.hpp>
#include <limits>
#include <string>
#include <map>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph;
typedef boost::graph_traits<graph>::edge_descriptor edge_descr;
typedef boost::graph_traits<graph>::vertex_descriptor vertex_desc;
typedef boost::graph_traits<graph>::edge_iterator edge_it;

int main(){

    std::ios_base::sync_with_stdio(false);
	
	int t;
	std::cin >> t;
	while(t>0){

		int n, c, f;
		std::cin >> n >> c >> f;

		std::map<std::string, std::vector<int>> m;

		for(int i=0; i<n; ++i){
			for(int j=0; j<c; ++j){

				std::string s;
				std::cin >> s;
				
				if(m.find(s)==m.end()){
					m.insert(make_pair(s, std::vector<int>()));
					m[s].push_back(i);
				} else {
					m[s].push_back(i);
				}
			}
		}

		int arr[400][400] = {0};

		for (auto it=m.begin(); it!=m.end(); ++it){
			std::vector<int> v = it->second;
			for (auto i=v.begin(); i!=v.end(); ++i){
				for(auto j=i+1; j<v.end(); ++j){
					arr[*i][*j]++;
				}
			}
		}

		graph G(n);

		for(int i=0; i<n; ++i){
			for(int j=i+1; j<n; ++j){
				if(arr[i][j]>f){
					boost::add_edge(i, j, G);
				}
			}
		}


		std::vector<vertex_desc> mate_map(n); // exterior property map
		const vertex_desc NULL_VERTEX = boost::graph_traits<graph>::null_vertex();
		boost::edmonds_maximum_cardinality_matching(G,
boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));
		int matching_size = boost::matching_size(G,
boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));

		if(matching_size >= n/2){
			std::cout << "not optimal" << std::endl;
		} else {
			std::cout << "optimal" << std::endl;
		}

//for (int i = 0; i < n; ++i) {
// mate_map[i] != NULL_VERTEX: the vertex is matched
// i < mate_map[i]: visit each edge in the matching only once
//if (mate_map[i] != NULL_VERTEX && i < mate_map[i]) std::cout << i << " " << mate_map[i] << "\n";

		t--;
	}
	return 0;
}
