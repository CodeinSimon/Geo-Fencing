//
// Created by Simon Nie on 2019/1/6.
// @Copyright (c) 2019 Simon Nie. All rights reserved.
//
#include "global.h"

//std::unordered_map<int, std::vector<std::pair<double, double> >> polygon_set;
std::vector<Point> points;
//MyTree polygonTree;
std::unordered_map<int, GridSet> polygon_grid;
//std::unordered_map<int, std::pair<double, double> > point_set;
std::vector<int> polygon_ids;
std::vector<int> point_ids;
std::vector<int> hit_polygon_ids;

//std::unordered_map<int, Rect> polygon_rect;
std::unordered_map<int, bool> polygon_is_deleted;
std::unordered_map<int, bool> point_is_deleted;
//double tx, ty;
