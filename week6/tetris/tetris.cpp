//Implementation by marcobaga
//This solution achieves 100 points

#include <iostream>
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
	int w, n; std::cin >> w >> n;
	graph G(2*(w+1)+2);
	edge_adder adder(G);
	int source = 2*w+2;
	int target = 2*w+3;
	std::vector<std::vector<int>> block(w+1, std::vector<int>(w+1, 0));
	for(int i=0; i<n; ++i){
		int a,b; std::cin >> a >> b;
		if(a>b){ std::swap(a,b); }
		block[a][b]++;
	}
	adder.add_edge(source, 0, std::numeric_limits<int>::max());
	adder.add_edge(w+1+w, target, std::numeric_limits<int>::max());
	for(int i=0; i<w+1; ++i){
		if(i==0 || i==w){
			adder.add_edge(i, w+1+i, std::numeric_limits<int>::max());
		} else {
			adder.add_edge(i, w+1+i, 1);
		}
		for(int j=0; j<w+1; ++j){
			if(block[i][j]>0){
				adder.add_edge(w+1+i, j, block[i][j]);
			}
		}
	}

	std::cout <<   boost::push_relabel_max_flow(G, source, target) << '\n';
	return;
}

int main(){
	std::ios_base::sync_with_stdio(false);
	int t; std::cin >> t;
	while(t-- >0){
		testcase();
	}
	return 0;
}
