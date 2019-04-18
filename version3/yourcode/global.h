//
// Created by Simon Nie on 2019/1/6.
// @Copyright (c) 2019 Simon Nie. All rights reserved.
//

#ifndef INC_16307130133_3_GLOBAL_H
#define INC_16307130133_3_GLOBAL_H

#include <vector>
#include <unordered_map>
#include <stdio.h>
#include <climits>
#include <algorithm>
#include "GridPoint.h"
#include <climits>

const int MX = INT_MAX;
const int MIN = INT_MIN;

struct Point{

    Point(const double ax, const double ay, const int aid){
        x = ax;
        y = ay;
        id = aid;
    }
    double x, y;
    int id;
};

//extern std::unordered_map<int, std::vector<std::pair<double, double> > > polygon_set;
//extern std::unordered_map<int, std::pair<double, double> > point_set;
extern std::vector<Point> points;
extern std::vector<int> polygon_ids;
extern std::vector<int> point_ids;
extern std::vector<int> hit_polygon_ids;
//extern std::unordered_map<int, Rect> polygon_rect;
extern std::unordered_map<int, bool> point_is_deleted;
extern std::unordered_map<int, bool> polygon_is_deleted;
extern std::unordered_map<int, GridSet> polygon_grid;
//extern double tx, ty;
#endif //INC_16307130133_3_GLOBAL_H
