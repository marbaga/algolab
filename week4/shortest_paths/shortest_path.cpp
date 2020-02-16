//Implementation by marcobaga
//This solution achieves 100 points

#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <limits>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property, boost::property<boost::edge_weight_t, int>> weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor edge_descr;
typedef boost::graph_traits<weighted_graph>::edge_iterator edge_it;

int main(){

    std::ios_base::sync_with_stdio(false);
	
	int n, m, q;
	std::cin >> n >> m >> q;

	for(int i=0; i<n; ++i){
		int lat, lon;
		std::cin >> lat >> lon;
	}

	weighted_graph G(n);
	edge_descr ed;
	weight_map weights = boost::get(boost::edge_weight, G);

	for(int i=0; i<m; ++i){
		int a, b, c;
		std::cin >> a >> b >> c;
		ed = boost::add_edge(a, b, G).first;
		weights[ed] = c;
	}

	while(q>0){
		int s, t;
		std::cin >> s >> t;

		std::vector<int> dist_map(n);
		boost::dijkstra_shortest_paths(G, s, boost::distance_map(boost::make_iterator_property_map(dist_map.begin(), boost::get(boost::vertex_index, G))));

		int sol = dist_map[t];

		if(sol < 2147483647){
			std::cout << sol << std::endl;
		} else {
			std::cout << "unreachable" << std::endl;
		}
		q--;
	}
    return 0;
}
