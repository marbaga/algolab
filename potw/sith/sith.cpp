//Implementation by marcobaga
//This solution achieves 100 points

#include <vector>
#include <iostream>
#include <boost/pending/disjoint_sets.hpp>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef boost::disjoint_sets_with_storage<> uf_t;
typedef CGAL::Triangulation_vertex_base_with_info_2<int,K>   Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Triangulation;

void testcase(){
	long n, r; std::cin >> n >> r;
	std::vector<std::pair<K::Point_2, int>> planet;
	for(int i=0; i<n; i++){
		long x,y; std::cin >> x >> y;
		planet.emplace_back(K::Point_2(x,y), i);
	}

	Triangulation t;
	uf_t uf(n);
	long max=0;
	for(int i=n-1; i>=0; --i){
		t.insert(planet.begin()+i, planet.begin()+i+1);
		Triangulation::Vertex_handle vh = t.nearest_vertex(planet[i].first);
		//std::cout << vh->info() << '\n';
		//std::cout << t.is_infinite(vh) <<  ' ' << t.number_of_vertices() << '\n';
		Triangulation::Edge_circulator c = t.incident_edges(vh);
		if(t.number_of_vertices()>1){
			do {
				//std::cout << "hi\n";
				if (t.is_infinite(c)) {
					continue;
				} else {
					Triangulation::Vertex_handle v1 = c->first->vertex((c->second + 1) % 3);
					Triangulation::Vertex_handle v2 = c->first->vertex((c->second + 2) % 3);
					if(CGAL::squared_distance(v1->point(), v2->point())<=r*r){
						uf.union_set(v1->info(), v2->info());
					}
				}
			} while (++c != t.incident_edges(vh));
		}

		std::vector<long> sizes(n, 0);
		for(int j=i; j<n; ++j){
			long ind = uf.find_set(j);
			sizes[ind]++;
			max = std::max(max, sizes[ind]);
		}
		if(max>=i){
			std::cout << i << '\n';
			return;
		}
	}
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
