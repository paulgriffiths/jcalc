/*
 *  math_helper.h
 *  =============
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Mathematical helper functions.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#ifndef PG_MATH_HELPER_H
#define PG_MATH_HELPER_H

#include <cmath>


namespace mathhelp {

/*
 *  Constants
 */

const double PI = 3.14159265358979323846;



/*
 *  Inline functions
 */


/*
 *  Calculates the length of the hypotenuse using Pythagoras.
 */

inline double hypot(const double opp, const double adj) {
    return std::sqrt(std::pow(opp, 2) + std::pow(adj, 2));
}


/*
 *  Returns a double representing an angle in degrees in the
 *  range 0 <= d < 360, when the supplied angle may or may
 *  not be outside of this range.
 */

inline double normalize_degrees(const double angle) {
    return angle - 360 * floor(angle / 360);
}


/*
 *  Converts radians to degrees.
 */

inline double degrees(const double rads) {
    return rads / (PI / 180);
}


/*
 *  Converts degrees to radians.
 */

inline double radians(const double degs) {
    return degs * (PI / 180);
}

}           //  namespace mathhelp

#endif          // PG_MATH_HELPER_H
