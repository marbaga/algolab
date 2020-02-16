//Implementation by marcobaga
//This solution achieves 100 points

#include <iostream>
#include <vector>
#include <algorithm>

int main(){

	std::ios_base::sync_with_stdio(false);
	int t;
	std::cin >> t;
	while(t>0){
		int n;
		std::cin >> n;
		std::vector<std::pair<int, int>> boats(n);

		for(int i=0; i<n; ++i){
			int l,r;
			std::cin >> l >> r;
			boats[i] = std::make_pair(r, l);
		}
		//std::cout << "Read input" << std::endl;

		std::sort(boats.begin(), boats.end());

		//for (int i=0; i<n; ++i){
			//std::cout << boats[i].first << ' ' << boats[i].second << std::endl;
		//}

		int count = 1;
		int last_taken = boats[0].first;
		//std::cout << "First boat finishes at " << last_taken << std::endl;
		for(int i=1; i<n; ++i){
			if(boats[i].first >=last_taken){
				//std::cout << "Considering boat at ring " << boats[i].first << std::endl;
				int possible_end = std::max(boats[i].first, last_taken + boats[i].second);
				//std::cout << "This boat would end at " << possible_end << std::endl;
				int cnt;
				for(cnt=0; (i+1+cnt<n) && (boats[i+1+cnt].first<possible_end); cnt++);
				//std::cout << "It would overlap with this many rings: " << cnt <<std::endl;
				int sel = i;
				for(int j=0; j<cnt; ++j){
					//std::cout << "Comparing with boat at ring " << boats[i+1+j].first << std::endl;
					int curr_end = std::max(boats[i+1+j].first, last_taken + boats[i+1+j].second);
					//std::cout << "That boat would end at " << curr_end << std::endl;
					if(curr_end < possible_end){
						
						possible_end = curr_end;
						sel = i+1+j;
					}

				}
				i = sel;
				last_taken = possible_end;
				//std::cout << "One boat was placed until " << last_taken << std::endl;
				count++;
			}
		}
		std::cout << count << std::endl;
		t--;
	}	
	return 0;
}
