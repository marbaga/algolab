//Implementation by marcobaga
//This solution achieves 100 points

#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <limits>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, boost::no_property, boost::property<boost::edge_weight_t, int>> weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor edge_descr;
typedef boost::graph_traits<weighted_graph>::edge_iterator edge_it;

int main(){

    std::ios_base::sync_with_stdio(false);
    int t;
    std::cin >> t;
    while(t>0){
		
		int n, e, s, a, b;
		std::cin >> n >> e >> s >> a >> b;

		std::array<std::vector<std::tuple<int, int, int>>, 20> species_weight;

		edge_descr ed;

		for(int i=0; i<e; ++i){
			int t1, t2;
			std::cin >> t1 >> t2;
			int temp;
			for(int j=0; j<s; ++j){
				std::cin >> temp;
				species_weight[j].push_back(std::make_tuple(t1, t2, temp));
			}
		}

		int trash;
		for(int i=0; i<s; ++i){
			std::cin >> trash;
		}

		weighted_graph G(n);
		weight_map weights = boost::get(boost::edge_weight, G);

		for(int i=0; i<s; ++i){
			weighted_graph GS(n);
			weight_map weightsS = boost::get(boost::edge_weight, GS);
			for(auto j=species_weight[i].begin(); j!=species_weight[i].end(); ++j){
				int t1, t2, w;
    			std::tie(t1, t2, w) = *j;
				ed = boost::add_edge(t1, t2, GS).first;
				weightsS[ed] = w;
			}

			//std::cout << "Building MST for species " << i << std::endl;

			std::vector<edge_descr> mst;
			boost::kruskal_minimum_spanning_tree(GS, std::back_inserter(mst));
			for (std::vector<edge_descr>::iterator it = mst.begin(); it != mst.end(); ++it) {
				//std::cout << "Analyzing edge from " << boost::source(*it, GS) << " to " << boost::target(*it, GS) << std::endl;
				//std::cout << "Species graph weight: " << weightsS[*it] << std::endl;

				//std::cout << "Does this vertex exist in the global graph" << std::endl;
				//std::cout << boost::edge(boost::source(*it, GS), boost::target(*it, GS), G).second << std::endl;

				if(boost::edge(boost::source(*it, GS), boost::target(*it, GS), G).second){
					ed = boost::edge(boost::source(*it, GS), boost::target(*it, GS), G).first;
					if(weightsS[*it]<weights[ed]){
						weights[ed] = weightsS[*it];
					}
				}else{
					ed = boost::add_edge(boost::source(*it, GS), boost::target(*it, GS), G).first;
					weights[ed] = weightsS[*it];
				}
			}
		}
/*
		edge_it e_beg, e_end;
		for (boost::tie(e_beg, e_end) = boost::edges(G); e_beg != e_end; ++e_beg) {
			std::cout << boost::source(*e_beg, G) << " " << boost::target(*e_beg, G) << " " <<  weights[*e_beg] << "\n";
		}
*/
		std::vector<int> dist_map(n);
		boost::dijkstra_shortest_paths(G, a, boost::distance_map(boost::make_iterator_property_map(dist_map.begin(), boost::get(boost::vertex_index, G))));

		std::cout << dist_map[b] <<std::endl;
		t--;
	}
    return 0;
}
