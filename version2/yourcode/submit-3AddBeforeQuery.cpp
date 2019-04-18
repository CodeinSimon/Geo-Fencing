#include "submit-3AddBeforeQuery.h"

void SetEnvironmentFromAddBeforeQuery() {
    polygon_set.clear();
    points_set.clear();
}

inline bool SearchCallback3(int id) {
    hit_polygon_ids.push_back(id);
    return true;
}

void AddPointFromAddBeforeQuery(int id, double x, double y) {
    double a[2] = {x, y};
    pointTree=Insert(pointTree, a, id);
    points_set[id] = std::make_pair(x, y);

}

void AddPolygonFromAddBeforeQuery(int id, int n, std::vector<std::pair<double, double> > &polygon) {
    double a_minX = MX, a_minY = MX, a_maxX = MIN, a_maxY = MIN, tmpx, tmpy;
    for (int i = 0; i < n; i++) {
        tmpx = polygon[i].first;
        tmpy = polygon[i].second;
        a_minX = a_minX < tmpx ? a_minX : tmpx;
        a_minY = a_minY < tmpy ? a_minY : tmpy;
        a_maxX = a_maxX > tmpx ? a_maxX : tmpx;
        a_maxY = a_maxY > tmpy ? a_maxY : tmpy;
    }
    Rect tmpRect(a_minX, a_minY, a_maxX, a_maxY);
    polygonTree.Insert(tmpRect.min, tmpRect.max, id);
    polygon_set[id] = polygon;
    return;
}

std::vector<int> QueryPointFromAddBeforeQuery(double x, double y){
    hit_polygon_ids.clear();
    std::vector<int> polygon_ids;
    Rect pointRect(x, y, x, y);
    int nHits;
    nHits = polygonTree.Search(pointRect.min, pointRect.max, SearchCallback3);
    for (int i = 0; i < nHits; i++) {
        int tmpId = hit_polygon_ids[i];
        std::vector<std::pair<double, double> >& a_polygon = polygon_set[tmpId];
        if(pointInPolygon(x, y, a_polygon))
            polygon_ids.push_back(tmpId);
    }
    return polygon_ids;
}

inline bool SearchCallback4(int id) {
    hit_point_ids.push_back(id);
    return true;
}

std::vector<int> QueryPolygonFromAddBeforeQuery(int n, std::vector<std::pair<double, double> > &polygon) {
    hit_ids.clear();
    std::vector<int> point_ids;
    double a_minX = MX, a_minY = MX, a_maxX = MIN, a_maxY = MIN;
    for (int i = 0; i < n; i++) {
        double tmpx = polygon[i].first;
        double tmpy = polygon[i].second;
        a_minX = a_minX < tmpx ? a_minX : tmpx;
        a_minY = a_minY < tmpy ? a_minY : tmpy;
        a_maxX = a_maxX > tmpx ? a_maxX : tmpx;
        a_maxY = a_maxY > tmpy ? a_maxY : tmpy;
    }
    double a[2] = {a_minX, a_minY}, b[2] = {a_maxX, a_maxY};

    Search(pointTree, a, b);
    int nHits = hit_ids.size();
    for (int i = 0; i < nHits; i++) {
        int tmpId = hit_ids[i];
        std::pair<int, int> tmpPoint = points_set[tmpId];
        if(pointInPolygon(tmpPoint.first, tmpPoint.second, polygon))
        point_ids.push_back(tmpId);
    }
    return point_ids;
}
