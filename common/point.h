/*
 *  point.h
 *  =======
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Interface to Point class.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#ifndef PG_JCALC_POINT_H
#define PG_JCALC_POINT_H

namespace jcalc {

struct Point {
    double x;
    double y;

    Point() :
        x(0), y(0) {}
    Point(const double x, const double y) :
        x(x), y(y) {}
};

Point ptoc(const double theta, const double r,
           const Point& cp = Point(0, 0));

}

#endif          // PG_JCALC_POINT_H
