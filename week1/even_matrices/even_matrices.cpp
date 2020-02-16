//Implementation by marcobaga
//This solution achieves 100 points

#include <iostream>
#include <vector>
int main(){
	int t;
	std::cin >> t;
	while(t!=0){

		int n;
		std::cin >> n;
		std::vector<std::vector<int>> v(n, std::vector<int>(n));

		for(int i=0; i<n; ++i){
			for(int j=0; j<n; ++j){
				std::cin >> v[i][j];
			}
		}

		for(int i=0; i<n; ++i){
			for(int j=1; j<n; ++j){
				v[i][j] += v[i][j-1];
			}
		}

		for(int i=1; i<n; ++i){
			for(int j=0; j<n; ++j){
				v[i][j] += v[i-1][j];
			}
		}

		int count=0;
		for(int i=0; i<n; ++i){
			int e=0;
			int o=0;
			for(int j=0; j<n; ++j){
				if(v[i][j]%2==0){
					e++;
				} else {
					o++;
				}
			}
			count += (((e*(e-1))+(o*(o-1)))/2) + e;

			for(int h=0; h<i; ++h){
				o=0;
				e=0;
				for(int j=0; j<n; ++j){
					if((v[i][j]+v[h][j])%2==0){
						e++;
					} else {
						o++;
					}
				}
				count += (((e*(e-1))+(o*(o-1)))/2) + e;
			}
		}
		std::cout << count << '\n';

		t--;
	}
	return 0;
}
