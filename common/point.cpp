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

/*
 *  Converts polar coordinates to cartestian coordinates.
 *
 *  Arguments:
 *    theta - angle, in degrees, of polar coordinate. 0 points along
 *            the positive x-axis, with angles increasing towards the
 *            positive y-axis. With a graphical drawing surface with
 *            the origin at the top left, this means that angles
 *            increase counterclockwise.
 *    r - radius
 *    cp - Point struct representing an optional centerpoint. The
 *         default is (0, 0).
 *
 *  Returns:
 *    A Point struct representing the corresponding cartesian
 *    coordinate.
 */

Point jcalc::ptoc(const double theta, const double r,
                  const Point& cp) {
    return Point(cp.x + std::cos(mathhelp::radians(theta)) * r,
                 cp.y + std::sin(mathhelp::radians(theta)) * r);
}
