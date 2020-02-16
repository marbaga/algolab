//Implementation by marcobaga
//This solution achieves 100 points

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
#include <cmath>
#include <limits>

typedef long IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

int main(){
	std::ios_base::sync_with_stdio(false);
	int t;
	std::cin >> t;
	while(t>0){

		long n, m, h, w;
		std::cin >> n >> m >> h >> w;

		//reading nail positions
		std::vector<long> x_n(n), y_n(n), x_m(m), y_m(m);
		for(int i=0; i<n; ++i){			std::cin >> x_n[i] >> y_n[i];		}
		for(int i=0; i<m; ++i){			std::cin >> x_m[i] >> y_m[i];		}

		//setting lower bound for coefficients (>=1)
		Program lp (CGAL::SMALLER, true, 1, false, 0);

		//setting (-1*perimeter) as the objective function to minimize
		for(int i=0; i<n; ++i){
			lp.set_c(i, -2*(h+w));
		}

		int n_eq = 0;	//counting the constraints
		for(int i=0; i<n; ++i){

			bool found_x = false, found_y = false;
			long min_dx = std::numeric_limits<long>::max();
			long min_dy = std::numeric_limits<long>::max();

			//computing the two most strict restriction caused by old posters
			for(int j=0; j<m; ++j){
				long dx = std::abs(x_m[j]-x_n[i]);
				long dy = std::abs(y_m[j]-y_n[i]);
				if(dy*w > h*dx){
					if(dy < min_dy){
						min_dy = dy;
						found_y = true;
					}
				} else {
					if(dx < min_dx){
						min_dx = dx;
						found_x = true;
					}
				}
			}
			if(found_x){
				lp.set_a(i, n_eq, w); lp.set_b(n_eq, 2*min_dx - w);
				n_eq++;
			}
			if(found_y){
				lp.set_a(i, n_eq, h); lp.set_b(n_eq, 2*min_dy - h);
				n_eq++;
			}

			//forcing each pair of the new posters not to overlap
			for(int j=i+1; j<n; ++j){
				long dx = std::abs(x_n[j]-x_n[i]);
				long dy = std::abs(y_n[j]-y_n[i]);
				if(dx*h < dy*w){
					lp.set_a(i, n_eq, h); lp.set_a(j, n_eq, h); lp.set_b(n_eq, 2*dy);
				} else {
					lp.set_a(i, n_eq, w); lp.set_a(j, n_eq, w); lp.set_b(n_eq, 2*dx);
				}
				n_eq++;
			}
		}

		//solving and casting
		Solution s = CGAL::solve_linear_program(lp, ET());
		double sol = -std::floor(CGAL::to_double(s.objective_value()));
		std::cout << std::lround(sol) << std::endl;

		t--;
	}
	return 0;
}
