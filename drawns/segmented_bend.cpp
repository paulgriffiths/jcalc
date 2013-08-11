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
#include <cmath>
#include "drawn_common.h"
#include "segmented_bend.h"

using namespace jcalc;


/*
 *  Constructor.
 *
 *  Arguments:
 *    dc - PDC pointer to a drawing context.
 *    origin - center of the bend arc
 *    sbi - dimensions of the segmented bend
 *    fillcolor - color with which to fill (outlines are always drawn
 *                in black)
 *    fill - fills the bend with 'fillcolor' if true
 *    outline - draws a full outline if true. If false, draws an outline
 *              only at the bend sides (i.e. not the bend end-faces) 
 */

SegmentedBend::SegmentedBend(PDC dc, const Point& origin,
                             const SegBendInfo& sbi, const RGB& fillcolor,
                             const bool fill, const bool outline) :
    DrawnObject(dc, origin, 0, 0),
    m_sbi(sbi), m_fillcolor(fillcolor), m_fill(fill), m_outline(outline) {
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

void calc_segment_points(PointVector& pts,
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
    PointVector pts_out;             //  Extrados points
    PointVector pts_in;              //  Intrados points

    //  Calculate the extrados and intrados points

    calc_segment_points(pts_out, m_sbi.bend_radius + m_sbi.pipe_radius / 2,
                        m_sbi.bend_angle, m_sbi.segment_angle);
    calc_segment_points(pts_in, m_sbi.bend_radius - m_sbi.pipe_radius / 2,
                        m_sbi.bend_angle, m_sbi.segment_angle);

    dc->set_color(RGB::stock_Black);
    
    if ( m_outline || m_fill ) {

        //  Draw the extrados points, from zero degrees proceeding in a
        //  counterclockwise direction.

        for ( PointVector::const_iterator i = pts_out.begin();
              i != pts_out.end(); ++i ) {
            if ( i == pts_out.begin() ) {
                dc->move_to(*i);
            } else {
                dc->line_to(*i);
            }
        }

        //  Draw the intrados points in the reverse direction, to form
        //  an enclosed path suitable for filling.

        for ( PointVector::const_reverse_iterator i = pts_in.rbegin();
              i != pts_in.rend(); ++i ) {
            dc->line_to(*i);
        }

        dc->close_path();

        //  Fill with color, if applicable.

        if ( m_fill ) {
            dc->set_color(m_fillcolor);
            if ( m_outline ) {

                //  If we're drawing an outline in addition to filling,
                //  we need to remember the path, so call fill_preserve()
                //  rather than fill().

                dc->fill_preserve();
            } else {
                dc->fill();
            }
            dc->set_color(RGB::stock_Black);
        }

        if ( m_outline ) {
            dc->stroke();
        }
    }
    
    //  Draw a partial outline of the sides only, if necessary.

    if ( m_outline == false ) {
        for ( PointVector::const_iterator i = pts_out.begin();
              i != pts_out.end(); ++i ) {
            if ( i == pts_out.begin() ) {
                dc->move_to(*i);
            } else {
                dc->line_to(*i);
            }
        }
        dc->stroke();

        for ( PointVector::const_iterator i = pts_in.begin();
              i != pts_in.end(); ++i ) {
            if ( i == pts_out.begin() ) {
                dc->move_to(*i);
            } else {
                dc->line_to(*i);
            }
        }
        dc->stroke();
    }
}

