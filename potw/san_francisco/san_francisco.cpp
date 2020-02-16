#include <vector>
#include <iostream>
#include <algorithm>

void testcase(){
	long n,m,x,k; std::cin >> n >> m >> x >> k;
	std::vector<std::vector<std::pair<long,long>>> canals(n);
	for(int i=0; i<m; ++i){
		long u,v,p; std::cin >> u >> v >> p;
		canals[u].push_back(std::make_pair(v,p));
	}
	std::vector<std::vector<long>> DP(n,std::vector<long>(k+1, -1));
	for(int i=0; i<n; ++i){
		DP[i][0] = 0;
	}
	for(int j=1; j<=k; ++j){
		for(int i=0; i<n; ++i){
			if(canals[i].empty()){
				DP[i][j] = DP[0][j];
				continue;
			}
			long max = 0;
			for(auto candidate : canals[i]){
				max = std::max(max, candidate.second + DP[candidate.first][j-1]);
			}
			DP[i][j] = max;
			if(i==0&&DP[i][j]>=x){
				std::cout << j << '\n';
				return;
			}
		}
	}
	std::cout << "Impossible\n";
	return;
}

int main(){
	std::ios_base::sync_with_stdio(false);
	int t; std::cin >> t;
	while(t-- >0){
		testcase();
	}
	return 0;
}