//
// Created by Simon on 2018/12/12.
//
#include "Rectangle.h"


std::unordered_map<int, std::vector<std::pair<double, double> > > polygon_set;

std::unordered_map<int, std::pair<double, double> > points_set;

MyTree polygonTree;
Node* pointTree = NULL;
std::vector<int> hit_polygon_ids;
std::unordered_map<int, Rect > polygon_rect;
