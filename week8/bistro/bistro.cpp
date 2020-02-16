//Implementation by marcobaga
//This solution achieves 100 points

#include <iostream>
#include <vector>
#include <algorithm>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Finite_faces_iterator  Face_iterator;

void testcase(int n){
	std::vector<K::Point_2> existing(n);
	for(int i=0; i<n; ++i){
		int x,y; std::cin>>x>>y;
		existing[i]=K::Point_2(x,y);
	}
	Triangulation t;
	t.insert(existing.begin(), existing.end());
	int m; std::cin >> m;
	for(int i=0; i<m; ++i){
		int x,y; std::cin>>x>>y;
		K::Point_2 tmp(x,y);
		K::FT res = CGAL::squared_distance(tmp, t.nearest_vertex(tmp)->point());
		std::cout << (long)CGAL::to_double(res) << '\n';
	}
	return;
}

int main(){
	std::ios_base::sync_with_stdio(false);
	int n;
	while(std::cin >> n && n > 0){
		testcase(n);
	}
	return 0;
}
