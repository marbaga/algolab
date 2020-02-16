//Implementation by marcobaga
//This solution achieves 100 points

#include <vector>
#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;
typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;

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

void testcase(){
	int n, m, s, d; std::cin >> n >> m >> s >> d;
	graph G(2*n+2);
	edge_adder adder(G);
	int source = 2*n;
	int target = 2*n+1;
	for(int i=0; i<m; ++i){
		int u, v; std::cin >> u >> v;
		adder.add_edge(u+n, v, 3*n);
	}
	for(int i=0; i<s; ++i){
		int j; std::cin >> j;
		adder.add_edge(source, j, 3*n);
	}
	for(int i=0; i<d; ++i){
		int j; std::cin >> j;
		adder.add_edge(j+n, target, 3*n);
	}
	for(int i=0; i<n; ++i){
		adder.add_edge(i, i+n, 1);
	}
	std::cout << boost::push_relabel_max_flow(G, source, target) << '\n';
	return;
}

int main(){
	std::ios_base::sync_with_stdio(false);
	int t; std::cin >> t;
	while(t-- > 0){
		testcase();
	}
	return 0;
}
