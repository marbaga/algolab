//Implementation by marcobaga
//This solution achieves 100 points

#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
#include <vector>

typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef K::Point_2 P;
typedef K::Segment_2 S;
typedef CGAL::Min_circle_2_traits_2<K> Traits;
typedef CGAL::Min_circle_2<Traits> Min_circle;

int main(){

    std::ios_base::sync_with_stdio(false);
    int n;
    std::cin >> n;
    std::cout << std::fixed << std::setprecision(0);
    CGAL::set_pretty_mode( std::cout);
    while(n!=0){

        double x,y;
        std::vector<P> citizens(n);
        for(int i=0; i<n; ++i){
            std::cin >> x >> y;
            citizens.at(i) = P(x,y);
        }
        Min_circle mc(citizens.begin(), citizens.end() ,true);
	
        Traits::Circle c = mc.circle();
	K::FT radius = c.squared_radius();
	//std::cout << "First squared radius: " << CGAL::to_double(radius) << std::endl;

	P last;

	for(int i=0; i<mc.number_of_support_points(); ++i){		
		if(i!=0){
			citizens.push_back(last);
		}
		P curr = mc.support_point(i);
		//std::cout << "Considering support point " << curr << std::endl;
		std::vector<P>::iterator it = std::find(citizens.begin(), citizens.end(), curr);
		//std::cout << "Found support point " << *it << std::endl;
		last = *it;
		citizens.erase(it);

		Min_circle mc2(citizens.begin(), citizens.end() ,true);

		Traits::Circle c2 = mc2.circle();
		K::FT radius2 = CGAL::sqrt(c2.squared_radius());
		//std::cout << "New circle radius is " << CGAL::to_double(radius2) << std::endl;
		
		if(radius2<radius){
			radius=radius2;
		}
	}

	double ans = std::ceil(CGAL::to_double(radius));
        while(ans>=radius+1) ans -= 1;
        while(ans<radius) ans += 1;

        std::cout << ans << std::endl;

        std::cin >> n;
    }
    return 0;
}
