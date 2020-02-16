//Implementation by marcobaga
//This solution achieves 100 points

#include <vector>
#include <iostream>
#include <map>

void flip_switch(	int start,
			int end,
			std::vector<int> &setup,
			std::vector<std::vector<int>> &on,
			std::vector<std::vector<int>> &off,
			std::map<std::vector<int>, int> &map,
			int switched){
	if(start>end){
		return;
	}
	flip_switch(start+1, end, setup, on, off, map, switched);
	int m = setup.size();
	std::vector<int> backup = setup;
	for(int i=0; i<m; ++i){
		setup[i] = setup[i] + off[start][i] - on[start][i];
	}
	std::vector<int> copy = setup;
	if(map.find(copy)==map.end()){
		map.insert(std::make_pair(copy, switched+1));
	} else {
		int min = std::min(map.find(copy)->second, switched+1);
		map.find(copy)->second = min;
	}
	flip_switch(start+1, end, setup, on, off, map, switched+1);
	setup = backup;
	return;
}

void testcase(){
	int n, m; std::cin >> n >> m;
	std::vector<int> target(m);
	for(int i=0; i<m; ++i){
		std::cin >> target[i];
	}
	std::vector<std::vector<int>> on (n, std::vector<int>(m));
	std::vector<std::vector<int>> off (n, std::vector<int>(m));

	for(int i=0; i<n; ++i){
		for(int j=0; j<m; ++j){
			std::cin >> on[i][j] >> off[i][j];
			target[j] -= on[i][j];
		}
	}

	std::vector<int> empty_array(m, 0);
	std::vector<int> setup(m, 0);
	std::map<std::vector<int>, int> comb1;
	comb1.insert(std::make_pair(empty_array, 0));
	flip_switch(0, (n/2)-1, setup, on, off, comb1, 0);
	std::map<std::vector<int>, int> comb2;
	comb2.insert(std::make_pair(empty_array, 0));
	flip_switch(n/2, n-1, setup, on, off, comb2, 0);
/*
	std::cout << "Updated target  ";
	for(int i=0; i<m; ++i){
		std::cout << target[i] << ' ';
	}
	std::cout << '\n';

	std::cout << "Combinations 1: \n";
	for(auto v : comb1){
		std::cout << v.second << " total switches  ";
		for(int i=0; i<m; ++i){
			std::cout << v.first[i] << ' ';
		}
		std::cout << '\n';
	}
	std::cout << "Combinations 2: \n";
	for(auto v : comb2){
		std::cout << v.second << " total switches  ";
		for(int i=0; i<m; ++i){
			std::cout << v.first[i] << ' ';
		}
		std::cout << '\n';
	}
*/
	int min = 31;	
	for (auto v : comb1){
		std::vector<int> complement(m);
		for(int i=0; i<m ; ++i){
			complement[i] = target[i]-v.first[i];
		}
		auto it = comb2.find(complement);
		if(it!=comb2.end()){
			min = std::min(min, it->second+v.second);	
		}
	}

	if(min < 31){
		std::cout << min << '\n';
	} else {
		std::cout << "impossible\n";
	}
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
