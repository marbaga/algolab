//Implementation by marcobaga
//This solution achieves 100 points

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef int IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Exact_predicates_inexact_constructions_kernel IK;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

int main(){
	int n, m;
	std::cin >> n >> m;
	while(n*m!=0){

		std::vector<int> min_amount(n, 0);
		std::vector<int> max_amount(n, 0);
		std::vector<int> price(m, 0);
		std::vector<std::vector<int>> amounts (m, std::vector<int>(n, 0));
		for(int i=0; i<n; ++i){
			std::cin >> min_amount[i] >> max_amount[i];
		}
		for(int i=0; i<m; ++i){
			std::cin >> price[i];
			for(int j=0; j<n; ++j){
				std::cin >> amounts[i][j];
			}
		}

		Program lp (CGAL::SMALLER, true, 0, false, 0);
		for(int i=0; i<n; ++i){
			for(int j=0; j<m; ++j){
				lp.set_a(j, i, amounts[j][i]);
				lp.set_a(j, n+i, -1*amounts[j][i]);
			}
			lp.set_b(i, max_amount[i]);
			lp.set_b(n+i, -1*min_amount[i]);
		}
		for(int i=0; i<m; ++i){
			lp.set_c(i, price[i]);
		}

		Solution s = CGAL::solve_linear_program(lp, ET());
		assert(s.solves_linear_program(lp));
		//std::cout << s;
		if(s.is_optimal()){
			std::cout << int(CGAL::to_double(s.objective_value())) << std::endl;
		}else{
			std::cout << "No such diet." << std::endl;
		}
		std::cin >> n >> m;
	}
	return 0;
}
