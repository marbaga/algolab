//Implementation by marcobaga
//This solution achieves 0 points

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

void testcase(){
	int n,m,k; std::cin >> n >> m >> k;
	std::vector<long> temp(n);
	for(int i=0; i<n ; ++i){
		std::cin >> temp[i];
	}

	std::vector<int> parent(n);
	std::vector<std::vector<int>> sons (n, std::vector<int>());
	for(int i=0; i<n-1; ++i){
		int u, v; std::cin >> u >> v;
		//std::cout << n << ' ' << u << ' ' << v << '\n';
		sons[u].push_back(v);
		parent[v] = u;
	}

	int curr = 0;
	std::vector<int> hist;
	std::multiset<int> temp_curr;
	std::vector<int> max(n, -1);
	std::vector<int> min(n, -1);
	std::vector<int> start(n, -1);
	std::vector<int> visited(n, 0);
	while(true){
		if(curr == 0 && sons[curr].size()==0) break;
		if(visited[curr] == 0){
			visited[curr] = 1;
			hist.push_back(curr);
			temp_curr.insert(temp[curr]);
			while(hist.size()>m){
				int oldest = hist[0];
				temp_curr.erase(temp[oldest]);
				hist.erase(hist.begin());
			}
			if(hist.size()==m){
				start[curr] = hist[0];
				max[curr] = *(temp_curr.end()--);
				min[curr] = *temp_curr.begin();
			}
		}
		if(sons[curr].size()>0){
			int son = sons[curr][0];
			sons[curr].erase(sons[curr].begin());
			curr = son;
		} else {
			int oldest = hist[0];
			if(oldest>0){
				int back_in = parent[oldest];
				hist.emplace(hist.begin(), back_in);
				temp_curr.insert(temp[back_in]);
			}
			hist.pop_back();
			temp_curr.erase(temp[curr]);
			curr = parent[curr];
		}
	}

	std::set<int> sol;
	for(int i=0; i<n; ++i){
		if(start[i]!=-1 && max[i]-min[i]<=k){
			sol.insert(start[i]);
		}
	}
	if(sol.empty()){
		std::cout << "Abort mission\n";
		return;
	}
	//std::sort(sol.begin(), sol.end());
	for(auto i = sol.begin(); i!=sol.end(); ++i){
		std::cout << *i << ' ';
	}
	std::cout << '\n';
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
