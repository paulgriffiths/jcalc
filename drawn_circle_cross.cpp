/*
 *  drawn_circle_cross.cpp
 *  ======================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Implementation of example drawn object.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */

#include <algorithm>
#include "jcalc_common_types.h"
#include "drawing_context.h"
#include "drawn_circle_cross.h"

using namespace jcalc;

CircleCross::CircleCross(PDC dc, const Point& origin,
                         const double width, const double height) :
    DrawnObject(dc, origin, width, height) {
}

CircleCross::~CircleCross() {
}

void CircleCross::scale(PDC dc, const double width, const double height) {
    const double scale_factor = std::min(width, height) / 1000;
    dc->scale(scale_factor, scale_factor);
    dc->set_line_width(1 / scale_factor);
}

void CircleCross::draw_internal(PDC dc) {
    dc->set_color(RGB::stock_Gold);
    dc->arc(Point(500, 500), 400, 0, 360);
    dc->fill_preserve();
    dc->set_color(RGB::stock_Black);
    dc->stroke();

    dc->set_color(RGB::stock_White);
    dc->arc(Point(500, 500), 350, 0, 360);
    dc->fill_preserve();
    dc->set_color(RGB::stock_Black);
    dc->stroke();

    dc->set_color(RGB::stock_Gold);
    dc->rectangle(Point(0, 475), Point(1000, 525));
    dc->fill();

    dc->rectangle(Point(475, 0), Point(525, 1000));
    dc->fill_preserve();

    dc->set_color(RGB::stock_Black);
    dc->stroke();

    dc->rectangle(Point(0, 475), Point(1000, 525));
    dc->stroke();
}

