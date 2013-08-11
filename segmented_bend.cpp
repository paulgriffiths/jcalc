/*
 *  segmented_bend.cpp
 *  ==================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Implementation of drawn segmented bend.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */

#include <vector>
#include <algorithm>
#include "jcalc_common_types.h"
#include "drawing_context.h"
#include "segmented_bend.h"
#include "math_helper.h"

using namespace jcalc;

SegmentedBend::SegmentedBend(PDC dc, const Point& origin,
                             const SegBendInfo& sbi, const RGB& rgb,
                             const bool fill, const bool outline) :
    DrawnObject(dc, origin, 0, 0),
    m_sbi(sbi), m_rgb(rgb), m_fill(fill), m_outline(outline) {
}

SegmentedBend::~SegmentedBend() {
}

void calc_segment_points(std::vector<Point>& pts,
                         const double cf_radius,
                         const double bend_angle,
                         const double segment_angle) {
    const int num_segments = bend_angle / segment_angle;
    const int erad = cf_radius / std::cos(mathhelp::radians(segment_angle / 2));

    pts.push_back(ptoc(0, cf_radius));
    for ( int i = 0; i < num_segments; ++i ) {
        pts.push_back(ptoc(360 - segment_angle * (i + 0.5), erad));
    }
    pts.push_back(ptoc(360 - bend_angle, cf_radius));
}

void SegmentedBend::draw_internal(PDC dc) {
    std::vector<Point> pts_out;
    std::vector<Point> pts_in;

    calc_segment_points(pts_out, m_sbi.bend_radius + m_sbi.pipe_radius / 2,
                        m_sbi.bend_angle, m_sbi.segment_angle);
    calc_segment_points(pts_in, m_sbi.bend_radius - m_sbi.pipe_radius / 2,
                        m_sbi.bend_angle, m_sbi.segment_angle);

    for ( std::vector<Point>::const_iterator i = pts_out.begin();
          i != pts_out.end(); ++i ) {
        if ( i == pts_out.begin() ) {
            dc->move_to(*i);
        } else {
            dc->line_to(*i);
        }
    }

    for ( std::vector<Point>::reverse_iterator i = pts_in.rbegin();
          i != pts_in.rend(); ++i ) {
        if ( i == pts_in.rbegin() && m_outline == false && m_fill == false) {
            dc->move_to(*i);
        } else {
            dc->line_to(*i);
        }
    }

    if ( m_outline ) {
        dc->close_path();
    }

    if ( m_fill ) {
        dc->save();
        dc->set_color(m_rgb);
        if ( m_outline ) {
            dc->fill_preserve();
        } else {
            dc->fill();
        }
        dc->restore();
    }

    if ( m_outline || m_fill == false) {
        dc->stroke();
    }
}

