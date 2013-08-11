/*
 *  drawn_circle_cross.h
 *  ====================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Interface to example drawn object.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#ifndef PG_DRAWN_CIRCLE_CROSS_H
#define PG_DRAWN_CIRCLE_CROSS_H

#include "drawn_common.h"
#include "drawn_object.h"

namespace jcalc {

class CircleCross : public DrawnObject {
    public:
        explicit CircleCross(PDC dc, const Point& origin,
                             const double width, const double height);
        virtual ~CircleCross();

    private:
        virtual void scale(PDC dc, const double width, const double height);
        virtual void draw_internal(PDC dc);
};

}           //  namespace jcalc

#endif          // PG_DRAWN_CIRCLE_CROSS_H
