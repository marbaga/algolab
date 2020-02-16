//Implementation by marcobaga
//This solution achieves 100 points

#include<vector>
#include<iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;
typedef boost::graph_traits<weighted_graph>::out_edge_iterator          out_edge_it;

void testcase(){
	int n,i; std::cin >> n >> i;
	weighted_graph G1(n);
	weight_map weights1 = boost::get(boost::edge_weight, G1);
	edge_desc e;
	//std::cout << "about to read input\n";
	std::vector<std::vector<int>> w (n, std::vector<int>(n, -1));
	for(int j=0; j<n-1; ++j){
		for(int k=j+1; k<n; ++k){
			int c; std::cin >> c;
  			e = boost::add_edge(j, k, G1).first; weights1[e]=c;
			w[j][k]=c;
			w[k][j]=c;
		}
	}
	std::vector<edge_desc> mst;
	//std::cout << "about to call kruskal\n";
	boost::kruskal_minimum_spanning_tree(G1, std::back_inserter(mst));

	weighted_graph G(n);
	weight_map weights = boost::get(boost::edge_weight, G);
	int total_weight=0;
	for (std::vector<edge_desc>::iterator it = mst.begin(); it != mst.end(); ++it) {
  		e = boost::add_edge(boost::source(*it, G1), boost::target(*it, G1), G).first;
		//std::cout << boost::source(*it, G1) << ' ' << boost::target(*it, G1) << '\n';
 		weights[e]=weights1[*it]; //????
		total_weight += weights[e]; //watch out it should be undirected
	}

	//std::cout << "About to start bfs\n";
	std::vector<std::vector<int>> largest_edge (n, std::vector<int>(n, -1));
	for (int v=0; v<n; ++v){
		//std::cout << "bfs\n";
		std::vector<int> parent(n,-1);
		std::queue<int> Q;
		parent[v]=v;
		largest_edge[v][v]=0;
		Q.push(v);
		while (!Q.empty()) {
			const int u = Q.front();
			Q.pop();
			out_edge_it ebeg, eend;
			for (boost::tie(ebeg, eend) = boost::out_edges(u, G); ebeg != eend; ++ebeg) {
				const int z = boost::target(*ebeg, G);
				if (parent[z]!=-1) continue;
				parent[z]=u;
				largest_edge[v][z] = std::max(largest_edge[v][u], weights[*ebeg]);
				largest_edge[z][v] = std::max(largest_edge[u][v], weights[*ebeg]);
				Q.push(z);
			}
		}
	}
	//std::cout << "finished bfs\n";
	int diff = std::numeric_limits<int>::max();
	for(int i=0; i<n; ++i){
		for(int j=0; j<n; ++j){
			if(!boost::edge(i,j,G).second&&i!=j){
				//std::cout << boost::edge(i,j,G).second << ' ' << i << ' ' << j << '\n';
				//std::cout << w[i][j] << ' ' << largest_edge[i][j] << '\n';
				diff = std::min(diff, w[i][j] - largest_edge[i][j]);
			}
		}
	}
	//std::cout << total_weight << ' ' << diff << '\n';
	std::cout << total_weight + diff << '\n';
	return;
}

int main(){
	std::ios_base::sync_with_stdio(false);
	int t; std::cin >> t;
	while(t-- > 0)
		testcase();
	return 0;
}
