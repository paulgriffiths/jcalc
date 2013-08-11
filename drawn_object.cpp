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

#include "jcalc_common_types.h"
#include "drawing_context.h"
#include "drawn_object.h"

using namespace jcalc;

DrawnObject::DrawnObject(PDC dc, const Point& origin,
                         const double width, const double height) :
    m_dc(dc), m_origin(origin), m_width(width), m_height(height) {
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

double DrawnObject::width() {
    return m_width;
}

double DrawnObject::height() {
    return m_height;
}

