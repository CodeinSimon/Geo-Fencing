//
// Created by Simon Nie on 2018/12/12.
//
/**-----------------------------------------------------------------------------------------------------------
 * |  Declare: This file is open-source code which can be download at http://alienryderflex.com/polygon/     |
 * |           And i have modified some data structure of these functions.                                   |
 *------------------------------------------------------------------------------------------------------------
 */
#include "JudgePoint.h"

bool pointInPolygon(double px, double py, std::vector<std::pair<double, double>> &polygon) {
    bool flag = false;
    for (int i = 0, l = polygon.size(), j = l - 1; i < l; j = i, i++) {
        double sx = polygon[i].first, sy = polygon[i].second, tx = polygon[j].first, ty = polygon[j].second;
        if ((sx == px && sy == py) || (tx == px && ty == py)) return false;
        if ((sy < py && ty >= py) || (sy >= py && ty < py)) {
            double x = sx + (py - sy) * (tx - sx) / (ty - sy);
            if (x == px) return false;
            if (x > px) flag = !flag;
        }
    }
    return flag;
}