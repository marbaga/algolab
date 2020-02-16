//Implementation by marcobaga
//This solution achieves 100 points

#include <vector>
#include <iostream>
#include<iomanip>

void testcase(){
	int n,k,m; std::cin >> n >> k >> m;
	std::vector<double> p(n);
	for(int i=0; i<n; ++i){
		std::cin >> p[i];
	}
	std::vector<std::vector<double>> DP (m+1, std::vector<double>(n+1, -1));
	for(int j=0; j<n+1; ++j)
		DP[m][j]=1;
	for(int i=0; i<m; ++i)
		DP[i][n]=0;
	for(int j=n-1; j>=0; --j){
		for(int i=0; i<m; ++i){
			double max = 0;
			for(int bet = 0; bet<=std::min(i, m-i); ++bet){
				max = std::max(max, p[j]*(DP[i+bet][j+1])+(1-p[j])*(DP[i-bet][j+1]));
				//std::cout << "max " << max << "; bet = " << bet << '\n';
			}
			DP[i][j] = max;
		}
	}
/*
	for(int i=0; i<m+1; ++i){
		for(int j=0; j<n+1; ++j){
			std::cout << DP[i][j] << ' ';
		}
		std::cout << '\n';
	}
*/
	std::cout << DP[k][0] << "\n";
	return;
}


int main(){
	std::ios_base::sync_with_stdio(false);
	std::cout << std::fixed << std::setprecision(5);
	int t; std::cin >> t;
	while(t-- > 0)
		testcase();
	return 0;
}
