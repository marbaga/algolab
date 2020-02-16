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
	int n, d;
	std::cin >> n;
	while(n!=0){

		std::cin >> d;
		Program lp (CGAL::SMALLER, false, 0, false, 0);

		for(int i=0; i<n; ++i){
			int norm=0;
			int a;
			for(int j=0; j<d; ++j){
				std::cin >> a;
				lp.set_a(j, i, a);
				norm+= a*a;
			}
			int b;
			std::cin >> b;
			norm = std::sqrt(norm);
			lp.set_a(d, i, norm);
			lp.set_b(i, b);
		}

		lp.set_a(d, n, -1);
		lp.set_b(n, 0);

		lp.set_c(d, -1);

		Solution s = CGAL::solve_linear_program(lp, ET());
		assert(s.solves_linear_program(lp));
		if(s.is_optimal()){
			std::cout << -1*int(CGAL::to_double(s.objective_value())) << std::endl;
		}else if(s.is_unbounded()){
			std::cout << "inf" << std::endl;
		}else{
			std::cout << "none" << std::endl;
		}

		std::cin >> n;
	}
	return 0;
}
