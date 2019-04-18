#include "submit-2AddPointBeforeQueryPolygon.h"

void SetEnvironmentFromAddPointBeforeQueryPolygon() {
    points_set.clear();
}

inline bool SearchCallback2(int id) {
    hit_point_ids.push_back(id);
    return true;
}

void AddPointFromAddPointBeforeQueryPolygon(int id, double x, double y) {
    Rect tmpRect(x, y, x, y);
    pointTree.Insert(tmpRect.min, tmpRect.max, id);
    points_set[id] = std::make_pair(x, y);
    point_rect[id] = tmpRect;
    point_nums++;

}

std::vector<int> QueryPolygonFromAddPointBeforeQueryPolygon(int n, std::vector<std::pair<double, double> > polygon) {
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
    nHits = pointTree.Search(polygonRect.min, polygonRect.max, SearchCallback2);

    for (int i = 0; i < nHits; i++) {
        int tmpId = hit_point_ids[i];
        std::pair<int, int> tmpPoint = points_set[tmpId];
        if(pointInPolygon(tmpPoint.first, tmpPoint.second, polygon))
        point_ids.push_back(tmpId);
    }
    return point_ids;
}
