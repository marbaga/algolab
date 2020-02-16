//Implementation by marcobaga
//This solution achieves 100 points

#include <iostream>
#include <array>

int main (){
	std::ios_base::sync_with_stdio(false);
	int t;
	std::cin >> t;
	for(int a=0; a<t; ++a){
		int n, m, k;
		std::cin >> n;
		std::cin >> m;
		std::cin >> k;
		std::array<int, 1000> coins;
		for(int i=0; i<n; i++){
			std::cin >> coins.at(i);
		}
        std::array<int, 1000> cache = {-1};

        if((n-1)%m==k){
            for(int i=0; i<n; ++i){
                cache.at(i)=coins.at(i);
            }
        } else {
            for(int i=0; i<n; ++i){
                cache.at(i)=0;
            }
        }
        int curr=(n-2)%m;
        for(int width=1; width<n; width++){
            if(curr==k){
                for(int i=0; i<n-width; i++){
                    cache.at(i)=std::max(cache.at(i)+coins.at(i+width), cache.at(i+1)+coins.at(i));
                }
            } else {
                for(int i=0; i<n-width; i++){
                    cache.at(i)=std::min(cache.at(i), cache.at(i+1));
                }
            }
            curr--;
            if(curr<0){
                curr+=m;
            }
        }
        std::cout << cache.at(0) << std::endl;
	}
	return 0;
}
