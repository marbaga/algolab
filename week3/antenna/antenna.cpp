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
    while(n!=0){

        double x,y;
        std::vector<P> citizens(n);
        for(int i=0; i<n; ++i){
            std::cin >> x >> y;
            citizens.at(i) = P(x,y);
        }
        Min_circle mc(citizens.begin(), citizens.end() ,true);
        Traits::Circle c = mc.circle();
        K::FT radius = CGAL::sqrt(c.squared_radius());
        double ans = std::ceil(CGAL::to_double(radius));
        while(ans>=radius+1) ans -= 1;
        while(ans<radius) ans += 1;
        std::cout << ans << std::endl;

        std::cin >> n;
    }
    return 0;
}
