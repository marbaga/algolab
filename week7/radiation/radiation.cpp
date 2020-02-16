//Implementation by marcobaga
//This solution achieves 0 points

#include <iostream>
#include <vector>
#include <algorithm>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef int IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

bool fit(int degree, std::vector<std::tuple<int,int,int>> hc, std::vector<std::tuple<int,int,int>>tc){
	Program lp (CGAL::SMALLER, true, 0, false, 0);
  	for(int h_it = 0; h_it < hc.size(); h_it++){
		std::tuple<int,int,int> p = hc[h_it];
		for(int dx=0; dx<=degree; ++dx){
			for(int dy=0; dy<=degree-dx; ++dy){
				for(int dz=0; dz<=degree-dx-dy; ++dz){
					int tmp = std::pow(std::get<0>(p), dx) + std::pow(std::get<1>(p),dy) + std::pow(std::get<2>(p),dz);
					int coeff = (dx*(degree+1)*(degree+1)+dy*(degree+1)+dz);
					lp.set_a(coeff, h_it,  tmp);
				}
			}
		
		}
		lp.set_b(h_it, -1);
	}    
	for(int t_it = 0; t_it < tc.size(); t_it++){
		std::tuple<int,int,int> p = tc[t_it];
		for(int dx=0; dx<=degree; ++dx){
			for(int dy=0; dy<=degree-dx; ++dy){
				for(int dz=0; dz<=degree-dx-dy; ++dz){
					int tmp = std::pow(std::get<0>(p), dx) + std::pow(std::get<1>(p),dy) + std::pow(std::get<2>(p),dz);
					int coeff = (dx*(degree+1)*(degree+1)+dy*(degree+1)+dz);
					lp.set_a(coeff, t_it,  -1*tmp);
				}
			}
		
		}
		lp.set_b(t_it, -1);
	}
	Solution s = CGAL::solve_linear_program(lp, ET());
	assert(s.solves_linear_program(lp));
	return !s.is_infeasible();
}


void testcase(){
	int h,t; std::cin >> h >> t;
	std::vector<std::tuple<int,int,int>> hc (h);
	std::vector<std::tuple<int,int,int>> tc (t);
	for(int i=0; i<h; ++i){
		int x,y,z; std::cin >> x >> y >> z;
		hc[i]=std::make_tuple(x,y,z);
	}
	for(int i=0; i<t; ++i){
		int x,y,z; std::cin >> x >> y >> z;
		tc[i]=std::make_tuple(x,y,z);
	}
	int l = 0; int r = 30;
	while(true){
		if (l==r-1){
			if(fit(l, hc, tc)){
				std::cout << l << '\n';
				return;
			}
			if(fit(r, hc, tc)){
				std::cout << r << '\n';
				return;
			}
			std::cout << "Impossible!\n";
			return;
		}
		if(fit((l+r)/2, hc, tc))
			r = (l+r)/2;
		else
			l = (l+r)/2;
	}
}

int main(){
	std::ios_base::sync_with_stdio(false);
	int t; std::cin >> t;
	while(t-->0){
		testcase();
	}
	return 0;
}
