#include "submit-6MixQuery.h"

void SetEnvironmentFromMixQuery() {
    polygon_set.clear();
    points_set.clear();
    polygon_rect.clear();
    point_rect.clear();
}

inline bool SearchCallback7(int id) {
    hit_polygon_ids.push_back(id);
    return true;
}

void AddPointFromMixQuery(int id, double x, double y) {
    Rect tmpRect(x, y, x, y);
    pointTree.Insert(tmpRect.min, tmpRect.max, id);
    points_set[id] = std::make_pair(x, y);
    point_rect[id] = tmpRect;
    point_nums++;
}

void DeletePointFromMixQuery(int id) {
    Rect& tmp = point_rect[id];
    pointTree.Remove(tmp.min, tmp.max, id);
    return;
}

std::vector<int> QueryPointFromMixQuery(double x, double y) {
    hit_polygon_ids.clear();
    std::vector<int> polygon_ids;
    Rect pointRect(x, y, x, y);
    int nHits;
    nHits = polygonTree.Search(pointRect.min, pointRect.max, SearchCallback7);
    for (int i = 0; i < nHits; i++) {
        int tmpId = hit_polygon_ids[i];
        std::vector<std::pair<double, double> > &a_polygon = polygon_set[tmpId];
        if(pointInPolygon(x, y, a_polygon))
            polygon_ids.push_back(tmpId);
    }
    return polygon_ids;
}

void AddPolygonFromMixQuery(int id, int n, std::vector<std::pair<double, double>> &polygon) {
    double a_minX = MX, a_minY = MX, a_maxX = MIN, a_maxY = MIN;
    double tmpy, tmpx;
    for (int i = 0; i < n; i++){
        tmpx = polygon[i].first;
        tmpy = polygon[i].second;
        a_minX = std::min(a_minX, tmpx);
        a_minY = std::min(a_minY, tmpy);
        a_maxX = std::max(a_maxX, tmpx);
        a_maxY = std::max(a_maxY, tmpy);
    }
    Rect tmpRect(a_minX, a_minY, a_maxX, a_maxY);
    polygon_rect.insert({id, tmpRect});
    polygonTree.Insert(tmpRect.min, tmpRect.max, id);
    polygon_set[id] = polygon;
    return;
}

void DeletePolygonFromMixQuery(int id) {
    Rect& tmp = polygon_rect[id];
    polygonTree.Remove(tmp.min, tmp.max, id);
    return;
}

inline bool SearchCallback8(int id) {
    hit_point_ids.push_back(id);
    return true;
}

std::vector<int> QueryPolygonFromMixQuery(int n, std::vector<std::pair<double, double>> &polygon) {
    hit_point_ids.clear();
    std::vector<int> point_ids;
    double a_minX = MX, a_minY = MX, a_maxX = MIN, a_maxY = MIN;
    double tmpx, tmpy;
    for (int i = 0; i < n; i++) {
        tmpx = polygon[i].first;
        tmpy = polygon[i].second;
        a_minX = std::min(a_minX, tmpx);
        a_minY = std::min(a_minY, tmpy);
        a_maxX = std::max(a_maxX, tmpx);
        a_maxY = std::max(a_maxY, tmpy);
    }
    Rect polygonRect(a_minX, a_minY, a_maxX, a_maxY);
    int nHits;
    nHits = pointTree.Search(polygonRect.min, polygonRect.max, SearchCallback8);

    for (int i = 0; i < nHits; i++) {
        int tmpId = hit_point_ids[i];
        std::pair<int, int> tmpPoint = points_set[tmpId];
        if(pointInPolygon(tmpPoint.first, tmpPoint.second, polygon))
            point_ids.push_back(tmpId);
    }
    return point_ids;
}

