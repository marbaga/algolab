//Implementation by marcobaga
//This solution achieves 100 points

#include <vector>
#include <iostream>

void testcase(){
	int n, ik, k; std::cin >> n >> ik >> k;
	//std::cout << "n " << n << " ik " << ik << " k " << k << '\n';
	std::vector<int> disk(n);
	for(int i=0; i<n; ++i){
		std::cin >> disk[i];
		disk[i] = disk[i] % k;
		//std::cout << disk[i] << ' ';
	}
	//std::cout << '\n';

	std::vector<std::vector<bool>> DP (n, std::vector<bool>(k, false));
	
	DP[0][disk[0]]=true;
	for(int i=1; i<n; ++i){
		for(int j=0; j<k; ++j){
			int offset = j-disk[i];
			if(offset<0)
				offset+=k;
			offset = offset % k;
			if(disk[i]==j || DP[i-1][j] || DP[i-1][offset]){
				DP[i][j]=true;
			}
		}
	}/*
	for(int i=0; i<n; ++i){
		for(int j=0; j<k; ++j){
			std::cout << DP[i][j] << ' ';
		}
		std::cout << '\n';
	}*/
	if(DP[n-1][ik])
		std::cout << "yes" << '\n';
	else
		std::cout << "no" << '\n';
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
