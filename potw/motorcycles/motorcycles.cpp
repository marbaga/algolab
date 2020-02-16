//Implementation by marcobaga
//This solution achieves 100 points

#include <array>
#include <iostream>
#include <vector>
#include <boost/multiprecision/cpp_int.hpp>
#include <stack>
#include <algorithm>

typedef boost::multiprecision::int128_t int128;


int main(){
	int t;
	std::cin >> t;
	while(t>0){
		int n;
		std::cin >> n;

		std::vector<std::pair<int128, int>> start(n);
		std::vector<int128> dx(n);
		std::vector<int128> dy(n);
		std::vector<bool> rides(n, false);

		for(int i=0; i<n; ++i){
			int128 y0, x1, y1;
			std::cin >> y0 >> x1 >> y1;
			start[i].first = y0;
			start[i].second = i;
			dx[i] = x1;
			dy[i] = y1-y0;

/*
			std::cout << y0 << ' ' << x1 << ' ' << y1 << ' ' << dx[i]*dy[i] << std::endl;

			std::cout << i;
			if(dx[i]*dy[i]>0){
				std::cout << " is ascending ";
			} else if (dx[i]*dy[i]==0){				
				std::cout << " is horizontal ";
			} else {
				std::cout << " is descending ";
			}
			std::cout << "with dx=" << dx[i] << " and dy=" << dy[i] << std::endl;
*/
		}

		std::sort(start.begin(), start.end());
		std::reverse(start.begin(), start.end());
/*
		for(int i=0; i<n; ++i){
			std::cout << start[i].first << ' ' << start[i].second << std::endl;
			int j = start[i].second;
			std::cout << dx[j] << ' ' << dy[j] << ' ' << rides[j] << std::endl;
		}
*/
		int i=0;
		int scenario = 1; //ascending rays
		int128 dxm = 0;
		int128 dym = 1;

		std::stack<int> descending;

		for(int j=0; j<n; ++j){
			i = start[j].second;

			//std::cout << "Analyzing ray leaving from y=" << start[j].first << std::endl;

			if(scenario == 1){ 	//ascending rays
				//std::cout << "Last ray was ascending\n";
				if(dy[i]==0){
					scenario = 0;
					rides[i] = true;
					//std::cout << "This ray is horizontal\n";
				}else if(dy[i]>0){	//ascending line
					//std::cout << "This ray is ascending\n";
					//std::cout << "m = " << dy[i] << '/' << dx[i] << ", mmin = " << dym << '/' << dxm << std::endl;

					if(dy[i]*dxm<=dx[i]*dym){
						//std::cout << "This ray is less steep than the previous\n";
						rides[i] = true;
						dxm = dx[i];
						dym = dy[i];
					}
				} else {	//descending line
					//std::cout << "This ray is descending\n";
					descending.push(i);
					scenario = 2;
				}


			} else if(scenario == 2){ //descending rays
				if(dy[i]==0){
					scenario = 0;
					rides[i] = true;
					descending = std::stack<int>();
					//std::cout << "This ray is horizontal, the stack was emptied\n";
				}else if(dy[i]>0){	//ascending line
					//std::cout << "This ray is ascending\n";
					while(!(descending.empty() || abs(dy[i]*dx[descending.top()]) > abs(dx[i]*dy[descending.top()]))){
						descending.pop();
						//std::cout << "It eliminates a descending ray\n";
					}
					if(descending.empty()){
						scenario = 1;
						if(dy[i]*dxm<=dx[i]*dym){
							//std::cout << "This ray is less steep than the previous\n";
							rides[i] = true;
							dxm = dx[i];
							dym = dy[i];
						}
					}
				} else {	//descending line
					//std::cout << "This ray is descending\n";
					while(!(descending.empty() || abs(dy[i]*dx[descending.top()]) >= abs(dx[i]*dy[descending.top()]))){
						descending.pop();
						//std::cout << "It eliminates a ray\n";
					}
					descending.push(i);
				}


			} else if(scenario == 0) {	//an horizontal line was found
				if(dy[i]==0){
					rides[i] = true;
					descending = std::stack<int>();
					//std::cout << "This ray is horizontal too\n";
				}else if(dy[i]>0){	//ascending line
					//std::cout << "This ray is ascending and will not be couned\n"
					while(!(descending.empty() || abs(dy[i]*dx[descending.top()]) > abs(dx[i]*dy[descending.top()]))){
						descending.pop();
						//std::cout << "It eliminates a descending ray\n";
					}
					//do not do nothing, it cannot ride
				} else {	//descending line 
					while(!(descending.empty() || abs(dy[i]*dx[descending.top()]) >= abs(dx[i]*dy[descending.top()]))){
						descending.pop();
						//std::cout << "It eliminates a ray\n";
					}
					descending.push(i);
				}
			}
		}

		while(!descending.empty()){
			rides[descending.top()] = true;
			descending.pop();
		}

		std::vector<int> riders;
		for(int i=0; i<n; i++){
			if(rides[i]){
				riders.push_back(i);
			}
		}
		
		std::sort(riders.begin(), riders.end());

		for(int i : riders){
			std::cout << i << ' ';
		}
		std::cout << std::endl;

		t--;
	}
	return 0;
}
