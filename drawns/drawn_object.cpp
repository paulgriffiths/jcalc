/*
 *  drawn_object.cpp
 *  ================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Implementation of drawn object base class.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */

#include "drawn_common.h"
#include "drawn_object.h"

using namespace jcalc;

DrawnObject::DrawnObject(PDC dc, const Point& origin,
                         const double width, const double height) :
    m_dc(dc), m_origin(origin),
    m_width(width), m_height(height),
    m_scale_factor_x(1), m_scale_factor_y(1) {
}

DrawnObject::~DrawnObject() {
}

void DrawnObject::draw() {
    m_dc->save();
    m_dc->translate(m_origin.x, m_origin.y);

    scale(m_dc, m_width, m_height);
    draw_internal(m_dc);

    m_dc->restore();
}

void DrawnObject::set_scale(const double sx, const double sy) {
    m_dc->scale(sx, sy);
    m_scale_factor_x = sx;
    m_scale_factor_y = sy;
}

#pragma GCC diagnostic ignored "-Wunused-parameter"

void DrawnObject::scale(PDC dc, const double width, const double height) {
}

#pragma GCC diagnostic pop

double DrawnObject::width() const {
    return m_width / m_scale_factor_x;
}

double DrawnObject::height() const {
    return m_height / m_scale_factor_y;
}

