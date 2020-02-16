//Implementation by marcobaga
//This solution achieves 100 points

#include <vector>
#include <iostream>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef double IT;
typedef CGAL::Gmpz ET;
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;

void testcase(){
	//read input
	int n,m,c; std::cin >> n >> m >> c;
	std::vector<K::Point_2> warehouse;
	std::vector<int> supply(n);
	std::vector<double> alcohol(n);
	for(int i=0; i<n; ++i){
		int x,y; std::cin >> x >> y >> supply[i] >> alcohol[i];
		warehouse.push_back(K::Point_2(x,y));
	}
	std::vector<K::Point_2> stadium;
	std::vector<int> demand(m);
	std::vector<int> limit(m);
	for(int i=0; i<m;++i){
		int x,y; std::cin >> x >> y >> demand[i] >> limit[i];
		stadium.push_back(K::Point_2(x,y));
	}
	std::vector<std::vector<double>> revenue(n, std::vector<double>(m));
	for(int i=0; i<n; ++i){
		for(int j=0; j<m; ++j){
			std::cin >> revenue[i][j];
			revenue[i][j] = revenue[i][j] * 100;
		}
	}
	std::vector<K::Point_2> contour;
	std::vector<int> r(c);
	for(int i=0; i<c; ++i){
		int x,y; std::cin >> x >> y >> r[i];
		contour.push_back(K::Point_2(x,y));
	}

	//update revenue
	Triangulation t;
	t.insert(warehouse.begin(), warehouse.end());
	t.insert(stadium.begin(), stadium.end());
	for(int i=0; i<c; ++i){
		if(CGAL::squared_distance(contour[i], t.nearest_vertex(contour[i])->point()) < r[i]*r[i]){
			for(int w=0; w<n; ++w){
				bool is_in1 = CGAL::squared_distance(warehouse[w], contour[i]) > r[i]*r[i];
				for(int s=0; s<m; ++s){
					bool is_in2 = CGAL::squared_distance(stadium[s], contour[i]) > r[i]*r[i];
					if(is_in1!=is_in2){
						revenue[w][s] -=1;
					}
				}
			}
		}
	}
/*
	for(int i=0; i<n; ++i){
		for(int j=0; j<m; ++j){
			std::cout << revenue[i][j] << ' ';
		}
		std::cout << '\n';
	}
*/
	Program lp (CGAL::SMALLER, true, 0, false, 0);

	int count = 0;
	for(int i=0; i<n; ++i){
		//std::cout << "Equation " << count << '\n';
		for(int j=0; j<m; ++j){
			lp.set_a(i*m+j,count,1);
			//std::cout << "+" << i*m+j;
		}
		//std::cout << "<=" << supply[i] << '\n';
		lp.set_b(count, supply[i]);
		count++;
	}
	//each warehouse has limited supply

	for(int j=0; j<m; ++j){
		//std::cout << "Equation " << count << '\n';
		for(int i=0; i<n; ++i){
			//std::cout << "+" << i*m+j;
			lp.set_a(i*m+j, count, 1);
		}
		//std::cout << "<=" << demand[j] << '\n';
		lp.set_b(count, demand[j]);
		count++;
	}
	for(int j=0; j<m; ++j){
		//std::cout << "Equation " << count << '\n';
		for(int i=0; i<n; ++i){
			//std::cout << "-" << i*m+j;
			lp.set_a(i*m+j, count, -1);
		}
		//std::cout << "<=-" << demand[j] << '\n';
		lp.set_b(count, -demand[j]);
		count++;
	}
	//each stadium has an exact demand

	for(int j=0; j<m; ++j){
		//std::cout << "Equation " << count << '\n';
		for(int i=0; i<n; ++i){
			lp.set_a(i*m+j, count, alcohol[i]);
			//std::cout << "+" << alcohol[i] << "*" << i*m+j;
		}
		//std::cout << "<=" << limit[j] << '\n';
		lp.set_b(count, limit[j]*100);
		count++;
	}
	//upper limit of alcohol at each stadium

	//std::cout << "Minimize\n";
	for(int i=0; i<n; ++i){
		for(int j=0; j<m; ++j){
			//std::cout << "-" << revenue[i][j] << "*" << i*m+j;
			lp.set_c(i*m+j, -revenue[i][j]);
		}
	}
	//std::cout << '\n';
	//minimize negative profit

	Solution s = CGAL::solve_linear_program(lp, ET());
	assert(s.solves_linear_program(lp));
	if(s.is_infeasible()){
		std::cout << "RIOT!\n";
		return;
	}
	std::cout << (int)std::floor(CGAL::to_double(-1*s.objective_value()/100)) << '\n';
	return;
}

int main(){
	std::ios_base::sync_with_stdio(false);
	int t; std::cin >> t;
	while(t-- > 0){
		testcase();
	}
	return 0;
}
