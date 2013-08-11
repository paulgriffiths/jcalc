/*
 *  point.cpp
 *  =========
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Implemented of Point class and functions.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */



#include <cmath>
#include "math_helper.h"
#include "point.h"

using namespace jcalc;

Point jcalc::ptoc(const double theta, const double r,
                  const Point& cp) {
    return Point(cp.x + std::cos(mathhelp::radians(theta)) * r,
                 cp.y + std::sin(mathhelp::radians(theta)) * r);
}
