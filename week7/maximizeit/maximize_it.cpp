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
	int p;
	std::cin >> p;
	while(p!=0){
		int a, b;
		std::cin >> a >> b;
		Solution s;

		if(p==1){
	  		Program lp (CGAL::SMALLER, true, 0, false, 0);
			const int X=0;
			const int Y=1;

			lp.set_a(X,0,1); lp.set_a(Y,0,1); lp.set_b(0, 4);
			lp.set_a(X,1,4); lp.set_a(Y,1,2); lp.set_b(1,a*b);
			lp.set_a(X,2,-1); lp.set_a(Y,2,1); lp.set_b(2,1);

			lp.set_c(X, a);
			lp.set_c(Y, -1*b);
			lp.set_c0(0);

			s = CGAL::solve_linear_program(lp, ET());
			assert(s.solves_linear_program(lp));
		} else {
	  		Program lp (CGAL::SMALLER, false, 0, true, 0);
			const int X=0;
			const int Y=1;
			const int Z=2;

			lp.set_a(X,0,-1); lp.set_a(Y,0,-1); lp.set_b(0, 4);
			lp.set_a(X,1,-4); lp.set_a(Y,1,-2); lp.set_a(Z, 1, -1); lp.set_b(1,a*b);
			lp.set_a(X,2,1); lp.set_a(Y,2,-1); lp.set_b(2,1);

			lp.set_c(X, a);
			lp.set_c(Y, b);
			lp.set_c(Z, 1);
			lp.set_c0(0);

			s = CGAL::solve_linear_program(lp, ET());
			assert(s.solves_linear_program(lp));
		}

		//std::cout << s << std::endl;
		if(s.is_optimal()){
			if(p==1){
				std::cout << -1*int(CGAL::to_double(s.objective_value())) << std::endl;
			}else{
				std::cout << int(CGAL::to_double(s.objective_value())) << std::endl;
			}
		}else if(s.is_infeasible()){
			std::cout << "no" << std::endl;
		}else{
			std::cout << "unbounded" << std::endl;
		}
		std::cin >> p;
	}
	return 0;
}
