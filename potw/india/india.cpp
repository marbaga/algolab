//Implementation by marcobaga
//This solution achieves 100 points

#include <iostream>
#include <vector>
#include <algorithm>
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
                boost::property <boost::edge_weight_t, long> > > > > graph; // new! weightmap corresponds to costs
typedef boost::graph_traits<graph>::edge_descriptor             edge_desc;
typedef boost::graph_traits<graph>::out_edge_iterator           out_edge_it; // Iterator

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
	int c,g,b,k,a; std::cin >> c >> g >> b >> k >> a;
	graph G(c+2);
	int source = c;
	int target = c+1;
	edge_adder adder(G);
	auto c_map = boost::get(boost::edge_capacity, G);
	auto r_map = boost::get(boost::edge_reverse, G);
	auto rc_map = boost::get(boost::edge_residual_capacity, G);

	edge_desc e;
	for(int i=0; i<g; ++i){
		int x,y,d,ele; std::cin >> x >> y >> d >> ele;
		e = adder.add_edge(x,y,ele,d);
	}
	e = adder.add_edge(a, target, std::numeric_limits<int>::max(), 0);
	e = adder.add_edge(source, k, std::numeric_limits<int>::max(), 0);

	int max = boost::push_relabel_max_flow(G, source, target);
	//std::cout << "max flow is : " << max << '\n';
	//std::cout << "budget is : " << b << '\n';
	int min = 0;
	while(min<max-1){
		int curr = min + (max-min)/2;
		//std::cout << "trying to send " << curr << " bags\n";
		c_map[e]=curr;

		boost::successive_shortest_path_nonnegative_weights(G, source, target);
		int cost = boost::find_flow_cost(G);

		if(cost <= b){
			min = curr;
		} else {
			max = curr;
		}
		//std::cout << "cost: " << cost << ", min = " << min << ", max: " << max << "\n";
	}

	c_map[e]=max;
	int flow = boost::push_relabel_max_flow(G, source, target);
	boost::successive_shortest_path_nonnegative_weights(G, source, target);
	int cost = boost::find_flow_cost(G);
	if(cost>b){
		c_map[e]=min;
		flow = boost::push_relabel_max_flow(G, source, target);
	}
	std::cout << flow << '\n';
	return;
}

int main(){
	std::ios_base::sync_with_stdio(false);
	int t; std::cin >> t;
	while(t-->0){
		testcase();
	}
	return 0;
}
