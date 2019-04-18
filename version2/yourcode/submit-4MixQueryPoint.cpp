#include "submit-4MixQueryPoint.h"
void SetEnvironmentFromMixQueryPoint() {
    polygon_set.clear();
    polygon_rect.clear();
}

inline bool SearchCallback5(int id) {
    hit_polygon_ids.push_back(id);
    return true;
}

std::vector<int> QueryPointFromMixQueryPoint(double x, double y) {
    hit_polygon_ids.clear();
    std::vector<int> polygon_ids;
    Rect pointRect(x, y, x, y);
    int nHits;
    nHits = polygonTree.Search(pointRect.min, pointRect.max, SearchCallback5);
    for (int i = 0; i < nHits; i++) {
        int tmpId = hit_polygon_ids[i];
        std::vector<std::pair<double, double> >& a_polygon = polygon_set[tmpId];
        if(pointInPolygon(x, y, a_polygon))
            polygon_ids.push_back(tmpId);
    }
    return polygon_ids;
}

void AddPolygonFromMixQueryPoint(int id, int n, std::vector<std::pair<double, double> > &polygon) {
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
    polygon_rect.insert({id, tmpRect});
    polygonTree.Insert(tmpRect.min, tmpRect.max, id);
    polygon_set[id] = polygon;
    return;
}

void DeletePolygonFromMixQueryPoint(int id) {
    Rect tmp = polygon_rect[id];
    polygonTree.Remove(tmp.min, tmp.max, id);
    return;
}
