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

#include <utility>
#include "drawn_common.h"
#include "drawn_object.h"

using namespace jcalc;


/*
 *  Constructor.
 */

DrawnObject::DrawnObject(PDC dc, const Point& origin,
                         const double width, const double height) :
    m_dc(dc), m_origin(origin),
    m_width(width), m_height(height),
    m_scale_factor_x(1), m_scale_factor_y(1) {
}


/*
 *  Destructor.
 */

DrawnObject::~DrawnObject() {
}


/*
 *  Public draw function.
 *
 *  This function sets up for the virtual draw_internal() function,
 *  and translates and scales the drawing context so that draw_internal()
 *  can treat the entire area as its logical drawing space. Also saves
 *  and restores the original drawing context state so that draw_internal()
 *  does not interfere with the settings in the calling function.
 */

void DrawnObject::draw() {
    m_dc->save();
    m_dc->translate(m_origin.x, m_origin.y);

    std::pair<double, double> scale_factors = scale(m_dc, m_width, m_height);
    set_scale(scale_factors.first, scale_factors.second);

    draw_internal(m_dc);

    m_dc->restore();
}


/*
 *  Sets the drawing scale factors.
 */

void DrawnObject::set_scale(const double sx, const double sy) {
    m_dc->scale(sx, sy);
    m_scale_factor_x = sx;
    m_scale_factor_y = sy;
}


/*
 *  Default scale() member function.
 *
 *  This function does nothing, and is provided so that derived classes
 *  are not required to define it, if they don't need to scale.
 *
 *  The GCC "-Wunused parameter" warning is ignored since this function
 *  deliberately does nothing with its parameters.
 */

#pragma GCC diagnostic ignored "-Wunused-parameter"

std::pair<double, double>
DrawnObject::scale(PDC dc, const double width, const double height) {
    return std::pair<double, double>(1, 1);
}

#pragma GCC diagnostic pop


/*
 *  Returns the width of the drawing area in logical scaled units.
 */

double DrawnObject::width() const {
    return m_width / m_scale_factor_x;
}


/*
 *  Returns the height of the drawing area in logical scaled units.
 */

double DrawnObject::height() const {
    return m_height / m_scale_factor_y;
}
