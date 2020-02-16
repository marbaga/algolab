//Implementation by marcobaga
//This solution achieves 0 points

#include <vector>
#include <iostream>

void testcase(){
	int k; std::cin >> k;
	std::vector<std::vector<int>> balls(k, std::vector<int>(k));
	std::vector<std::vector<int>> dist_t(k, std::vector<int>(k));
	std::vector<std::vector<int>> dist_l(k, std::vector<int>(k));
	std::vector<std::vector<int>> dist_r(k, std::vector<int>(k));
	for(int i=0; i<k; ++i){
		for(int j=0; j<=i; ++j){
			std::cin >> balls[i][j];
		}
	}


	for(int i=0; i<k; ++i){
		for(int j=0; j<=i; ++j){
			std::cout << balls[i][j] << ' ';
		}
		std::cout << '\n';
	}

	dist_t[0][0] = 0;
	for(int i=1; i<k; ++i){
		for(int j=0; j<=i; ++j){
			if(j==0){
				dist_t[i][j] = balls[i][j] + dist_t[i-1][j];
			} else if (j==i){
				dist_t[i][j] = balls[i][j] + dist_t[i-1][j-1];
			} else{
				dist_t[i][j] = balls[i][j] + std::min(dist_t[i-1][j], dist_t[i-1][j-1]);
			}
		}
	}


	for(int i=0; i<k; ++i){
		for(int j=0; j<=i; ++j){
			std::cout << dist_t[i][j] << ' ';
		}
		std::cout << '\n';
	}


	dist_r[k-1][k-1] = 0;
	for(int j=k-2; j>=0; --j){
		for(int i=k-1; i>=j; --i){
			if(j==i){
				dist_r[i][j] = balls[i][j] + dist_r[i+1][j+1];
			} else if (i==k-1){
				dist_r[i][j] = balls[i][j] + dist_r[i][j+1];
			} else {
				dist_r[i][j] = balls[i][j] + std::min(dist_r[i][j+1], dist_r[i+1][j+1]);
			}
		}
	}

	for(int i=0; i<k; ++i){
		for(int j=0; j<=i; ++j){
			std::cout << dist_r[i][j] << ' ';
		}
		std::cout << '\n';
	}


	dist_l[k-1][0] = 0;
	for(int d=1; d<k; ++d){
		int i = k-1-d;
		int j = 0;
		while(i<k){
			//std::cout << i << ' ' << j << '\n';
			if(i==k-1){
				dist_l[i][j] = balls[i][j] + dist_l[i][j-1];
			} else if (j==0){
				dist_l[i][j] = balls[i][j] + dist_l[i+1][j];
			} else {
				dist_l[i][j] = balls[i][j] + std::min(dist_l[i][j-1], dist_l[i+1][j]);
			}
			j++;
			i++;
		}
	}


	for(int i=0; i<k; ++i){
		for(int j=0; j<=i; ++j){
			std::cout << dist_l[i][j] << ' ';
		}
		std::cout << '\n';
	}


	int min = k *2000;
	for(int i=0; i<k; ++i){
		for(int j=0; j<=i; ++j){
			min = std::min(min, dist_t[i][j]+dist_r[i][j]+dist_l[i][j]-2*balls[i][j]);
		}
	}
	std::cout << min << '\n';
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
