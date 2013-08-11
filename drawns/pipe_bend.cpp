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
#include <algorithm>
#include "drawn_common.h"
#include "pipe_bend.h"
#include "segmented_bend.h"

using namespace jcalc;


/*
 *  Constructor.
 */

PipeBend::PipeBend(PDC dc, const Point& origin,
                   const double width, const double height,
                   const PipeBendInfo& pbi) :
    DrawnObject(dc, origin, width, height),
    m_pbi(pbi) {
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
    SegBendInfo sbi(m_pbi.bend_angle, m_pbi.segment_angle,
                    m_pbi.nominal_radius, m_pbi.casing_od / 2);

    //  Set up colors and radii for the four "components"

    const double rads[] = {m_pbi.casing_od / 2,
                           m_pbi.casing_id / 2,
                           m_pbi.lining_od / 2,
                           m_pbi.lining_id / 2};
    const RGB colors[] = {RGB::stock_SeaGreen,
                          RGB::stock_LightGray,
                          RGB::stock_Bisque,
                          RGB::stock_White};

    //  Draw them

    for ( int i = 0; i < 4; ++i ) {
        sbi.pipe_radius = rads[i];
        SegmentedBend section(dc, Point(0, height()), sbi, colors[i],
                              true, false);
        section.draw();
    }
                
    //  Draw the overall bend outline. Draw last to avoid the drawing
    //  of the other components interfering with it.

    sbi.pipe_radius = m_pbi.casing_od / 2;
    SegmentedBend bend_outline(dc, Point(0, height()), sbi,
                               RGB::stock_Black, false, true);
    bend_outline.draw();
}


/*
 *  Virtual scaling function.
 *
 *  This function is currently very rudimentary while the class
 *  is being developed.
 */

void PipeBend::scale(PDC dc, const double width, const double height) {
    const double extent = m_pbi.nominal_radius +
                          m_pbi.casing_od / 2;
    const double s_extent = std::min(width, height);
    const double s_factor = s_extent / extent;
    set_scale(s_factor, s_factor);
}
