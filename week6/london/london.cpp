//Implementation by marcobaga
//This solution achieves 100 points

#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

#define A_LENGHT 26

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
		c_map[rev_e] = 0;
		r_map[e] = rev_e;
		r_map[rev_e] = e;
	}
};

int main(){

	std::ios_base::sync_with_stdio(false);
	int t;
	std::cin >> t;
	while(t>0){

		//read input
		int h, w;
		std::cin >> h >> w;
		std::string note;
		getline(std::cin, note); //flush endline
		getline(std::cin, note);

		//count letters appearing in the note
		std::vector<std::pair<int, int>> count(A_LENGHT, std::make_pair(0,-1));
		int letters_used=0;
		for(int i=0; i<note.length(); ++i){
			if(count[int(note[i]-'A')].first==0){
				letters_used++;
			}
			count[int(note[i]-'A')].first++;
		}

		//read front of the note
		std::vector<std::vector<char>> front (h, std::vector<char>(w));
		for(int i=0; i<h; ++i){
			for(int j=0; j<w; ++j){
				std::cin >> front[i][j];
			}
		}

		//count snippets and assign vertex indices
		std::vector<std::vector<std::pair<int, int>>> snippets (A_LENGHT, std::vector<std::pair<int, int>>(A_LENGHT, std::make_pair(0,-1)));
		int k=0;	//vertex index
		int snippets_used=0;
		for(int i=0; i<h; ++i){
		    for(int j=0; j<w; ++j){
		        int a,b;
		        a=front[i][w-j-1]-'A';
				char t;
				std::cin >> t;
		        b=t-'A';
		        if(a<b){
		            int temp = a;
		            a=b;
		            b=temp;
		        }
		        if(snippets[a][b].first==0){
		            snippets_used++;
		            snippets[a][b].second=k;
		            k++;
		        }
		        snippets[a][b].first++;
		    }
		}
		
		//assign vertex indices to each letter
		for (int i=0; i<A_LENGHT; ++i){
		    if(count[i].first>0){
		        count[i].second=k;
		        k++;
		    }
		}

		//construct the graph
		graph G(snippets_used+letters_used+2);
		edge_adder adder(G);
		int source = snippets_used+letters_used;
		int sink = snippets_used+letters_used+1;

		//add edges from the source to snippets and from snippets to their letters
		for(int i=0; i<A_LENGHT; ++i){
			for(int j=0; j<=i; ++j){
                if(snippets[i][j].first>0){
                    adder.add_edge(source, snippets[i][j].second, snippets[i][j].first);
					if(count[i].first>0){
	        		    adder.add_edge(snippets[i][j].second, count[i].second, snippets[i][j].first);
					}
                    if(i!=j && count[j].first>0){
                        adder.add_edge(snippets[i][j].second, count[j].second, snippets[i][j].first);
                    }
                }
			}
		}

		//add edge from letters to sink
		for(int i=0; i<A_LENGHT; i++){
            if(count[i].first>0){
                adder.add_edge(count[i].second, sink, count[i].first);
            }
		}

		//compute max flow
		long flow = boost::push_relabel_max_flow(G, source, sink);

		if(flow==note.length()){
			std::cout << "Yes" << std::endl;
		} else {
			std::cout << "No" << std::endl;
		}

		t--;
	}	
	return 0;
}
