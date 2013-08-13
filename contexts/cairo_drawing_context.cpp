/*
 *  cairo_drawing_context.cpp
 *  =========================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Implementation of Cairo drawing context
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */

#include <string>
#include <cairommconfig.h>
#include <cairomm/context.h>
#include <cairomm/surface.h>
#include "contexts_common.h"
#include "cairo_drawing_context.h"

using namespace jcalc;


/*
 *  Constructor.
 */

CairoDrawingContext::CairoDrawingContext(Cairo::RefPtr<Cairo::Surface> surface,
                                         const std::string& filename,
                                         const int width,
                                         const int height) :
    DrawingContext(filename, width, height),
    m_surface(surface),
    m_cr(Cairo::Context::create(m_surface)) {
}


/*
 *  Destructor.
 */

CairoDrawingContext::~CairoDrawingContext() {
}


/*
 *  Virtual drawing member functions.
 */

void CairoDrawingContext::show_page() {
    m_cr->show_page();
}

void CairoDrawingContext::save() {
    m_cr->save();
}

void CairoDrawingContext::restore() {
    m_cr->restore();
}

void CairoDrawingContext::set_line_width(const double width) {
    m_cr->set_line_width(width);
}

void CairoDrawingContext::set_scaled_line_width(const double width) {
    double x = 1;
    double y = 1;

    m_cr->device_to_user_distance(x, y);

    m_cr->set_line_width(width * x);
}

void CairoDrawingContext::set_color(const RGB& rgb) {
    m_cr->set_source_rgb(rgb.red, rgb.green, rgb.blue);
}

void CairoDrawingContext::set_color_alpha(const RGBA& rgba) {
    m_cr->set_source_rgba(rgba.red, rgba.green, rgba.blue, rgba.alpha);
}

void CairoDrawingContext::translate(const double tx, const double ty) {
    m_cr->translate(tx, ty);
}

void CairoDrawingContext::scale(const double sx, const double sy) {
    m_cr->scale(sx, sy);
}

void CairoDrawingContext::rotate(const double degrees) {
    m_cr->rotate_degrees(degrees);
}

void CairoDrawingContext::move_to(const Point& pt) {
    m_cr->move_to(pt.x, pt.y);
}

void CairoDrawingContext::line_to(const Point& pt) {
    m_cr->line_to(pt.x, pt.y);
}

void CairoDrawingContext::rectangle(const Point& topleft,
                                    const Point& bottomright) {
    m_cr->rectangle(topleft.x, topleft.y,
                    bottomright.x - topleft.x,
                    bottomright.y - topleft.y);
}

void CairoDrawingContext::rectangle(const Point& topleft,
                                    const double width,
                                    const double height) {
    m_cr->rectangle(topleft.x, topleft.y, width, height);
}

void CairoDrawingContext::arc(const Point& center, const double radius,
                              const double start_degrees,
                              const double end_degrees,
                              const bool reverse) {
    if ( reverse ) {
        m_cr->arc_negative(center.x, center.y, radius,
                           mathhelp::radians(start_degrees),
                           mathhelp::radians(end_degrees));
    } else {
        m_cr->arc(center.x, center.y, radius,
                  mathhelp::radians(start_degrees),
                  mathhelp::radians(end_degrees));
    }
}

void CairoDrawingContext::stroke() {
    m_cr->stroke();
}

void CairoDrawingContext::stroke_preserve() {
    m_cr->stroke_preserve();
}

void CairoDrawingContext::fill() {
    m_cr->fill();
}

void CairoDrawingContext::fill_preserve() {
    m_cr->fill_preserve();
}

void CairoDrawingContext::close_path() {
    m_cr->close_path();
}

void CairoDrawingContext::paint() {
    m_cr->paint();
}

void CairoDrawingContext::solid_line() {
    static const std::vector<double> solid_dash;
    m_cr->set_dash(solid_dash, 0);
}

void CairoDrawingContext::scaled_dashed_line() {
    std::vector<double> dashes = {7, 2, 2, 2};

    double x = 1;
    double y = 1;

    m_cr->device_to_user_distance(x, y);

    for ( std::vector<double>::iterator itr = dashes.begin();
          itr != dashes.end(); ++itr ) {
        *itr = *itr * x;
    }

    m_cr->set_dash(dashes, 0);
}

