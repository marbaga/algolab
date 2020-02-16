//Implementation by marcobaga
//This solution achieves 100 points

#include <iostream>
#include <vector>
#include <algorithm>

int bin_search(std::vector<int> &vec, int target){
	int ll = 0;
	int lr = vec.size()-1;
	if(vec[ll] >= target)
		return ll;
	if(vec[lr] < target)
		return vec.size();
	while(ll < lr-1){
		int tmp = ll + (lr-ll)/2;
		if(vec[tmp]<target)
			ll = tmp;
		else
			lr = tmp;
	}
	return lr;
}

void testcase(){
	int n,m; std::cin >> n >> m;
	std::vector<int> s(n);
	std::vector<int> b(m);
	for(int i=0; i<n; ++i)
		std::cin >> s[i];
	for(int i=0; i<m; ++i)
		std::cin >> b[i];

    	std::sort(b.begin(), b.end(), std::greater<int>());
    	std::sort(s.begin(), s.end(), std::greater<int>());

/*
	std::cout << "Strengths: \n";
	for(int i=0; i<n; ++i)
		std::cout << s[i] << ' ';
	std::cout << '\n';
	std::cout << "Boxes: \n";
	for(int i=0; i<m; ++i)
		std::cout << b[i] << ' ';
	std::cout << '\n';
*/
	if(b[0]>s[0]){
		std::cout << "impossible\n";
		return;
	}

	std::vector<int> ind (1, 0);
	std::vector<int> ind_s (1, s[0]);
	for(int i=0; i<m; ++i){
		int j=0;
		j = bin_search(ind_s, b[i]);
		if (j >= ind.size()){
			ind.push_back(0);
			ind_s.push_back(s[0]);
		}
		ind[j]++;
		if(ind[j]<n){
			ind_s[j] = s[ind[j]];
		} else {
			ind_s[j] = -1;
		}
	}
	std::cout << 2 + (ind.size()-1)*3 << '\n';
	return;
}


int main(){
	std::ios_base::sync_with_stdio(false);
	int t; std::cin >> t;
	while(t-->0)
		testcase();
	return 0;
}
