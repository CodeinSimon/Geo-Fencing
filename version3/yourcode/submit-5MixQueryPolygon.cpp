//
// Created by zhang on 18-12-4.
// Filled by Simon Nie on 18-12-13
//

#include "submit-5MixQueryPolygon.h"

void SetEnvironmentFromMixQueryPolygon() {
}

void AddPointFromMixQueryPolygon(int id, double x, double y) {
    points.push_back(Point(x, y, id));
    point_ids.push_back(id);
    point_is_deleted[id] = false;
}

void DeletePointFromMixQueryPolygon(int id) {
    point_is_deleted[id] = true;
}

std::vector<int> QueryPolygonFromMixQueryPolygon(int n, std::vector<std::pair<double, double> > &polygon) {
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
        for(auto i = it; i != points.end() && i->x < a_maxX; i++){
            if(point_is_deleted[i->id]) continue;
            if(GridTest(&p_gs, i->x, i->y))
                hit_point_ids.push_back(i->id);
        }
    }
    GridCleanup(&p_gs);
    return hit_point_ids;
}
