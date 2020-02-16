//Implementation by marcobaga
//This solution achieves 100 points

#include<iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <boost/pending/disjoint_sets.hpp>
#include <vector>
#include <tuple>
#include <algorithm>
#include <iostream>
#include <boost/pending/disjoint_sets.hpp>

typedef CGAL::Exact_predicates_inexact_constructions_kernel	K;
typedef CGAL::Triangulation_vertex_base_with_info_2<int,K>	Vb;
typedef CGAL::Triangulation_face_base_2<K>			Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>		Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>			Triangulation;
typedef Triangulation::Edge_iterator				Edge_iterator;
typedef boost::disjoint_sets_with_storage<>                  ds;

void testcase(){
	long n,m,p; std::cin >> n >> m >> p;
	std::vector<std::pair<K::Point_2, int>> j(n);
	for(int i=0; i<n; ++i){
		int x,y; std::cin >> x >> y;
		j[i] = std::make_pair(K::Point_2(x,y), i);
		//std::cout << "Read point " << x << ',' << y << " with id " << i << '\n';
	}
	Triangulation t;
	t.insert(j.begin(), j.end());
	typedef std::tuple<long, int, int> Edge;
	std::vector<Edge> edges;
	for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
		long length = t.segment(e).squared_length();
		int source = e->first->vertex((e->second+1)%3)->info();
		int target = e->first->vertex((e->second+2)%3)->info();
		edges.push_back(std::make_tuple(length, source, target));
	}
	std::sort(edges.begin(), edges.end());
	/*std::cout << "Sorted edges: \n";
	for(int i=0; i<edges.size(); ++i){
		std::cout << "from " << std::get<1>(edges[i]) << " to " << std::get<2>(edges[i]) << " with length " << std::get<0>(edges[i]) << '\n';
	}*/
	ds up(n), umin(n), umax(n);
	int i_min = 0;
	long pow_con_min = 0;
	int i_max = 0;
	long pow_con_max = 0;
	for(int i=0; i<edges.size(); ++i){
		if(std::get<0>(edges[i])<=p){
			up.union_set(std::get<1>(edges[i]), std::get<2>(edges[i]));
			//std::cout << "Joining " << std::get<1>(edges[i]) << " and " << std::get<2>(edges[i]) << " with current power consumption\n";
		}
	}

	for(int i=0; i<m; ++i){
		long x0,y0,x1,y1; std::cin >> x0 >> y0 >> x1 >> y1;
		//std::cout << "Considering query " << x0 <<','<<y0 << " to " <<x1<<','<<y1<<'\n';
		K::Point_2 start_p = K::Point_2(x0,y0);
		K::Point_2 end_p = K::Point_2(x1,y1);
		Triangulation::Vertex_handle start_v = t.nearest_vertex(start_p);
		Triangulation::Vertex_handle end_v = t.nearest_vertex(end_p);
		K::Point_2 start = start_v->point();
		K::Point_2 end = end_v->point();
		//std::cout << "Nearest vertex to start: " << start_v->info() << '\n';
		//std::cout << "Nearest vertex to end: " << end_v->info() << '\n';
		if(CGAL::squared_distance(start,start_p)*4<=p && CGAL::squared_distance(end,end_p)*4<=p && up.find_set(start_v->info())==up.find_set(end_v->info())){
			std::cout << 'y';
			//std::cout << " Feasible!!\n";
			pow_con_min = std::max(pow_con_min, (long)CGAL::to_double(CGAL::squared_distance(start,start_p)*4));
			pow_con_min = std::max(pow_con_min, (long)CGAL::to_double(CGAL::squared_distance(end,end_p)*4));
			while(umin.find_set(start_v->info())!=umin.find_set(end_v->info())){
				umin.union_set(std::get<1>(edges[i_min]), std::get<2>(edges[i_min]));
				pow_con_min = std::max(pow_con_min, std::get<0>(edges[i_min]));
				i_min++;
				//std::cout << "Adding " << std::get<1>(edges[i_min]) << ' ' << std::get<2>(edges[i_min]) << "to set of edges needed for minimal missions\n";
			}
			//std::cout << "Min_pow_con updated to " << pow_con_min << '\n';
		} else {
			std::cout << 'n';
			//std::cout << " Not feasible\n";
		}
		pow_con_max = std::max(pow_con_max, (long)CGAL::to_double(CGAL::squared_distance(start,start_p)*4));
		pow_con_max = std::max(pow_con_max, (long)CGAL::to_double(CGAL::squared_distance(end,end_p)*4));
		while(umax.find_set(start_v->info())!=umax.find_set(end_v->info())){
			umax.union_set(std::get<1>(edges[i_max]), std::get<2>(edges[i_max]));
			pow_con_max = std::max(pow_con_max, std::get<0>(edges[i_max]));
			i_max++;
			//std::cout << "Adding " << std::get<1>(edges[i_max]) << ' ' << std::get<2>(edges[i_max]) << "to set of edges needed for all missions\n";
		}
		//std::cout << "Max_pow_con updated to " << pow_con_max << '\n';
	}
	std::cout << '\n' << pow_con_max << '\n' << pow_con_min << '\n';
	return;
}

int main(){
	std::ios_base::sync_with_stdio(false);
	int t; std::cin >> t;
	while(t-- > 0)
		testcase();
	return 0;
}
