//Implementation by marcobaga
//This solution achieves 100 points

#include <iostream>
#include <vector>
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
	//std::cout << "Adding edge from " << from << " to " << to << " with capacity " << capacity << '\n';
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
	int n,m; std::cin >> n >> m;
	std::vector<int> a(m);
	std::vector<int> b(m);
	std::vector<int> c(m);
	for(int i=0; i<m; ++i){
		std::cin >> a[i] >> b[i] >> c[i];
	}
	int tot_score = 0;
	std::vector<int> score(n);
	for(int i=0; i<n; ++i){
		std::cin >> score[i];
		tot_score +=score[i];
	}

	if(tot_score!=m){
		std::cout << "no" << '\n';
		return;
	}

	graph G(n+m);
	edge_adder adder(G);
	const vertex_desc v_source = boost::add_vertex(G);
	const vertex_desc v_target = boost::add_vertex(G);

	for(int i=0; i<m; ++i){//Implementation by marcobaga
//This solution achieves 100 points


		adder.add_edge(v_source, i, 1);
		if(c[i]!=1)
			adder.add_edge(i, b[i]+m, 1);
		if (c[i]!=2)
			adder.add_edge(i, a[i]+m, 1);
	}


	for(int i=0; i<n; ++i){
		if(score[i]>=0){
			adder.add_edge(m+i, v_target, score[i]);
		} else if (score[i]<0){
			std::cout << "no" << '\n';
			return;
		}
	}


	long flow = boost::push_relabel_max_flow(G, v_source, v_target);
	if(flow == tot_score)
		std::cout << "yes" << '\n';
	else 
		std::cout << "no" << '\n';

	return;
}

int main (){
	std::ios_base::sync_with_stdio(false);
	int t; std::cin >> t;
	while(t>0){
		testcase();
		t--;
	}
	return 0;
}
