//Implementation by marcobaga
//This solution achieves 100 points

#include <iostream>
#include <vector>
#define OS 1000001

int main (){
	std::ios_base::sync_with_stdio(false);
	int t;
	std::cin >> t;
	while(t>0){

		std::vector<bool> beach(2*OS, false);
		std::vector<int> solutions;

		int n;
		std::cin >> n;
		for(int i=0; i<n; ++i){
			int tmp;
			std::cin >> tmp;
			beach[tmp + OS] = true;
		}

		int dist = 0;
		int min_dist = 0;
		int count = 0;
		int max_count = 0;
		int i=0;
		int l=0;
		int r=0;
		int rightmost = r;

		while(i<2*OS){

			while(l<i-100){
				if(beach[l])
					count--;
				l++;
			}
			while(!(beach[l]||l==i))
				l++;

			while(r<i+100&&r<2*OS){
				r++;
				if(beach[r]){
					count++;
					rightmost = r;
				}
			}

			if(rightmost<i){
				rightmost = i;
			}

			int dist = std::max(rightmost-i, i-l);

			if((count == max_count && dist < min_dist) || count > max_count){
				max_count = count;
				min_dist = dist;
				solutions.clear();
				solutions.push_back(i-OS);
			} else if (count == max_count && dist == min_dist){
				solutions.push_back(i-OS);
			}
			i++;
		}

		std::cout << max_count << ' ' << min_dist << '\n';
		for(int j=0; j<solutions.size(); ++j){
			std::cout << solutions[j] << ' ';
		}
		std::cout << '\n';

		t--;
	}
	return 0;
}
