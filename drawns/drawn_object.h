/*
 *  drawn_object.h
 *  ==============
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Abstract base class for drawn objects.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#ifndef PG_DRAWN_OBJECT_H
#define PG_DRAWN_OBJECT_H

#include "drawn_common.h"

namespace jcalc {

class DrawnObject {
    public:
        explicit DrawnObject(PDC dc, const Point& origin,
                             const double width, const double height);
        virtual ~DrawnObject();

        void draw();

    protected:
        void set_scale(const double sx, const double sy);
        double width() const;
        double height() const;

    private:
        virtual void draw_internal(PDC dc) = 0;
        virtual void scale(PDC dc, const double width, const double height);

        PDC m_dc;
        const Point m_origin;
        const double m_width;
        const double m_height;
        double m_scale_factor_x;
        double m_scale_factor_y;
};

}           //  namespace jcalc

#endif          // PG_DRAWN_OBJECT_H
