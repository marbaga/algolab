//Implementation by marcobaga
//This solution achieves 100 points

#include <iostream>
#include <algorithm>
#include <vector>


void testcase(){
	int n,m,r,b;
	std::cin >> n >> m >> r >> b;
	std::vector<std::vector<int>> tr(n+1, std::vector<int>());

	for(int i=0; i<m; ++i){
		int u,v;
		std::cin >> u >> v ;
		tr[u].push_back(v);
	}

	std::vector<int> min(n+1, 500000);
	std::vector<int> max(n+1, -1);
	min[n]=0;
	max[n]=0;
	for(int i=n-1; i>=std::min(r,b); --i){
		for (int dest : tr[i]){
			min[i] = std::min(min[i], 1+max[dest]);
			max[i] = std::max(max[i], 1+min[dest]);
		}
	}
	int red = min[r];
	int black = min[b];

	if(red<black || (red==black && red%2==1))
		std::cout << 0 << '\n';
	else
		std::cout << 1 << '\n';
	return;
}

int main(){
	std::ios_base::sync_with_stdio(false);
	int t;
	std::cin >> t;
	while(t>0){
		testcase();
		t--;
	}
	return 0;
}
