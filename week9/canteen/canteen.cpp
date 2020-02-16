//Implementation by marcobaga
//This solution achieves 100 points

#include <vector>
#include <algorithm>
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
typedef boost::graph_traits<graph>::edge_iterator           	edge_it;

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
	int n; std::cin >> n;
	graph G(n+2);
	edge_adder adder(G);
	auto c_map = boost::get(boost::edge_capacity, G);
	auto r_map = boost::get(boost::edge_reverse, G);
	auto rc_map = boost::get(boost::edge_residual_capacity, G);
    	auto w_map = boost::get(boost::edge_weight, G);
	int src = n;
	int trg = n + 1;
	int tot_meals_to_serve = 0;
	std::vector<edge_desc> edge_list;
	for(int i=0; i<n; ++i){
		int a,c; std::cin >> a >> c;
		edge_list.push_back(adder.add_edge(src,i,a,c));
	}
	for(int i=0; i<n; ++i){
		int s,p; std::cin >> s >> p;
		edge_list.push_back(adder.add_edge(i, trg, s, 20-p));
		tot_meals_to_serve+=s;
	}
	for(int i=0; i<n-1; ++i){
		int v,e; std::cin >> v >> e;
		edge_list.push_back(adder.add_edge(i, i+1, v,e));
	}

	boost::successive_shortest_path_nonnegative_weights(G, src, trg);
	int income = 0;

    	int flow = 0;
    	out_edge_it e, eend;
    	for(boost::tie(e, eend) = boost::out_edges(boost::vertex(src,G), G); e != eend; ++e)
		flow += c_map[*e] - rc_map[*e];
	for (edge_desc ed : edge_list)
		income += (c_map[ed] - rc_map[ed])*(w_map[ed]);
	income = 20*flow - income;

	if(flow == tot_meals_to_serve)
		std::cout << "possible " << flow << ' ' << income << '\n';
	else
		std::cout << "impossible " << flow << ' ' << income << '\n';
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