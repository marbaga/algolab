//Implementation by marcobaga
//This solution achieves 100 points

#include <iostream>
#include <vector>

void testcase(){
	int n,m,k; std::cin >> n >> m >> k;
	std::vector<int> def(n);
	for(int i=0; i<n; ++i){
		std::cin >> def[i];
	}
	std::vector<int> sequence_begin(n, -1);
	std::vector<int> length(n,-1);
	int l=0, r=0;
	int sum = def[0];
	do{
		while(sum<k&&r<n){
			r++;
			if(r<n){
				sum+=def[r];
			}
		}
		//std::cout << l << ' ' << r << ' ' << sum << '\n';
		while(sum>=k&&l<=r){
			if(sum==k){
				sequence_begin[r] = l;
				length[r] = r-l+1;
			}
			sum-=def[l];
			l++;
		}
	} while (r<n);

	std::vector<std::vector<int>> DP (n, std::vector<int>(m+1,-1));
	DP[0][0] = 0;
	if(sequence_begin[0]==0)
		DP[0][1] = 1;
	for(int i=1; i<n; ++i){
		DP[i][0] = 0;
		if(sequence_begin[i]==-1)
			DP[i][1] = DP[i-1][1];
		else
			DP[i][1] = std::max(length[i], DP[i-1][1]);
	}

	for(int i=1; i<n; ++i){
		for(int j=2; j<m+1; ++j){
			if(sequence_begin[i]<=0||DP[sequence_begin[i]-1][j-1]==-1)
				DP[i][j] = DP[i-1][j];
			else
				DP[i][j] = std::max(DP[i-1][j], DP[sequence_begin[i]-1][j-1] + length[i]);
			if(DP[i][j]==-1)
				break;
		}
	}
/*
	for(int i=0; i<n; ++i)
		std::cout << sequence_begin[i] << ' ';
	std::cout << '\n';

	for(int i=0; i<n; ++i)
		std::cout << length[i] << ' ';
	std::cout << '\n';

	for(int i=0; i<n; ++i){
		for(int j=0; j<m+1; j++){
			std::cout << DP[i][j] << ' ';
		}
		std::cout << '\n';
	}
*/
	if(DP[n-1][m] > 0)
		std::cout << DP[n-1][m] << '\n';
	else
		std::cout << "fail\n";
	return;
}


int main(){
	std::ios_base::sync_with_stdio(false);
	int t; std::cin >> t;
	while(t-->0)
		testcase();
	return 0;
}
