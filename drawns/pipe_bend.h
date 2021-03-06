/*
 *  pipe_bend.h
 *  ===========
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Interface to drawn pipe bend.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#ifndef PG_DRAWN_PIPE_BEND_H
#define PG_DRAWN_PIPE_BEND_H

#include <utility>
#include "drawn_common.h"
#include "drawn_object.h"
#include "flange.h"

namespace jcalc {

/*
 *  Struct for containing information about a pipe bend
 *  necessary for drawing it.
 */

struct PipeBendInfo {
    const double bend_angle;
    const double segment_angle;
    const double nominal_radius;
    const double casing_od;
    const double casing_id;
    const double lining_od;
    const double lining_id;

    PipeBendInfo() :
        bend_angle(0), segment_angle(0),
        nominal_radius(0),
        casing_od(0), casing_id(0),
        lining_od(0), lining_id(0) {}
    PipeBendInfo(const double bend_angle, const double segment_angle,
                const double nominal_radius,
                const double casing_od, const double casing_id,
                const double lining_od, const double lining_id) :
        bend_angle(bend_angle), segment_angle(segment_angle),
        nominal_radius(nominal_radius),
        casing_od(casing_od), casing_id(casing_id),
        lining_od(lining_od), lining_id(lining_id) {}
};


/*
 *  Pipe bend drawn object class.
 */

class PipeBend : public DrawnObject {
    public:
        explicit PipeBend(PDC dc, const Point& origin,
                          const double width, const double height,
                          const PipeBendInfo& pbi,
                          const FlangeInfo& fi);
        virtual ~PipeBend();

    private:
        virtual void draw_internal(PDC dc);
        void draw_pipe(PDC dc);
        void draw_pipe_cross_section(PDC dc);
        void draw_flanges(PDC dc);
        virtual std::pair<double, double>
            scale(PDC dc, const double width, const double height);

        const PipeBendInfo& m_pbi;
        const FlangeInfo& m_fi;
};

}           //  namespace jcalc

#endif          // PG_DRAWN_PIPE_BEND_H
