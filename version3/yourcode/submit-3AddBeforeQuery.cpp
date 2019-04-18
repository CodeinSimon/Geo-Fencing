#include "submit-3AddBeforeQuery.h"

void SetEnvironmentFromAddBeforeQuery(){
}

void AddPointFromAddBeforeQuery(int id, double x, double y) {
    points.push_back(Point(x, y, id));
    point_ids.push_back(id);
}

void AddPolygonFromAddBeforeQuery(int id, int n, std::vector<std::pair<double, double> > &polygon) {
    GridSet p_gs;
    GridSetup(polygon, n, 20, &p_gs);
    polygon_grid[id] = p_gs;
    polygon_ids.push_back(id);
}

std::vector<int> QueryPointFromAddBeforeQuery(double x, double y) {
    hit_polygon_ids.clear();
    int num = polygon_ids.size();
    for(int i = 0; i < num; i++){
        int id = polygon_ids[i];
        GridSet tmp = polygon_grid[id];
        if(GridTest(&tmp, x, y))
            hit_polygon_ids.push_back(id);
    }
    return hit_polygon_ids;
}


std::vector<int> QueryPolygonFromAddBeforeQuery(int n, std::vector<std::pair<double, double> > &polygon) {
    std::vector<int> hit_point_ids;
    std::sort(points.begin(), points.end(), [](Point a, Point b){
        return a.x == b.x ? a.y < b.y : a.x < b.x;
    });//ascending order
    double a_minX = MX, a_maxX = MIN;
    for(int i = 0; i < n; i++){
        double x = polygon[i].first;
        a_minX = a_minX < x ? a_minX : x;
        a_maxX = a_maxX > x ? a_maxX : x;
    }
    GridSet p_gs;
    GridSetup(polygon, n, 20, &p_gs);
    //int num = point_ids.size();
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