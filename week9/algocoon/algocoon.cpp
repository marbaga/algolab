//Implementation by marcobaga
//This solution achieves 100 points

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/tuple/tuple.hpp>

typedef	boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
	boost::property<boost::edge_capacity_t, long,
		boost::property<boost::edge_residual_capacity_t, long,
			boost::property<boost::edge_reverse_t, traits::edge_descriptor> > > >	graph;
typedef	boost::graph_traits<graph>::edge_descriptor			edge_desc;
typedef	boost::graph_traits<graph>::out_edge_iterator			out_edge_it;

class edge_adder {
 graph &G;
 public:
  explicit edge_adder(graph &G) : G(G) {}
  void add_edge(int from, int to, long capacity) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    const edge_desc e = boost::add_edge(from, to, G).first;
    const edge_desc rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
  }
};

void testcase(){
	int n, m; std::cin >> n >> m;
	graph G(n);
	edge_adder adder(G);
	auto rc_map = boost::get(boost::edge_residual_capacity, G);

	for(int i=0; i<m; ++i){
		int a,b,c; std::cin >> a >> b >> c;
		adder.add_edge(a,b,c);
	}

	int min = std::numeric_limits<int>::max();
	int imin = 0;
	for(int i=0; i<n; ++i){
		int flow = boost::push_relabel_max_flow(G, i, (i+1)%n);
		if(flow < min){
			min = flow;
			imin = i;
		}
	}

	int flow = boost::push_relabel_max_flow(G, imin, (imin+1)%n);
	std::cout << flow << '\n';
	std::vector<int> my_statues;

	std::vector<int> vis(n, false);
	std::queue<int> Q;
	vis[imin] = true;
	my_statues.push_back(imin);
	Q.push(imin);
	while (!Q.empty()) {
		const int u = Q.front();
		Q.pop();
		out_edge_it ebeg, eend;
		for (boost::tie(ebeg, eend) = boost::out_edges(u, G); ebeg != eend; ++ebeg) {
			const int v = boost::target(*ebeg, G);
			if (rc_map[*ebeg] == 0 || vis[v]) continue;
			vis[v] = true;
			my_statues.push_back(v);
			Q.push(v);
		}
	}

	std::sort(my_statues.begin(), my_statues.end());
	std::cout << my_statues.size();
	for(int statue : my_statues){
		std::cout << ' ' << statue;
	}
	std::cout << '\n';
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
