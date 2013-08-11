/*
 *  segmented_bend.cpp
 *  ==================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Implementation of drawn segmented bend class.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */

#include <vector>
#include <algorithm>
#include "drawn_common.h"
#include "segmented_bend.h"

using namespace jcalc;


/*
 *  Constructor.
 */

SegmentedBend::SegmentedBend(PDC dc, const Point& origin,
                             const SegBendInfo& sbi, const RGB& rgb,
                             const bool fill, const bool outline) :
    DrawnObject(dc, origin, 0, 0),
    m_sbi(sbi), m_rgb(rgb), m_fill(fill), m_outline(outline) {
}


/*
 *  Destructor.
 */

SegmentedBend::~SegmentedBend() {
}


/*
 *  Standalone function for calculating segment points.
 *
 *  Arguments:
 *    pts - a std::vector<Point> in which the function stores the
 *          calculated points.
 *    cf_radius - the nominal or center-face radius of the bend, which
 *                passes through the center of each end-face.
 *    bend_angle - the angle of the total bend.
 *    segment_angle - the angle of each segment.
 *
 *  Bends are always terminated with a half-segment for a flat face.
 *  Thus, the 'erad' variable is necessary since the nominal radius
 *  passes through the pipe's center at mid segment (end-face for a
 *  half segment) but not at the ends of the segments where the points
 *  are calculated.
 *
 *  This function has local scope only, and is used by draw_internal().
 */

namespace {

void calc_segment_points(std::vector<Point>& pts,
                         const double cf_radius,
                         const double bend_angle,
                         const double segment_angle) {
    const int num_segments = bend_angle / segment_angle;
    const int erad = cf_radius /
        std::cos(mathhelp::radians(segment_angle / 2));

    pts.push_back(ptoc(0, cf_radius));
    for ( int i = 0; i < num_segments; ++i ) {
        pts.push_back(ptoc(360 - segment_angle * (i + 0.5), erad));
    }
    pts.push_back(ptoc(360 - bend_angle, cf_radius));
}

}           //  namespace


/*
 *  Draws a segmented bend.
 */

void SegmentedBend::draw_internal(PDC dc) {
    std::vector<Point> pts_out;             //  Extrados points
    std::vector<Point> pts_in;              //  Intrados points

    //  Calculate the extrados and intrados points

    calc_segment_points(pts_out, m_sbi.bend_radius + m_sbi.pipe_radius / 2,
                        m_sbi.bend_angle, m_sbi.segment_angle);
    calc_segment_points(pts_in, m_sbi.bend_radius - m_sbi.pipe_radius / 2,
                        m_sbi.bend_angle, m_sbi.segment_angle);

    //  Draw the extrados points, from zero degrees proceeding in a
    //  counterclockwise direction.

    for ( std::vector<Point>::const_iterator i = pts_out.begin();
          i != pts_out.end(); ++i ) {
        if ( i == pts_out.begin() ) {
            dc->move_to(*i);
        } else {
            dc->line_to(*i);
        }
    }

    //  Draw the intrados points in the reverse direction, to form
    //  an enclosed path suitable for filling.

    for ( std::vector<Point>::reverse_iterator i = pts_in.rbegin();
          i != pts_in.rend(); ++i ) {
        if ( i == pts_in.rbegin() &&
             m_outline == false &&
             m_fill == false ) {

            //  When m_outline is true, we're drawing the entire
            //  outline (i.e. not omitting the faces), and when
            //  m_fill is true, we're filling with a color. In
            //  both of these cases we need an enclosing path,
            //  so only use move_to() when we're not in either
            //  situation and we're just drawing the sides, not
            //  the faces.

            dc->move_to(*i);
        } else {
            dc->line_to(*i);
        }
    }

    //  Close the path if we're drawing a complete outline or
    //  filling with color.

    if ( m_outline || m_fill ) {
        dc->close_path();
    }

    //  Fill with color, if applicable.

    if ( m_fill ) {
        dc->save();
        dc->set_color(m_rgb);
        if ( m_outline ) {

            //  If we're drawing an outline in addition to filling,
            //  we need to remember the path, so call fill_preserve()
            //  rather than fill().

            dc->fill_preserve();
        } else {
            dc->fill();
        }
        dc->restore();
    }

    //  Stroke the outline if necessary. If m_fill is false, we
    //  assume we're drawing some kind of outline. If m_outline
    //  is also false, then we assume we're just drawing a partial
    //  outline (i.e. the sides, but not the faces.
    //
    //  Note that we cannot simultaneously fill and draw a partial
    //  outline with the current logic, it has to be fill with a
    //  full outline, or a partial outline with no fill.
    //
    //  TODO: remedy the above, we'll always need to at least draw
    //  a partial outline, so by changing this behaviour we can
    //  avoid calling the function twice. Some code duplication
    //  will be necessary, as in one case we need a closed path,
    //  and in the other case, we can't have one.

    if ( m_outline || m_fill == false ) {
        dc->stroke();
    }
}

