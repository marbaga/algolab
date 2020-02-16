//Implementation by marcobaga
//This solution achieves 100 points

#include <iostream>

int main(){

    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    for(int i=0; i<t; ++i){
        int n = 0;
        int even = 0;
        int odd = 0;
        std::cin >> n;
        int partial = 0;
        for(int i=0; i<n; ++i){
            int x;
            std::cin>>x;
            if((x&&partial)||(!x&&!partial)){
                even++;
                partial = 0;
            } else {
                odd++;
                partial = 1;
            }
        }
        std::cout << (odd*(odd-1) + (even-1)*even)/2 + even;
        std::cout << std::endl;
    }
    return 0;
}
