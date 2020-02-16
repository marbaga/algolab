//Implementation by marcobaga
//This solution achieves 100 points

#include <iostream>
#include <array>

int abs(int a){
    return a>0? a : -a;
}

int main(){

    std::ios_base::sync_with_stdio(false);

    int t;
    std::cin >> t;
    for(int h=0; h<t; ++h){

        int n,k, sol_i, sol_j, best_difference, sum;
        sol_i=0;
        sol_j=0;
        std::cin >> n;
        std::cin >> k;
        best_difference=k;
        std::array<int, 100000> deck;

        for(int i=0; i<n; ++i){
            std::cin >> deck.at(i);
        }

        sum=deck[0];

        int i = 0;
        int j = 0;

        while(j<n){
            //std::cout << "Trying i=" << i << " and j=" << j << ", sum=" << sum << ", k=" << k <<", n="<<n<< std::endl;
            if(abs(sum-k)<best_difference){
                best_difference = abs(sum-k);
                sol_i = i;
                sol_j = j;
                //std::cout << "Sum " << sum << " is very close to k " << k << std::endl;
            }
            if(sum==k){
                sol_i = i;
                sol_j = j;
                //std::cout << "Found perfect solution!" << std::endl;
                break;
            } else if(sum>k&&i<j){
                sum-=deck[i];
                //std::cout << "Sum " << sum << " is higher than k, moving i" << std::endl;
                i++;
            } else {
                j++;
                sum+=deck[j];
                //std::cout << "Sum " << sum << " is lower than k, moving j" << std:: endl;
            }
        }
        std::cout << sol_i << ' ' << sol_j << std::endl;
    }
    return 0;
}
