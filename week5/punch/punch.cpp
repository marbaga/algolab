//Implementation by marcobaga
//This solution only achieves 50 points
//It can be sped up by limiting operations on vectors

#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

typedef std::tuple<int, int, std::vector<int>> cand_t;	//cost, #beverages, beverage vector
typedef std::tuple<int, int, int> bev_t;	//id, cost, liters

int maxx = std::numeric_limits<int>::max();

int compare(cand_t &a, cand_t &b){
	if(std::get<0>(a) < std::get<0>(b)){ return 1; }
	if(std::get<0>(a)==std::get<0>(b)){
		if(std::get<1>(a) >= std::get<1>(b)){ return 1;	}
	}
	return 0;
}

void testcase(){
	int n, k0; std::cin >> n >> k0;
	std::vector<bev_t> bev(n);
	int max_v = 0;
	for(int i=0; i<n; ++i){
		int c,v; std::cin >> c >> v;
		max_v = std::max(max_v, v);
		bev[i] = std::make_tuple(i,c,v);
	}
	int k = k0+std::min(max_v,4000);
	std::vector<int> empty_v;
	std::vector<cand_t> DP(k+1);
	for(int i=0; i<k+1; ++i){
		cand_t best_candidate = std::make_tuple(maxx,0,empty_v);
		for(auto b : bev){
			cand_t new_candidate;

			if(std::get<2>(b)>i){
				new_candidate = std::make_tuple(maxx,0,empty_v);
			} else if(std::get<2>(b)==i){
				std::vector<int> temp(0);
				temp.push_back(std::get<0>(b));
				new_candidate = std::make_tuple(std::get<1>(b),1,temp);
			} else if(std::get<0>(DP[i-std::get<2>(b)])==maxx){
				new_candidate = std::make_tuple(maxx,0,empty_v);
			} else {
				cand_t c = DP[i-std::get<2>(b)];
				int cost = std::get<1>(b) + std::get<0>(c);
				int bev_count = std::get<1>(c);
				std::vector<int> bev_used = std::get<2>(c);
				int found = false;
				for(int i=0; i<bev_used.size(); ++i){
					if(bev_used[i]==std::get<0>(b)){
						found = true;
						break;
					}
				}
				if(!found){
					bev_used.push_back(std::get<0>(b));
					bev_count++;
				}
				new_candidate = std::make_tuple(cost, bev_count, bev_used);
			}

			if(compare(best_candidate, new_candidate)==0){
				best_candidate = new_candidate;
			}
		}
		DP[i] = best_candidate;
	}
	cand_t best_candidate = DP[k0];
	while(k0<=k){
		if(compare(best_candidate, DP[k0])==0){
			best_candidate = DP[k0];
		}
		k0++;
	}

	std::cout << std::get<0>(best_candidate) << ' ' << std::get<1>(best_candidate) << '\n';
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
