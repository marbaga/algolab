//Implementation by marcobaga
//This solution achieves 20 points

#include <vector>
#include <iostream>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef CGAL::Gmpz IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

void testcase(){
	int xs,ys,n; std::cin >> xs >> ys >> n;
	const int xe = 0;
	const int ye = 1;
	const int t = 2;
	Program lp (CGAL::SMALLER, false, 0, false, 0); 
	for(int i=0; i<n; ++i){
		int a, c, b, v;
		std::cin >> a >> b >> c >> v;
		//std::cout << "a " << a << " b " << b << " c " << c << " v " << v << '\n';
		int coeff = (a*xs+b*ys+c);
		if(coeff >=0){
			lp.set_a(xe, i, -1*a);
			lp.set_a(ye, i, -1*b);
			lp.set_b(i, c);
		}else{
			lp.set_a(xe, i, a);
			lp.set_a(ye, i, b);
			lp.set_b(i, -1*c);
		}
		lp.set_a(t, i+n, std::sqrt(a*a+b*b)*v);
		if(coeff >= 0){
			lp.set_a(xe, i+n, -1*a);
			lp.set_a(ye, i+n, -1*b);
			lp.set_b(i+n, c);
		} else {
			lp.set_a(xe, i+n, a);
			lp.set_a(ye, i+n, b);
			lp.set_b(i+n, -1*c);
		}
	}
	lp.set_l(t, 0);
	lp.set_c(t, -1);

	Solution s = CGAL::solve_linear_program(lp, ET());
	assert (s.solves_linear_program(lp));
	//std::cout << s << '\n';
	std::cout << std::floor(CGAL::to_double(-1*s.objective_value())) << '\n';
	return;
}

int main(){
	std::ios_base::sync_with_stdio(false);
	int t; std::cin >> t;
	while(t-->0){
		testcase();
	}
	return 0;
}
