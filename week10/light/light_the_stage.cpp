//Implementation by marcobaga
//This solution achieves 80 points

#include <iostream>
#include <vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;
typedef Triangulation::Vertex_handle Vertex_handle;

void find_survivors(int tmp, std::vector<K::Point_2> pts, std::vector<long> x, std::vector<long> y, std::vector<long> r, long h){

	if(tmp == 0)
		return;
	std::vector<K::Point_2> lights;
	for(int i=0; i<tmp; ++i){
		lights.push_back(pts[i]);
	}
	Triangulation t;
	t.insert(lights.begin(), lights.end());
	for(int i=0; i<x.size(); ++i){
		K::Point_2 curr = K::Point_2(x[i], y[i]);
		//std::cout << "Examining " << curr.x() << ',' << curr.y() << '\n';
		Vertex_handle nearest_v = t.nearest_vertex(curr);
		K::Point_2 nearest = nearest_v->point();
		if(CGAL::squared_distance(curr, nearest)>= (h+r[i])*(h+r[i]))
			std::cout << i << ' ';
	}
	std::cout << '\n';
}

bool survivors(int tmp, std::vector<K::Point_2> pts, std::vector<long> x, std::vector<long> y, std::vector<long> r, long h){ //how many survive after tmp lights shine

	if(tmp == 0)
		return true;
	std::vector<K::Point_2> lights;
	for(int i=0; i<tmp; ++i){
		lights.push_back(pts[i]);
	}
	Triangulation t;
	t.insert(lights.begin(), lights.end());
	for(int i=0; i<x.size(); ++i){
		K::Point_2 curr = K::Point_2(x[i], y[i]);
		//std::cout << "Examining " << curr.x() << ',' << curr.y() << '\n';
		Vertex_handle nearest_v = t.nearest_vertex(curr);
		K::Point_2 nearest = nearest_v->point();
		if(CGAL::squared_distance(curr, nearest)>= (h+r[i])*(h+r[i]))
			return true;
	}
	return false;
}


void testcase(){
	int m,n; std::cin >> m >>n;
	std::vector<long> x(m);
	std::vector<long> y(m);
	std::vector<long> r(m);
	for(int i=0; i<m; ++i){
		std::cin >>x[i]>>y[i]>>r[i];
	}
	std::vector<K::Point_2> pts;
	long h; std::cin >> h;
	for(int i=0; i<n; ++i){
		long xt,yt; std::cin >> xt >> yt;
		pts.push_back(K::Point_2(xt, yt));
	}

	int ll=0;
	int lr=n;
	while(ll<lr-1){
		int tmp = ll+(lr-ll)/2;
		if(survivors(tmp,pts,x,y,r,h))
			ll=tmp;
		else
			lr=tmp;
	}
	if(survivors(lr,pts,x,y,r,h))
		find_survivors(lr,pts,x,y,r,h);
	else
		find_survivors(ll,pts,x,y,r,h);
	return;
}

int main(){
	std::ios_base::sync_with_stdio(false);
	int t; std::cin >> t;
	while(t-->0)
		testcase();
	return 0;
}
