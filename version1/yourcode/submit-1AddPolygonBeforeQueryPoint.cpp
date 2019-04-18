#include "submit-1AddPolygonBeforeQueryPoint.h"

void SetEnvironmentFromAddPolygonBeforeQueryPoint() {
    polygon_set.clear();
}

inline bool SearchCallback1(int id) {
    hit_polygon_ids.push_back(id);
    return true;
}

std::vector<int> QueryPointFromAddPolygonBeforeQueryPoint(double x, double y) {
    hit_polygon_ids.clear();
    std::vector<int> polygon_ids;
    Rect pointRect(x, y, x, y);
    int nHits;
    nHits = polygonTree.Search(pointRect.min, pointRect.max, SearchCallback1);
    printf_s("nHits: %d\n", nHits);
    for (int i = 0; i < nHits; i++) {
        int tmpId = hit_polygon_ids[i];
        std::vector<std::pair<double, double> >& a_polygon = polygon_set[tmpId];
       if(pointInPolygon(x, y, a_polygon))
            polygon_ids.push_back(tmpId);
        if(! i%1000)fprintf(stderr,"query success\n");
    }

    return polygon_ids;
}

void AddPolygonFromAddPolygonBeforeQueryPoint(int id, int n, std::vector<std::pair<double, double> > &polygon) {
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
    //std::cout<<polygon_vector[polygon_nums].size()<<std::endl;
    polygon_set[id] = polygon;
    return;

}
