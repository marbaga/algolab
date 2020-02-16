//Implementation by marcobaga
//This solution achieves 0//Implementation by marcobaga
//This solution achieves 100 points

 points

#include <iostream>
#include <boost/disjoint_sets.hpp>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Finite_faces_iterator  Face_iterator;
typedef boost::disjoint_sets disj_sets;

void testcase(){
	int n,m,r; std::cin >> n >> m >> r;
	r = r*r;
	for(int i=0; i<n; ++i){
		int x,y; std::cin >> x >> y;
		pts.push_back(K::Point_2(x,y));
	}
	Triangulation t;
	t.insert(pts.begin(), pts.end());

	disj_sets<K::Point_2> dsets (n);
	for (Edge_iterator e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e){
		for(int i=1; i<3; ++i){
			Triangulation::Vertex_handle v = e->first->vertex((e.second+i)%3);
			int count = 0;
			Triangulation::Edge_circulator c = t.incident_edges(v);
			do{
				if(t.is_infinite(c)){
					continue;
				}
				Triangulation::Vertex_handle v1 = e->first->vertex((e.second+1)%3);
				Triangulation::Vertex_handle v2 = e->first->vertex((e.second+2)%3);
				if(CGAL::squared_distance(v1->point(), v2->point())<=r){
					count++;
					dsets.union_set(v1->point(),v2->point());
				}
			} while(++c != t.incident_edges(v));
			if (count>1){
				for(i=0; i<m; ++i){
					int xa,ya,xb,yb; std::cin >> xa >> ya >> xb >> yb;
					std::cout << 'n';
				}
				std::cout << '\n';
				return;
			}
		}
	}

	for(int i=0; i<m; ++i){
		int xa,ya,xb,yb; std::cin >> xa >> ya >> xb >> yb;
		K::Point_2 a (xa, ya);
		K::Point_2 b (xb, yb);
		if(CGAL::squared_distance(a,b) <= r){
			std::cout << '\n';
		}else{
			K::Point_2 start = t.nearest_vertex(a)->point();
			K::Point_2 end = t.nearest_vertex(b)->point();
			if(dsets.find_set(start) == dsets.find_set(end)){
				std::cout << 'y';
			}else{
				std::cout << 'n';
			}
		}
		std::cout << '\n';
	}
	return;
}

int main(){
	std::ios_base::sync_with_stdio(false);
	int t; std::cin >> t;
	while(t-->0){
		testcase();
	{
	return 0;
}
