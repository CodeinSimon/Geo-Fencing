//
// Created by Simon on 2018/12/12.
//
#include "Rectangle.h"


std::unordered_map<int, std::vector<std::pair<double, double> > > polygon_set;
int polygon_nums = 0; // = how many polygons in total

std::unordered_map<int, std::pair<double, double> > points_set;
int point_nums;

MyTree polygonTree;
MyTree pointTree;
std::vector<int> hit_polygon_ids;
std::vector<int> hit_point_ids;
std::unordered_map<int, Rect > polygon_rect;
std::unordered_map<int, Rect > point_rect;
