//Implementation by marcobaga
//This solution achieves 0 points due to a small bug

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <boost/pending/disjoint_sets.hpp>
#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_2<K>			Vb;
typedef CGAL::Triangulation_face_base_with_info_2<int,K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Triangulation;

void testcase(int n){
	std::vector<K::Point_2> pts;
	for(int i=0; i<n; ++i){
		int x,y; std::cin >> x >> y;
		pts.push_back(K::Point_2(x,y));
	}
	Triangulation t;
	std::cout << "Read " << pts.size() << " points\n";
	t.insert(pts.begin(), pts.end());
	//assign a number to each face
	int count = 1;
	for(auto f = t.all_faces_begin(); f != t.all_faces_end(); ++f){
		if(t.is_infinite(f)){
			f->info() = 0;
		} else {
			f->info() = count; count++;
		}
	}
	std::cout << "Found " << count << " faces\n";
	//edge map
	std::vector<std::vector<std::pair<int, int>>> edges(count);
	for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
		auto segment = t.segment(e);
		Triangulation::Face_handle f1 = e->first;
		Triangulation::Face_handle f2 = f1->neighbor(e->second);
		int i1 = f1->info();
		int i2 = f2->info();
		edges[i1].push_back(std::make_pair(i2, segment.squared_length()));
		edges[i2].push_back(std::make_pair(i1, segment.squared_length()));
		std::cout << "Adding edge from " << i1 << " to " << i2 << " with weight " << segment.squared_length() << '\n';
	}

	std::vector<int> narrowest(count, 0);
	narrowest[0] = std::numeric_limits<int>::max();
	std::priority_queue<std::pair<int, int>> q;
	q.push(std::make_pair(narrowest[0], 0));
	while(!q.empty()){
		int curr_w = q.top().first;
		int curr = q.top().second;
		q.pop();
		for(auto u : edges[curr]){
			int edge_width = u.second;
			if(std::min(edge_width,curr_w)>narrowest[u.first]){
				narrowest[u.first] = std::min(curr_w,edge_width);
				q.push(std::make_pair(narrowest[u.first], u.first));
			}
		}
	}

	for(int i=0; i<count; ++i){
		std::cout << narrowest[i] << ' ';
	}
	std::cout << '\n';

	int m; std::cin >> m;
	for(int i=0; i<m; ++i){
		std::cout << "Processing query " << i << '\n';
		long x,y,d; std::cin >> x >> y >> d;
		K::Point_2 start = K::Point_2(x,y);
		Triangulation::Face_handle f = t.locate(start);
		Triangulation::Vertex_handle v = t.nearest_vertex(start);
		std::cout << "The closest infected is at " << v->point().x() << ' ' << v->point().y() << '\n';
		std::cout << "Query starts from face " << f->info() << '\n';
		if(CGAL::squared_distance(v->point(), start)>=d &&
			narrowest[f->info()]>=4*d){
			std::cout << 'y';
		} else {
			std::cout << 'n';
		}
	}
	std::cout << '\n';
	return;
}

int main(){
	std::ios_base::sync_with_stdio(false);
	int n; std::cin >> n;
	while(n!=0){
		testcase(n);
		std::cin >> n;
	}
	return 0;
}
