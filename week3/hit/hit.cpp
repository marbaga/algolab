#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

int main(){

    std::ios_base::sync_with_stdio(false);
    int n;
    std::cin >> n;
    while(n!=0){
        double x,y,a,b;
        std::cin >> x;
        std::cin >> y;
        std::cin >> a;
        std::cin >> b;
        //std::cout << x << ' ' << y << ' ' << a << ' ' << b << std::endl;
        K::Point_2 p(x,y), q(a,b);
        K::Ray_2 l(p,q);
        bool exist = false;
        for(int i=0; i<n; ++i){
            double r,s,t,u;
            std::cin >> r;
            std::cin >> s;
            std::cin >> t;
            std::cin >> u;
            if(!exist){
                K::Point_2 j(r,s), k(t,u);
                K::Segment_2 seg(j,k);
                //std::cout << r << ' ' << s << ' ' << t << ' ' << u << std::endl;
                if(CGAL::do_intersect(l, seg)){
                    exist = true;
                }
            }
        }
        if(exist){
            std::cout << "yes" << std::endl;
        } else {
            std::cout << "no" << std::endl;
        }
        //std::cout << "loop" << n << std::endl;
        std::cin >> n;
    }
    return 0;
}