/*
 *  segmented_bend.h
 *  ================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Interface to drawn segmented bend class.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#ifndef PG_DRAWN_SEGMENTED_BEND_H
#define PG_DRAWN_SEGMENTED_BEND_H

#include "drawn_common.h"
#include "drawn_object.h"

namespace jcalc {

/*
 *  Struct to contain information about a segmented bend
 *  necessary to draw it.
 */

struct SegBendInfo {
    double bend_angle;
    double segment_angle;
    double bend_radius;
    double pipe_radius;

    SegBendInfo() :
        bend_angle(0), segment_angle(0),
        bend_radius(0), pipe_radius(0) {}
    SegBendInfo(const double bend_angle, const double segment_angle,
                const double bend_radius, const double pipe_radius) :
        bend_angle(bend_angle), segment_angle(segment_angle),
        bend_radius(bend_radius), pipe_radius(pipe_radius) {}
};


/*
 *  Segmented bend class.
 */

class SegmentedBend : public DrawnObject {
    public:
        enum class outline {none, partial, full};

        explicit SegmentedBend(PDC dc, const Point& origin,
                               const SegBendInfo& sbi, const RGB& rgb,
                               const bool fill = true,
                               const outline outline_type = outline::partial,
                               const bool ribs = false);
        virtual ~SegmentedBend();


    private:
        virtual void draw_internal(PDC dc);
        void draw_section(PDC dc, const PointVector& pts_out,
                          const PointVector& pts_in);
        void draw_ribs(PDC dc, const PointVector& pts_out,
                       const PointVector& pts_in);

        const SegBendInfo& m_sbi;
        const RGB& m_fillcolor;
        const bool m_fill;
        const outline m_outline;
        const bool m_ribs;
};

}           //  namespace jcalc

#endif          // PG_DRAWN_SEGMENTED_BEND_H
