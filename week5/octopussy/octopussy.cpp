//Implementation by marcobaga
//This solution achieves 100 points

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
void testcase(){
	int n; std::cin >> n;	//n < 2^16, odd
	std::vector<std::pair<long,int>> bombs(n);
	for(int i=0; i<n; ++i){
		int t; std::cin >> t;
		bombs[i] = std::make_pair(t, i);
	}
	std::sort(bombs.begin(), bombs.end());
	std::vector<int> m(n);
	std::vector<bool> defused(n, false);
	for(int j=0; j<n; ++j){
		m[bombs[j].second] = j;
	}
	int time = 0;
	std::stack<int> Q;
	for(int i=0; i<n; ++i){
		if(!defused[bombs[i].second]){
			Q.push(bombs[i].second);
			while(!Q.empty()){
				int curr = Q.top();
				//std::cout << "considering bomb " << curr << '\n';
				Q.pop();
				long timer = bombs[m[curr]].first;
				if(defused[curr]){
					//std::cout << "this bomb is already defused\n";
					continue;
				}
				if(time > timer-1){
					//std::cout << time << " > " << timer << '\n';
					std::cout << "no\n";
					return;
				}
				if(curr >= (n-1)/2){
					//std::cout << "it is on the floor\n";
					time++;
					defused[curr] = true;
					//std::cout << "Defusing " << curr << " at time " << time << '\n';
					continue;
				}
				bool support_defused = true;
				int s1 = 2*curr+1;
				int s2 = 2*curr+2;
				std::vector<int> sons = {2*curr+1, 2*curr+2};
				for(int s : sons){
					if(!defused[s]){
						support_defused = false;
					}
				}
				if(support_defused){
					time++;
					defused[curr] = true;
					//std::cout << "Defusing " << curr << " at time " << time << '\n';
				} else {
					Q.push(curr);
					for(int s : sons){
						if(!defused[s]){
							Q.push(s);
							//std::cout << "it lies on " << s << " which is yet to defuse\n";
						}
					}
				}
			}
		}
	}
	std::cout << "yes\n";
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
