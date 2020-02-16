//Implementation by marcobaga
//This solution achieves 100 points

#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
boost::property<boost::edge_capacity_t, long,
boost::property<boost::edge_residual_capacity_t, long,
boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;
typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;

typedef struct brick_s{
	int begin, end, id, quantity;
} brick_t;

class edge_adder {
	graph &G;

	public:
	explicit edge_adder(graph &G) : G(G) {}
	void add_edge(int from, int to, long capacity) {
		auto c_map = boost::get(boost::edge_capacity, G);
		auto r_map = boost::get(boost::edge_reverse, G);
		const auto e = boost::add_edge(from, to, G).first;
		const auto rev_e = boost::add_edge(to, from, G).first;
		c_map[e] = capacity;
		c_map[rev_e] = 0; // reverse edge has no capacity!
		r_map[e] = rev_e;
		r_map[rev_e] = e;
	}
};

int main(){

	std::ios_base::sync_with_stdio(false);
	int t;
	std::cin >> t;
	while(t>0){
		int n, m, s;
		std::cin >> n >> m >> s;
		graph G(n+1);
		edge_adder adder(G);
		
		int temp;
		for (int i=0; i<s; ++i){
			std::cin >> temp;
			adder.add_edge(temp, n, 1);
		}

		int a, b;
		for(int i=0; i<m; ++i){
			std::cin >> a >> b;
			adder.add_edge(a, b, 1);
			adder.add_edge(b,a,1);
		}
/*
		std::cout << "edges(g) = ";
		boost::graph_traits<graph>::edge_iterator ei, ei_end;
		for (boost::tie(ei, ei_end) = boost::edges(G); ei != ei_end; ++ei){
			std::cout << "(" << int(boost::source(*ei, G)) << "," << int(boost::target(*ei, G)) << ") ";
		}
		std::cout << std::endl;
*/
		//std::cout << "Running max flow" << std::endl;
		long flow = boost::push_relabel_max_flow(G, 0, n);
		if(flow==s){
			std::cout << "yes" << std::endl;
		} else {
			std::cout << "no" << std::endl;
		}
		t--;
	}	
	return 0;
}
