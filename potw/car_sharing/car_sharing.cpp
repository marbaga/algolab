//Implementation by marcobaga
//This solution achieves 100 points

#include <vector>
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
typedef boost::graph_traits<graph>::vertex_iterator           vert_it;

class edge_adder {
 graph &G;
 public:
  explicit edge_adder(graph &G) : G(G) {}
  void add_edge(int from, int to, long capacity, long cost, std::vector<bool> &used) {
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
	used[from] = true;
	used[to] = true;
	//std::cout << "adding edge " << from << ' ' << to << ' ' << capacity << ' ' <<cost << '\n';
  }
};

void testcase(){
	int n, s; std::cin >> n >> s;
	std::vector<int> initial_c(n);
	int tot_car = 0;
	for(int i=0; i<s; ++i){
		std::cin >> initial_c[i];
		tot_car += initial_c[i];
	}
	//std::cout << "total cars: " << tot_car << '\n';
	
	std::vector<int>timestamp(100001, -1);
	std::vector<std::tuple<int,int,int,int,int>> req;
	for(int i=0; i<n; ++i){
		int si, ti, di, ai, pi; std::cin >> si >> ti >> di >> ai >> pi;
		si--;
		ti--;
		timestamp[di] = -2;
		timestamp[ai] = -2;
		req.push_back(std::make_tuple(si, ti, di, ai, pi));
	}

	int count = 0;
	for(int i=0; i<100001; ++i){
		if(timestamp[i]==-2){
			//std::cout << i << ' ';
			timestamp[i] = count;
			count++;
		}
	}
	//std::cout << '\n';
	//std::cout << "important events: " << count << '\n';;

	graph G(s*count+2);
	edge_adder adder(G);
	std::vector<bool> used(s*count+2, false);

	int source = s*count;
	int target = s*count + 1;
	for(int i=0; i<n; ++i){
		int si = std::get<0>(req[i]), ti=std::get<1>(req[i]), di=std::get<2>(req[i]), ai=std::get<3>(req[i]), pi=std::get<4>(req[i]);
		int dt = timestamp[di];
		int at = timestamp[ai];
		adder.add_edge(dt*s+si, at*s+ti, 1, 100*(at-dt)-pi, used);
		//std::cout << "adding edge " << dt*s+si << ' ' << at*s+ti << ' ' << 1 << ' ' << 100*(at-dt)-pi << '\n';
		//std::cout << 100*(at-dt)-pi << '\n';
	}

	for(int i=0; i<s; ++i){
		adder.add_edge(source, i, initial_c[i], 0, used);
		int last = i;
		int following = i+s;
		while(following<(count-1)*s+i){
    			//out_edge_it e, eend;
			//boost::tie(e, eend) = boost::out_edges(boost::vertex(following,G), G);
			if(used[following]){
				adder.add_edge(last, following, tot_car, (following-last)*100/s, used);
				//std::cout << (following-last)*100/s << '\n';
				last = following;
			}
			following+=s;
		}
		adder.add_edge(last, following, tot_car, (following-last)*100/s, used);
		//std::cout << (following-last)*100/s << '\n';
		adder.add_edge(following, target, tot_car, 0, used);
	}

	int flow = boost::push_relabel_max_flow(G, source, target);
	boost::successive_shortest_path_nonnegative_weights(G, source, target);
	int cost = boost::find_flow_cost(G);
	std:: cout << 100*(count-1)*tot_car - cost << '\n';
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
