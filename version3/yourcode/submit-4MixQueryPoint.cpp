#include "submit-4MixQueryPoint.h"

void SetEnvironmentFromMixQueryPoint() {
}

std::vector<int> QueryPointFromMixQueryPoint(double x, double y) {
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

void AddPolygonFromMixQueryPoint(int id, int n, std::vector<std::pair<double, double> > &polygon) {
    GridSet p_gs;
    GridSetup(polygon, n, 20, &p_gs);
    polygon_grid[id] = p_gs;
    polygon_ids.push_back(id);
    polygon_is_deleted[id] = false;
}

void DeletePolygonFromMixQueryPoint(int id) {
    polygon_is_deleted[id] = true;
}
