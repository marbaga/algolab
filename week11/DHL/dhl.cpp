//Implementation by marcobaga
//This solution achieves 99 points

#include <iostream>
#include <vector>

void testcase(){
	int n; std::cin >> n;
	std::vector<int> a(n);
	std::vector<int> b(n);
	for(int i=0; i<n; ++i)
		std::cin >> a[i];
	for(int i=0; i<n; ++i)
		std::cin >> b[i];

	//for(int i=n-1; i>=0; --i){
		//std::cout << a[i] << '\t' << b[i] << '\n';
	//}
	//std::cout << '\n';

	std::vector<int>suma(n+1);
	std::vector<int>sumb(n+1);
	suma[0] = 0;
	sumb[0] = 0;
	for(int i=0; i<n; ++i){
		suma[i+1] = a[i]+suma[i];	//ith element is first + .. + i+1 from bottom
		sumb[i+1] = b[i]+sumb[i];
	}

	//for(int i=0; i<n; ++i)
		//std::cout << suma[i] << ' ';
	//std::cout << '\n';
	//for(int i=0; i<n; ++i)
		//std::cout << sumb[i] << ' ';
	//std::cout << '\n';

	std::vector<std::vector<long>> DP (n+1, std::vector<long>(n+1, -1));
	DP[0][0] = 0;
	for(int i=1; i<n+1; ++i){
		for(int j=1; j<n+1; ++j){
			long min = (suma[i]-i) * (sumb[j]-j); //take all
			for(int h=1; h<i&&j>1; ++h) // how many we are throwing out
				min = std::min(min, DP[i-h][j-1]+(suma[i]-suma[i-h]-h)*(b[j-1]-1));
			for(int h=1; h<j&&i>1; ++h) // how many we are throwing out
				min = std::min(min, DP[i-1][j-h]+(a[i-1]-1)*(sumb[j]-sumb[j-h]-h));
			DP[i][j] = min;
		}
	}
	std::cout << DP[n][n] << '\n';
/*
	for(int i=0; i<n+1; ++i){
		for(int j=0; j<n+1; ++j){
			std::cout << DP[i][j] << ' ';
		}
		std::cout << '\n';
	}
*/
	return;
}

int main(){
	std::ios_base::sync_with_stdio(false);
	int t; std::cin >> t;
	while(t-- > 0)
		testcase();
	return 0;
}
