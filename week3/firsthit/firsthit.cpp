//Implementation by marcobaga
//This solution achieves 100 points

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <math.h>
#include <vector>
#include <algorithm>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef std::result_of<K::Intersect_2(K::Ray_2, K::Segment_2)>::type IT;
typedef K::Point_2 P;
typedef K::Segment_2 S;

double floor_to_double(const K::FT& x) {
	double a = std::floor(CGAL::to_double(x));
	while (a > x)
		a -= 1;
	while (a+1 <= x)
		a += 1;
	return a;
}

void shorten_segment(K::Segment_2& s, const IT& o){
	if(const P*p = boost::get<P>(&*o))
		s = S(s.source(), *p);
	else if (const S* t = boost::get<S>(&*o))
		if(CGAL::collinear_are_ordered_along_line(s.source(), t->source(), t->target()))
			s = S(s.source(), t->source());
		else
			s = S(s.source(), t->target());	
}

void testcase(std::size_t n){
	long x,y,a,b; std::cin >> x >> y >> a >> b;
    P p(x,y), q(a,b);
    K::Ray_2 r(p,q);
	std::vector<S> segs;
	segs.reserve(n);

	for(std::size_t i=0; i<n; ++i){
		std::cin >> x >> y >> a >> b;
		segs.push_back(S(P(x,y),P(a,b)));
	}
	std::random_shuffle(segs.begin(), segs.end());
	S rc(r.source(), r.point(1));
	std::size_t i=0;
	for(; i<n; ++i){
		if(CGAL::do_intersect(segs[i],r)){
			shorten_segment(rc, CGAL::intersection(segs[i], r));
			break;
		}
	}
	if(i==n){
		std::cout << "no\n";
		return;
	}
	while(++i < n){
		if(CGAL::do_intersect(segs[i], rc)){
			shorten_segment(rc, CGAL::intersection(segs[i], r));
		}
	}
	std::cout << floor_to_double(rc.target().x()) << ' ' << floor_to_double(rc.target().y()) << '\n';\
	return;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);
    std::size_t t;
    std::cin >> t;
    while(t!=0){
		testcase(t);
		std::cin >> t;
	}
	return 0;
}
