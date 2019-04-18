#include "submit-6MixQuery.h"

void SetEnvironmentFromMixQuery() {
}

void AddPointFromMixQuery(int id, double x, double y) {
    points.push_back(Point(x, y, id));
    point_ids.push_back(id);
    point_is_deleted[id] = false;
}

void DeletePointFromMixQuery(int id) {
    point_is_deleted[id] = true;
}

std::vector<int> QueryPointFromMixQuery(double x, double y) {
    hit_polygon_ids.clear();
    int num = polygon_ids.size();
    for(int i = 0; i < num; i++){
        int id = polygon_ids[i];
        if(polygon_is_deleted[id]) continue;
        GridSet tmp = polygon_grid[id];
        if(GridTest(&tmp, x, y))
            hit_polygon_ids.push_back(id);
    }
    return hit_polygon_ids;
}

void AddPolygonFromMixQuery(int id, int n, std::vector<std::pair<double, double>> &polygon) {
    GridSet p_gs;
    GridSetup(polygon, n, 20, &p_gs);
    polygon_grid[id] = p_gs;
    polygon_ids.push_back(id);
    polygon_is_deleted[id] = false;
}

void DeletePolygonFromMixQuery(int id) {
    polygon_is_deleted[id] = true;
}
std::vector<int> QueryPolygonFromMixQuery(int n, std::vector<std::pair<double, double> >& polygon) {
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
            if(point_is_deleted[i->id]) continue;
            if(GridTest(&p_gs, i->x, i->y))
                hit_point_ids.push_back(i->id);
        }
    }
    GridCleanup(&p_gs);
    return hit_point_ids;
}

