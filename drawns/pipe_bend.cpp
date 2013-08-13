/*
 *  pipe_bend.cpp
 *  =============
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Implementation of drawn pipe bend.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */

#include <vector>
#include <utility>
#include <algorithm>
#include "drawn_common.h"
#include "pipe_bend.h"
#include "segmented_bend.h"
#include "flange.h"

using namespace jcalc;


/*
 *  Constructor.
 */

PipeBend::PipeBend(PDC dc, const Point& origin,
                   const double width, const double height,
                   const PipeBendInfo& pbi,
                   const FlangeInfo& fi) :
    DrawnObject(dc, origin, width, height),
    m_pbi(pbi), m_fi(fi) {
}


/*
 *  Destructor.
 */

PipeBend::~PipeBend() {
}


/*
 *  Virtual draw_internal() function.
 */

void PipeBend::draw_internal(PDC dc) {
    dc->set_scaled_line_width(0.5);
    draw_pipe(dc);
    draw_pipe_cross_section(dc);
    draw_flanges(dc);
}


/*
 *  Draws the pipe part of the bend.
 */

void PipeBend::draw_pipe(PDC dc) {
    static const int num_components = 5;
    const Point origin(0, height() - (m_fi.fd / 2));
    SegBendInfo sbi(m_pbi.bend_angle, m_pbi.segment_angle,
                    m_pbi.nominal_radius, m_pbi.casing_od / 2);

    //  Set up colors and radii for the four "components", and
    //  for the full outline at the end (drawn separately to
    //  avoid the other drawn components interfering with it).

    const double rads[num_components] = {m_pbi.casing_od / 2,
                                         m_pbi.casing_id / 2,
                                         m_pbi.lining_od / 2,
                                         m_pbi.lining_id / 2,
                                         m_pbi.casing_od / 2};
    const RGB colors[num_components] = {RGB::stock_SeaGreen,
                                        RGB::stock_LightGray,
                                        RGB::stock_Bisque,
                                        RGB::stock_White,
                                        RGB::stock_SeaGreen};

    //  Draw them. When i ==:
    //    0 - the outer component is drawn filled, but with no outline
    //    1, 2, 3 - the inner components are drawn filled with partial
    //              outlines
    //    4 - the full outline and ribs are drawn for the outer component,
    //        with no fill.

    for ( int i = 0; i < num_components; ++i ) {
        sbi.pipe_radius = rads[i];
        const bool fill = (i == num_components - 1 ? false : true);
        const bool ribs = (i == num_components - 1 ? true : false);
        SegmentedBend::outline outline;
        if ( i == 0 ) {
            outline = SegmentedBend::outline::none;
        } else if ( i == num_components - 1 ) {
            outline = SegmentedBend::outline::full;
        } else {
            outline = SegmentedBend::outline::partial;
        }

        SegmentedBend section(dc, origin, sbi, colors[i], fill, outline, ribs);
        section.draw();
    }

    BendArc bend_arc(dc, origin, sbi);
    bend_arc.draw();
}


/*
 *  Draws the pipe cross section.
 */

void PipeBend::draw_pipe_cross_section(PDC dc) {
    static const int num_components = 4;
    const Point origin(m_pbi.nominal_radius, height() - (m_fi.fd / 2));

    const double rads[num_components] = {m_pbi.casing_od / 2,
                                         m_pbi.casing_id / 2,
                                         m_pbi.lining_od / 2,
                                         m_pbi.lining_id / 2};

    for ( int i = 0; i < num_components; ++i ) {
        dc->arc(origin, rads[i], 0, 180);
    }
    dc->stroke();
}


/*
 *  Draws the flanges.
 *
 *  Note the second flange has to be drawn with a center point at
 *  360 - bend_angle, but faces the other way so has to be flipped
 *  back 180 degrees.
 *
 *  A profile is drawn with the first flange.
 */

void PipeBend::draw_flanges(PDC dc) {
    const Point origin(0, height() - (m_fi.fd / 2));

    Flange fl1(dc, ptoc(0, m_pbi.nominal_radius, origin), 0, m_fi, true);
    fl1.draw();
    Flange fl2(dc, ptoc(360 - m_pbi.bend_angle, m_pbi.nominal_radius, origin),
               180 - m_pbi.bend_angle, m_fi);
    fl2.draw();
}


/*
 *  Virtual scaling function.
 *
 *  This function is currently very rudimentary while the class
 *  is being developed.
 */

std::pair<double, double>
PipeBend::scale(PDC dc, const double width, const double height) {
    const double x_extent = m_pbi.nominal_radius +
                            m_fi.fd / 2;
    const double y_extent = m_pbi.nominal_radius + m_fi.fd;
    const double sx_factor = width / x_extent;
    const double sy_factor = height / y_extent;
    const double s_factor = std::min(sx_factor, sy_factor);
    return std::pair<double, double>(s_factor, s_factor);
}
