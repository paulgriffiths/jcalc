/*
 *  segmented_bend.h
 *  ================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Interface to drawn segmented bend.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#ifndef PG_DRAWN_SEGMENTED_BEND_H
#define PG_DRAWN_SEGMENTED_BEND_H

#include "jcalc_common_types.h"
#include "drawing_context.h"
#include "drawn_object.h"

namespace jcalc {

struct SegBendInfo {
    const double bend_angle;
    const double segment_angle;
    const double bend_radius;
    const double pipe_radius;

    SegBendInfo() :
        bend_angle(0), segment_angle(0),
        bend_radius(0), pipe_radius(0) {}
    SegBendInfo(const double bend_angle, const double segment_angle,
                const double bend_radius, const double pipe_radius) :
        bend_angle(bend_angle), segment_angle(segment_angle),
        bend_radius(bend_radius), pipe_radius(pipe_radius) {}
};

class SegmentedBend : public DrawnObject {
    public:
        explicit SegmentedBend(PDC dc, const Point& origin,
                              const SegBendInfo& sbi, const RGB& rgb,
                              const bool fill = true,
                              const bool outline = false);
        virtual ~SegmentedBend();

    private:
        virtual void draw_internal(PDC dc);

        const SegBendInfo& m_sbi;
        const RGB& m_rgb;
        const bool m_fill;
        const bool m_outline;
};

}           //  namespace jcalc

#endif          // PG_DRAWN_SEGMENTED_BEND_H
