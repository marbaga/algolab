//Implementation by marcobaga
//This solution achieves 100 points

#include<iostream>
#include<vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef CGAL::Gmpq IT;
typedef CGAL::Gmpq ET;
//else try gmpq or casting
typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Finite_faces_iterator  Face_iterator;
typedef Triangulation::Vertex_handle Vertex_handle;

void testcase(){
	int a,s,b,e; std::cin >> a >> s >> b >> e;
	std::vector<K::Point_2> ast_p(a);
	std::vector<int> ast_d(a);
	for(int i=0; i<a; ++i){
		int x,y,d; std::cin >> x >> y >> d;
		ast_p[i] = K::Point_2(x,y);
		ast_d[i] = d;
		//std::cout << "Read asteroid " << ast_p[i].x() << ' ' << ast_p[i].y() << '\n';
	}
	std::vector<K::Point_2> shoot(s);
	for(int i=0; i<s; ++i){
		int x,y; std::cin >> x >> y;
		shoot[i] = K::Point_2(x,y);
		//std::cout << "Read shoot " << shoot[i].x() << ' ' << shoot[i].y() << '\n';
	}
	std::vector<K::Point_2> bh(b);
	for(int i=0; i<b; ++i){
		int x,y; std::cin >> x >> y;
		bh[i] = K::Point_2(x,y);
		//std::cout << "Read bh " << bh[i].x() << ' ' << bh[i].y() << '\n';
	}
	Triangulation t;
	t.insert(bh.begin(), bh.end());
	std::vector<long> r(s);
	if(b>0){
		for(int i=0; i<s; ++i){
			//std::cout << "Finding closest bh to " << shoot[i].x() << ' ' << shoot[i].y() << '\n';
	  		Vertex_handle nearest_v = t.nearest_vertex(shoot[i]);
	  		K::Point_2 nearest = nearest_v->point();
			r[i] = CGAL::squared_distance(t.nearest_vertex(shoot[i])->point(), shoot[i]);
			//std::cout << "Nearest is " << nearest.x() << ' ' << nearest.y() << " at distance " << r[i] << "\n";
		}
	}

	Program lp (CGAL::SMALLER, true, 0, false, 0);
	for(int i=0; i<a; ++i){
		for(int j=0; j<s; ++j){
			long dist = CGAL::squared_distance(shoot[j], ast_p[i]);
			//std::cout << dist << ' ' << r[j] << '\n';
			if(r[j] >= dist||b==0){
				IT coeff = IT(-1)/IT(std::max((long)1, dist));
				//std::cout << coeff << '\n';
				lp.set_a(j, i, coeff);
			}
		}
		lp.set_b(i, -1*ast_d[i]);
	}
	for(int i=0; i<s; ++i){
		lp.set_a(i, a, 1);
		lp.set_c(i,1);
	}
	lp.set_b(a, e);

	Solution sol = CGAL::solve_linear_program(lp, ET());
	assert(sol.solves_linear_program(lp));

	if(!sol.is_infeasible())
		std::cout << "y\n";
	else
		std::cout << "n\n";
	return;
}

int main(){
	std::ios_base::sync_with_stdio(false);
	int t; std::cin >> t;
	while(t-- >0)
		testcase();
	return 0;
}
