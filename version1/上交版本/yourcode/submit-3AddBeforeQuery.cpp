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
    Rect tmpRect(x, y, x, y);
    pointTree.Insert(tmpRect.min, tmpRect.max, id);
    points_set[id] = std::make_pair(x, y);

}

void AddPolygonFromAddBeforeQuery(int id, int n, std::vector<std::pair<double, double> > &polygon) {
    double a_minX = MX, a_minY = MX, a_maxX = MIN, a_maxY = MIN, tmpx, tmpy;
    for (int i = 0; i < n; i++) {
        tmpx = polygon[i].first;
        tmpy = polygon[i].second;
        a_minX = std::min(a_minX, tmpx);
        a_minY = std::min(a_minY, tmpy);
        a_maxX = std::max(a_maxX, tmpx);
        a_maxY = std::max(a_maxY, tmpy);
    }
    Rect tmpRect(a_minX, a_minY, a_maxX, a_maxY);
    polygonTree.Insert(tmpRect.min, tmpRect.max, id);
    polygon_set[id] = polygon;
    return;
}

std::vector<int> QueryPointFromAddBeforeQuery(double x, double y) {
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
    hit_point_ids.clear();
    std::vector<int> point_ids;
    double a_minX, a_minY, a_maxX, a_maxY;
    for (int i = 0; i < n; i++) {
        double tmpx = polygon[i].first;
        double tmpy = polygon[i].second;
        a_minX = std::min(a_minX, tmpx);
        a_minY = std::min(a_minY, tmpy);
        a_maxX = std::max(a_maxX, tmpx);
        a_maxY = std::max(a_maxY, tmpy);
    }
    Rect polygonRect(a_minX, a_minY, a_maxX, a_maxY);
    int nHits;
    nHits = pointTree.Search(polygonRect.min, polygonRect.max, SearchCallback4);
    for (int i = 0; i < nHits; i++) {
        int tmpId = hit_point_ids[i];
        std::pair<int, int> tmpPoint = points_set[tmpId];
        if(pointInPolygon(tmpPoint.first, tmpPoint.second, polygon))
        point_ids.push_back(tmpId);
    }
    return point_ids;
}
