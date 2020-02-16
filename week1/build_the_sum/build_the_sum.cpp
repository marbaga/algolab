//Implementation by marcobaga
//This solution achieves 100 points

#include <iostream>

int main(){

    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    for(int i=0; i<t; ++i){

        int n = 0;
        std::cin >> n;
        int sum=0;
        for(int i=0; i<n; ++i){
            int x;
            std::cin>>x;
            sum += x;
        }
        std::cout << sum << std::endl;
    }
    return 0;
}
