//Implementation by marcobaga
//This solution achieves 100 points

#include <vector>
#include <iostream>
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
	int z,j; std::cin >> z >> j;
	graph G(z+j+2);
	edge_adder adder(G);
	int source = z+j;
	int target = z+j+1;
	for(int i=0; i<z; ++i){
		int price; std::cin >> price;
		adder.add_edge(j+i, target, price);
	}
	int total_reward = 0;
	for(int i=0; i<j; ++i){
		int reward; std::cin >> reward;
		adder.add_edge(source, i, reward);
		total_reward += reward;
	}

	for(int i=0; i<j; ++i){
		int n; std::cin >> n;
		for(int k=0; k<n; ++k){
			int tick; std::cin >> tick;
			adder.add_edge(i, j+tick, std::numeric_limits<int>::max());
		}
	}
	std::cout << total_reward - boost::push_relabel_max_flow(G, source, target) << '\n';
	
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
