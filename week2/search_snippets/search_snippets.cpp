//Implementation by marcobaga
//This solution achieves 100 points

#include <iostream>
#include <vector>
#include <algorithm>

void testcase(){
	//std::cout << "Testcase begun\n";
	int n;
	std::cin >> n;
	//std::cout << "n:" << n << '\n';
	std::vector<int> counter(n, 0);
	std::vector<int> m(n);
	int length=0;
	for(int i=0; i<n; ++i){
		std::cin >> m[i];
		//std::cout << "m[" << i << "]=" << m[i] << '\n';
		length+=m[i];
	}
	//std::cout << "Read m\n";
	//std::cout << "Total length: " << length << '\n';

	int start=0;
	std::vector<std::pair<int,int>> v;
	for(int i=0; i<n; ++i){
		int min=0;
		for(int j=0; j<m[i]; ++j){
			int temp;
			std::cin >> temp;
			if(j==0||temp<min)
				min = temp;
			v.push_back(std::make_pair(temp, i));
		}
		if(min>start)
			start = min;
		//std::cout << start << '\n';
	}
	
	//std::cout << "Data acquired\n";
	std::sort(v.begin(), v.end());

	int l=0;
	int r=0;

	while(v[r].first<start){
		counter[v[r].second]++;
		r++;
	}
	counter[v[r].second]++;
	int ans = v[r].first - v[0].first + 1;

	for(int i=0; i<n; ++i){
		if(counter[i]==0){
			std::cout << "ERROR\n";
		}
	}

	//std::cout << "Starting\n";
	while(r<length){
		while(counter[v[l].second]>1&&l<=r){
			counter[v[l].second]--;
			l++;
		}
		ans = std::min(ans, v[r].first-v[l].first+1);
		while(counter[v[l].second]<2&&r<length){
			r++;
			counter[v[r].second]++;
		}
	}

	std::cout << ans << '\n';
	return;
}




int main(){
	std::ios_base::sync_with_stdio(false);
	int t;
	std::cin>>t;
	while(t>0){
		testcase();
		t--;
	}
	return 0;
}
