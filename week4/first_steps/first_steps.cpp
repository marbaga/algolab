//Implementation by marcobaga
//This solution achieves 100 points

#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, boost::no_property, boost::property<boost::edge_weight_t, int>> weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor edge_descr;

int main(){

    std::ios_base::sync_with_stdio(false);
    int t;
    std::cin >> t;
    while(t>0){
		
		int n, m;
		std::cin >> n >> m;

		weighted_graph G(n);
		weight_map weights = boost::get(boost::edge_weight, G);

		edge_descr e;

		for(int i=0; i<m; ++i){
			int a,b,c;
			std::cin >>a>>b>>c;
			e = boost::add_edge(a, b, G).first;
			weights[e]=c;
		}

		std::vector<edge_descr> mst;
		std::vector<int> dist_map(n);
		boost::kruskal_minimum_spanning_tree(G, std::back_inserter(mst));
		boost::dijkstra_shortest_paths(G, 0, boost::distance_map(boost::make_iterator_property_map(dist_map.begin(), boost::get(boost::vertex_index, G))));
		
		int sum = 0;
		for(std::vector<edge_descr>::iterator it = mst.begin(); it != mst.end(); ++it){
			sum += weights[*it];
		}

		int dist = 0;
		for(int i : dist_map){
			if(i>dist){
				dist = i;
			}
		}

		std::cout << sum << ' ' << dist << std::endl;
		t--;
	}
    return 0;
}
