//Implementation by marcobaga
//This solution achieves 100 points

#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <queue>
#define MAXSIZE 100000

int compute_depth(int last, int i, std::array<int, MAXSIZE> *depth, std::array<std::vector<int>, MAXSIZE> *children){
    last++;
    (*depth).at(i) = last;
    if((*children).at(i).empty()){
        return last;
    }

    int max_depth = 0;

    for(int j : (*children).at(i)){

        int ans = compute_depth(last, j, depth, children);
        if(ans>max_depth){
            max_depth = ans;
        }
    }
    return max_depth;
}

int main(){

    std::ios_base::sync_with_stdio(false);

	int t;
	std::cin >> t;
	for(int h=0; h<t; ++h){
		int n;
		int cost_sum = 0;
		std::cin >> n;

		//std::cout << n << std::endl;
		std::array<int, MAXSIZE> costs;
		std::array<int, MAXSIZE> mincost;
		std::array<int, MAXSIZE> mincost2;
		std::array<int, MAXSIZE> parentcost;
		std::array<int, MAXSIZE> childcost;
		std::array<int, MAXSIZE> colorcost;
		std::array<std::vector<int>, MAXSIZE> parents;
		std::array<std::vector<int>, MAXSIZE> children;
		std::array<int, MAXSIZE> depth = {0};

		for(int i=0; i<n-1; ++i){
			int a;
			int b;
			std::cin >> a >> b;
			children.at(a).push_back(b);
			parents.at(b).push_back(a);
		}

		for(int i=0; i<n; ++i){
			int temp;
			std::cin >> temp;
			costs.at(i) = temp;
			cost_sum += temp;
		}

		//int max_depth = compute_depth(-1, 0, &depth, &children);

		std::queue<int> q;
		depth.at(0) = 0;
		for(int i : children.at(0)){
            q.push(i);
		}
		int max_depth = 0;
		while(!q.empty()){
            int curr = q.front();
            q.pop();
            depth.at(curr)=depth.at(parents.at(curr).at(0)) + 1;
            if(depth.at(curr)>max_depth){
                max_depth = depth.at(curr);
            }
            for(int i : children.at(curr)){
                q.push(i);
            }
		}


		//std::cout << "Depth computed" << std::endl;

		std::vector<std::vector<int>> cities_by_depth(max_depth + 1);
		for(int i=0; i<n; ++i){
            cities_by_depth.at(depth.at(i)).push_back(i);
		}

		//for(int i=0; i<n; ++i){
        //    std::cout << "Depth for node " << i << " is " << depth.at(i) << std::endl;
		//}

		for(int i=0; i<n; ++i){
			if(children.at(i).empty()){
                mincost.at(i) = 0;
                parentcost.at(i) = 0;
                mincost2.at(i) = costs.at(i);
                colorcost.at(i) = costs.at(i);
                childcost.at(i) = costs.at(i);
			}
		}

		for(int l=max_depth; l>=0; --l){
            //std::cout << l << std::endl;
			for(int i : cities_by_depth.at(l)){
                if(!children.at(i).empty()){
                    parentcost.at(i)=0;
                    colorcost.at(i) = costs.at(i);
                    int minchild = cost_sum;
                    int candidatesum = 0;
                    for(int j : children.at(i)){
                        candidatesum+=mincost2.at(j);
                    }
                    for(int j : children.at(i)){
                        parentcost.at(i) += mincost2.at(j);
                        colorcost.at(i)+=mincost.at(j);
                        int this_candidatesum = candidatesum - mincost2.at(j) + colorcost.at(j);
                        if(this_candidatesum<minchild){
                            minchild = this_candidatesum;
                        }
                    }
                    childcost.at(i) = minchild;
                    mincost2.at(i) = std::min(colorcost.at(i), childcost.at(i));
                    mincost.at(i) = std::min(parentcost.at(i), mincost2.at(i));

                }
			}
		}

		int i = 0;
        colorcost.at(i) = costs.at(i);
        int minchild = cost_sum;
        for(int j : children.at(i)){
            int candidate = colorcost.at(j);
            colorcost.at(i)+=mincost.at(j);
            for(int k : children.at(i)){
                if(k!=j){
                    candidate += mincost2.at(k);
                }
            }
            if(candidate<minchild){
                minchild = candidate;
            }
        }
		childcost.at(i) = minchild;
		mincost.at(i) = std::min(colorcost.at(i), childcost.at(i));

		/*for(int i=0; i<n; ++i){
            std::cout << " Node " << i << std::endl;
            std::cout << "Colorcost: " << colorcost.at(i) << std::endl;
            std::cout << "Childcost: " << childcost.at(i) << std::endl;
            std::cout << "Parentcost: " << parentcost.at(i) << std::endl;
            std::cout << "Mincost: " << mincost.at(i) << std::endl << std::endl;
		}*/

		std::cout << mincost.at(0) << std::endl;
	}
	return 0;
}
