//Implementation by marcobaga
//This solution only achieves 50 points

#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/strong_components.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
boost::no_property,                         // no vertex property
boost::property<boost::edge_weight_t, double>  // interior edge weight property
> weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor vertex_desc;
int main(){

	std::ios_base::sync_with_stdio(false);
	int t;
	std::cin >> t;
	while(t>0){

		int n, m, k, T;
		std::cin >> n >> m >> k >> T;
		
		std::vector<int> tele(T);

		//weighted_graph G(n);
		weighted_graph inverted_G(n*2);
		//weight_map weights = boost::get(boost::edge_weight, G);
		weight_map inverted_weights = boost::get(boost::edge_weight, inverted_G);
		edge_desc e;

		//std::cout << "Acquired starting parameters" << std::endl;

		int temp;
		for(int i=0; i<T; ++i){
			std::cin >> temp;
			tele[i] = temp;
		}
		//std::cout << "Acquired teleporter locations" << std::endl;
		
		int u, v, c;
		for(int i=0; i<m; ++i){
			std::cin >> u >> v >> c;
			//e = boost::add_edge(u,v,G).first;
			//weights[e] = c;
			e = boost::add_edge(v,u,inverted_G).first;
			inverted_weights[e] = c;
		}


		//std::cout << "Acquired all edges" << std::endl;

		std::vector<int> scc_map(n*2);
		int nscc = boost::strong_components(inverted_G,
		boost::make_iterator_property_map(scc_map.begin(), boost::get(boost::vertex_index, inverted_G)));

		std::vector<std::vector<int>> components(nscc);

		for(int i : tele){
			components[scc_map[i]].push_back(i);
		}

		//std::cout << "added components" << std::endl;

		for(int i=0; i<nscc; ++i){
			if(components[i].size()>0){//auto new_vertex = boost::add_vertex(inverted_G);
				for (int j=0; j<components[i].size(); ++j){
					e = boost::add_edge(components[i][j], n+i, inverted_G).first;
					inverted_weights[e] = (float(components[i].size()-1))/2;
					e = boost::add_edge(i+n, components[i][j], inverted_G).first;
					inverted_weights[e] = (float(components[i].size()-1))/2;
				}
			}
		}

		//std::cout << "dijkstra" << std::endl;
		
		std::vector<float> dist_map(boost::num_vertices(inverted_G));
		boost::dijkstra_shortest_paths(inverted_G, n-1,
			boost::distance_map(boost::make_iterator_property_map(
			dist_map.begin(), boost::get(boost::vertex_index, inverted_G))));
		
		int min = dist_map[0];
		for(int i=1; i<k; ++i){
			//std::cout<< i << ' ' << dist_map[i]<<std::endl;
			if(dist_map[i]<min){
				min = dist_map[i];
			}
		}

		if(min>1000000){
			std::cout << "no" << std::endl;
		}else{
			std::cout << int(min) << std::endl;
		}

		t--;

	}	
	return 0;
}
