//Implementation by marcobaga
//This solution achieves 100 points

#include <iostream>
#include <vector>
#include <algorithm>

bool sortbysec(const std::pair<int,int> &a, 
              const std::pair<int,int> &b) 
{ 
    return (a.second < b.second); 
}


bool between (int a, int b, int c){
	if((a<=c&&(a<=b && b<=c)) || (c<a&&(b<=c || b>=a)))
		return true;
	return false;
}

bool intersect (int a1, int a2, int b1, int b2){
	if(between(a1, b1, a2) || between(a1, b2, a2) || between(b1, a1, b2) || between(b1, a2, b2))
		return true;
	return false;
}


int main(){ 

	std::ios_base::sync_with_stdio(false);
	int t;
	std::cin >> t;
	while(t>0){
		int n, m;
		std::cin >> n >> m;

		std::vector<std::pair<int, int>> jedi(n);
		std::vector<std::pair<int, bool>> sums;

		for(int i=0; i<n; ++i){
			int begin, end;
			std::cin >> begin >> end;
			jedi[i] = std::make_pair(begin, end);
			sums.push_back(std::make_pair(begin, true));
			sums.push_back(std::make_pair(end+1, false));
		}

		std::sort(sums.begin(), sums.end());

		int partial_sum = 0;
		int min = 0;
		int pos = 1;
		for(int i=0; i<sums.size(); ++i){
			if(sums[i].second){
				partial_sum++;
			} else {
				partial_sum--;
				if(partial_sum<min){
					min = partial_sum;
					pos = sums[i].first;
				}
			}
		}
		
		std::sort(jedi.begin(), jedi.end(), sortbysec);

		std::vector<int> jedi_to_choose;
		//std::cout << pos << std::endl;
		for(int i=0; i<n; i++){
			if(between(jedi[i].first, pos, jedi[i].second)){
				jedi_to_choose.push_back(i);
				//std::cout << jedi[i].first << ' ' << jedi[i].second << std::endl;
			}
		}
		//std::cout << '\t' << pos << std::endl;



		int max_jedi=0;
		for (int curr_jedi_ind : jedi_to_choose){
			std::pair<int, int> curr_jedi = jedi[curr_jedi_ind];
			
			int blocked_until = curr_jedi.second;
			int curr_max = 1;
			for(int i=curr_jedi_ind; i<n; ++i){
				if(i!=curr_jedi_ind && !intersect(curr_jedi.first, blocked_until, jedi[i].first, jedi[i].second)){
					curr_max++;
					blocked_until = jedi[i].second;
				}
			}
			for(int i=0; i<curr_jedi_ind; ++i){
				if(i!=curr_jedi_ind && !intersect(curr_jedi.first, blocked_until, jedi[i].first, jedi[i].second)){
					curr_max++;
					blocked_until = jedi[i].second;
				}
			}
			if(curr_max > max_jedi){
				max_jedi = curr_max;
			}
		}


		if(n>0){
			int curr_max = 1;
			int found_ind = 0;
			while(found_ind<n&&jedi[found_ind].second<=pos){
				found_ind++;
			}
			if(found_ind==n){
				found_ind =0;
			}
			while(found_ind<n&&between(jedi[found_ind].first, pos, jedi[found_ind].second)){
				found_ind++;
			}
			if(found_ind==n){
				found_ind =0;
			}
			while(found_ind<n&&between(jedi[found_ind].first, pos, jedi[found_ind].second)){
				found_ind++;
			}
			if(found_ind==n){
				found_ind =0;
			}
			std::pair<int, int> curr_jedi = jedi[found_ind];
			int blocked_until = curr_jedi.second;

			for(int i=found_ind; i<n; ++i){
			//std::cout << "Testing " << jedi[i].first << ' ' << jedi[i].second << std::endl;
				if(!intersect(curr_jedi.first, blocked_until, jedi[i].first, jedi[i].second)){
					curr_max++;
					blocked_until = jedi[i].second;
				}
			}
			for(int i=0; i<found_ind; ++i){
				//std::cout << "Testing " << jedi[i].first << ' ' << jedi[i].second << std::endl;
				if(!intersect(curr_jedi.first, blocked_until, jedi[i].first, jedi[i].second)){
					curr_max++;
					blocked_until = jedi[i].second;
				}
			}

			if(curr_max > max_jedi){
				max_jedi = curr_max;

			}
		}

		std::cout << max_jedi << std::endl;
/*
		if(jedi_to_choose.size()>20){
			std::cout << pos << std::endl;
			for(int i=0; i<jedi_to_choose.size(); ++i){
				std::cout << jedi[jedi_to_choose[i]].first << ' ' << jedi[jedi_to_choose[i]].second << std::endl;
			}
		}
*/
		t--;
	}
	return 0;
}
