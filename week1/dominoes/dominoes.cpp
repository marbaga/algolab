//Implementation by marcobaga
//This solution achieves 100 points

#include <iostream>

int main(){

    int t;
    std::cin >> t;
    for(int i=0; i<t; ++i){
        int n;
        std::cin >> n;
        int h = 2;
        int cnt = 0;
        for(int j=0; j<n; ++j){
            int temp;
            std::cin >> temp;
            h--;
            //std::cout << "Current height " << h << std::endl;
            if(h>0){
                cnt++;
                //std::cout << "Domino " << temp << " is falling." << std::endl;
                if(temp>h){
                    //std::cout << "The falling domino is taller than the last one" << std::endl;
                    h=temp;
                }
            }
        }
        std::cout << cnt << std::endl;
    }
    return 0;
}
