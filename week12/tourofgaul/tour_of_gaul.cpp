//Implementation by marcobaga
//This solution achieves 100 points

#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                boost::property <boost::edge_weight_t, long> > > > > graph;
typedef boost::graph_traits<graph>::edge_descriptor             edge_desc;
typedef boost::graph_traits<graph>::out_edge_iterator           out_edge_it;

class edge_adder {
 graph &G;
 public:
  explicit edge_adder(graph &G) : G(G) {}
  edge_desc add_edge(int from, int to, long capacity, long cost) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    auto w_map = boost::get(boost::edge_weight, G); // new!
    const edge_desc e = boost::add_edge(from, to, G).first;
    const edge_desc rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
    w_map[e] = cost;   // new assign cost
    w_map[rev_e] = -cost;   // new negative cost
    return e;
  }
};

void testcase(){
	int n,m; std::cin >> n >> m;
	graph G(n+2);
	int source = n;
	int target = n+1;
    	edge_adder adder(G);  
    	auto c_map = boost::get(boost::edge_capacity, G);
    	auto r_map = boost::get(boost::edge_reverse, G);
    	auto rc_map = boost::get(boost::edge_residual_capacity, G);
	auto w_map = boost::get(boost::edge_weight, G);

	std::vector<int> c(n-1);
	std::vector<std::vector<int>> bottleneck(n, std::vector<int>(n, 128));
	for(int i=0; i<n-1; ++i){
		std::cin >> c[i];
		adder.add_edge(source, i, c[i], 0);
		adder.add_edge(i,i+1,c[i],128);
		adder.add_edge(i+1, target, c[i], 0);
	}
	for(int i=0; i<n; ++i)
		for(int j=i+1; j<n; ++j)
			for(int k = i; k<j; k++)
				bottleneck[i][j] = std::min(bottleneck[i][j], c[k]);

	std::vector<std::vector<std::vector<int>>> food (n, std::vector<std::vector<int>>(n));

	for(int i=0; i<m; ++i){
		int a,b,d; std::cin >> a >> b >> d;
		food[a][b].push_back(d);
	}

	std::vector<edge_desc> edge_list;
	std::vector<int> significance;
	for(int i=0; i<n; ++i){
		for(int j=0; j<n; ++j){
			std::sort(food[i][j].begin(), food[i][j].end(), std::greater<int>());
			for(int k=0; k<std::min((int)bottleneck[i][j], (int)food[i][j].size()); ++k){
				edge_list.push_back(adder.add_edge(i,j,1,(j-i)*128-food[i][j][k]));
				significance.push_back(food[i][j][k]);
			}
		}
	}
	boost::successive_shortest_path_nonnegative_weights(G, source, target);
	int res = 0;
	for(int i=0; i<edge_list.size(); ++i)
		res += (1-rc_map[edge_list[i]])*(significance[i]);
	std::cout << res << '\n';
	return;
}

int main(){
	std::ios_base::sync_with_stdio(false);
	int t; std::cin >> t;
	while(t-- > 0)
		testcase();
	return 0;
}
