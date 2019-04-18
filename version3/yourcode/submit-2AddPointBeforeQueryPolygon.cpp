#include "submit-2AddPointBeforeQueryPolygon.h"
#include <iostream>
void SetEnvironmentFromAddPointBeforeQueryPolygon() {
}

void AddPointFromAddPointBeforeQueryPolygon(int id, double x, double y) {
    points.push_back(Point(x, y, id));
    point_ids.push_back(id);
}

std::vector<int> QueryPolygonFromAddPointBeforeQueryPolygon(int n, std::vector<std::pair<double, double> > polygon) {
    std::vector<int> hit_point_ids;
    double a_minX = MX, a_maxX = MIN;
    for(int i = 0; i < n; i++){
        double x = polygon[i].first;
        a_minX = a_minX < x ? a_minX : x;
        a_maxX = a_maxX > x ? a_maxX : x;
    }
    GridSet p_gs;
    GridSetup(polygon, n, 20, &p_gs);
    std::sort(points.begin(), points.end(), [](Point a, Point b){
        return a.x == b.x ? a.y < b.y : a.x < b.x;
    });//ascending order
    auto it = std::lower_bound(points.begin(), points.end(), a_minX, [](Point a, double c){
       return  a.x < c;
    });
    if(it != points.end()){
        for(auto i = it; i->x < a_maxX && i != points.end(); i++){
            if(GridTest(&p_gs, i->x, i->y))
                hit_point_ids.push_back(i->id);
        }
    }
    GridCleanup(&p_gs);
    return hit_point_ids;
}
