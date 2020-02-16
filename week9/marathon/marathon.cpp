//Implementation by marcobaga
//This solution achieves 100 points

#include <vector>
#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;
typedef traits::vertex_descriptor vertex_desc2;
typedef traits::edge_descriptor edge_desc2;

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
	int n,m,s,f; std::cin >> n >> m >> s >> f;
	std::vector<std::tuple<int,int,int,int>> input;

	weighted_graph G(n);
  	weight_map weights = boost::get(boost::edge_weight, G);
	edge_desc e;

	for(int i=0; i<m; ++i){
		int a,b,c,d; std::cin>>a>>b>>c>>d;
		e = boost::add_edge(a,b,G).first; weights[e]=d;
		e = boost::add_edge(b,a,G).first; weights[e]=d;
		input.push_back(std::make_tuple(a,b,c,d));
	}

	std::vector<int> dist_s(n);
  	boost::dijkstra_shortest_paths(G, s, boost::distance_map(boost::make_iterator_property_map(dist_s.begin(), boost::get(boost::vertex_index, G))));
	std::vector<int> dist_f(n);
  	boost::dijkstra_shortest_paths(G, f, boost::distance_map(boost::make_iterator_property_map(dist_f.begin(), boost::get(boost::vertex_index, G))));

	graph G2(n);
	edge_adder adder(G2);
	for(std::tuple<int,int,int,int> t : input){
		int a = std::get<0>(t);
		int b = std::get<1>(t);
		if(dist_f[a]>dist_f[b]){
			if(dist_f[a]==dist_f[b]+std::get<3>(t)){
				  adder.add_edge(a, b, std::get<2>(t));
			}
		} else if (dist_f[a]<dist_f[b]){
			if(dist_f[b]==dist_f[a]+std::get<3>(t)){
				  adder.add_edge(b, a, std::get<2>(t));
			}
		//} else {
			//std::cout << "ERROR\n";
		}
	}

	long flow = boost::push_relabel_max_flow(G2, s, f);
	std::cout << flow << '\n';
	return;
}

int main(){
	std::ios_base::sync_with_stdio(false);
	int t; std::cin >> t;
	while(t-- > 0)
		testcase();
	return 0;
}
