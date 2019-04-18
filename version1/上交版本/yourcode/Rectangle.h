//
// Created by Simon Nie on 2018/12/12.
//

#ifndef INC_16307130133_RECTANGLE_H
#define INC_16307130133_RECTANGLE_H

#include <vector>
#include <unordered_map>
#include <climits>
#include "RTree.h"

const int MX = INT_MAX;
const int MIN = INT_MIN;
extern std::unordered_map<int, std::vector<std::pair<double, double> > > polygon_set;
extern int polygon_nums;


extern std::unordered_map<int, std::pair<double, double> > points_set;
extern int point_nums;

struct Rect
{
    Rect() {}
    // constructor
    Rect(double& a_minX, double& a_minY, double& a_maxX, double& a_maxY)
    {
        min[0] = a_minX;
        min[1] = a_minY;

        max[0] = a_maxX;
        max[1] = a_maxY;
    }
    // copy constructor
    Rect(const Rect& a){
        min[0] = a.min[0];
        min[1] = a.min[1];
        max[0] = a.max[0];
        max[1] = a.max[1];
    }
    ~Rect() = default;
    double min[2];
    double max[2];
};

typedef RTree<int, double, 2, double> MyTree;
extern MyTree polygonTree;
extern MyTree pointTree; // each point is a rectangle
extern std::vector<int> hit_polygon_ids;
extern std::vector<int> hit_point_ids;
extern std::unordered_map<int, Rect> polygon_rect;
extern std::unordered_map<int, Rect> point_rect;

#endif //INC_16307130133_RECTANGLE_H
