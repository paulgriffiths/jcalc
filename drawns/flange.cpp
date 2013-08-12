/*
 *  flange.cpp
 *  ==========
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Implementation of flange drawn object.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */

#include <vector>
#include <algorithm>
#include "drawn_common.h"
#include "flange.h"

using namespace jcalc;


const FlangeInfo FlangeInfo::F100PN16("100PN16", 100, 220, 20,
                                      180, 18, 8, 158, 2);
const FlangeInfo FlangeInfo::F125PN16("125PN16", 125, 250, 22,
                                      210, 18, 8, 188, 2);
const FlangeInfo FlangeInfo::F150PN16("150PN16", 150, 285, 22,
                                      240, 22, 8, 212, 2);
const FlangeInfo FlangeInfo::F200PN16("200PN16", 200, 340, 24,
                                      295, 22, 12, 268, 2);
const FlangeInfo FlangeInfo::F250PN16("250PN16", 250, 405, 26,
                                      355, 26, 12, 320, 2);
const FlangeInfo FlangeInfo::F300PN16("300PN16", 300, 460, 28,
                                      410, 26, 12, 378, 2);
const FlangeInfo FlangeInfo::F400PN16("400PN16", 400, 580, 32,
                                      525, 30, 16, 490, 2);

/*
 *  Constructor.
 */

Flange::Flange(PDC dc, const Point& origin, const double angle,
               const FlangeInfo& fi) :
    DrawnObject(dc, origin, 0, 0),
    m_fi(fi), m_angle(angle) {
}


/*
 *  Destructor.
 */

Flange::~Flange() {
}


/*
 *  Virtual draw_internal() function.
 */

void Flange::draw_internal(PDC dc) {
    draw_profile(dc, m_angle);
}

void Flange::draw_profile(PDC dc, const double angle) {
    dc->save();
    dc->rotate(angle);

    for ( int reverse = 1; reverse >= -1; reverse -= 2 ) {
        Point pts[] = {Point(m_fi.hd / 2 * reverse, 0),
                       Point(m_fi.rfd / 2 * reverse, 0),
                       Point(m_fi.rfd / 2 * reverse, -m_fi.rfh),
                       Point(m_fi.fd / 2 * reverse, -m_fi.rfh),
                       Point(m_fi.fd / 2 * reverse, -m_fi.ft),
                       Point(m_fi.hd / 2 * reverse, -m_fi.ft)};

        dc->move_to(pts[0]);
        for ( int i = 1; i < 6; ++i ) {
            dc->line_to(pts[i]);
        }

        dc->close_path();
        dc->set_color(RGB::stock_LightGray);
        dc->fill_preserve();
        dc->set_color(RGB::stock_Black);
        dc->stroke();
    }

    dc->restore();
}
