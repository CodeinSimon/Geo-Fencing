//
// Created by zhang on 18-12-4.
// Filled by Simon Nie on 18-12-13
//

#include "submit-5MixQueryPolygon.h"

void SetEnvironmentFromMixQueryPolygon() {
    points_set.clear();
    point_rect.clear();
}

inline bool SearchCallback6(int id) {
    hit_point_ids.push_back(id);
    return true;
}

void AddPointFromMixQueryPolygon(int id, double x, double y) {
    Rect tmpRect(x, y, x, y);
    pointTree.Insert(tmpRect.min, tmpRect.max, id);
    points_set[id] = std::make_pair(x, y);
    point_rect[id] = tmpRect;
    point_nums++;
}

void DeletePointFromMixQueryPolygon(int id) {
    Rect tmp = point_rect[id];
    pointTree.Remove(tmp.min, tmp.max, id);
    return;
}

std::vector<int> QueryPolygonFromMixQueryPolygon(int n, std::vector<std::pair<double, double> > &polygon) {
    hit_point_ids.clear();
    std::vector<int> point_ids;
    double a_minX = MX, a_minY = MX, a_maxX = MIN, a_maxY = MIN, tmpx, tmpy;
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
    nHits = pointTree.Search(polygonRect.min, polygonRect.max, SearchCallback6);

    for (int i = 0; i < nHits; i++) {
        int tmpId = hit_point_ids[i];
        std::pair<int, int> tmpPoint = points_set[tmpId];
        if(pointInPolygon(tmpPoint.first, tmpPoint.second, polygon))
        point_ids.push_back(tmpId);
    }
    return point_ids;
}
