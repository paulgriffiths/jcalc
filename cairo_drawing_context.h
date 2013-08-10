/*
 *  cairo_drawing_context.h
 *  =======================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Interface to Cairo drawing context.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#ifndef PG_JCALC_CAIRO_DRAWING_CONTEXT_H
#define PG_JCALC_CAIRO_DRAWING_CONTEXT_H

#include <string>
#include <cairommconfig.h>
#include <cairomm/context.h>
#include <cairomm/surface.h>
#include "drawing_context.h"

namespace jcalc {

class CairoDrawingContext : public DrawingContext {
    public:
        explicit CairoDrawingContext(Cairo::RefPtr<Cairo::Surface> surface,
                                     const std::string& filename,
                                     const int width,
                                     const int height);
        virtual ~CairoDrawingContext();

        virtual void show_page();

        virtual void save();
        virtual void restore();
        virtual void set_line_width(const double width);
        virtual void set_color(const RGB& rgb);
        virtual void set_color_alpha(const RGBA& rgba);
        virtual void move_to(const Point& pt);
        virtual void line_to(const Point& pt);
        virtual void rectangle(const Point& topleft,
                               const Point& bottomright);
        virtual void rectangle(const Point& topleft,
                               const double width,
                               const double height);
        virtual void stroke();

    private:
        Cairo::RefPtr<Cairo::Surface> m_surface;
        Cairo::RefPtr<Cairo::Context> m_cr;
};

}

#endif          // PG_JCALC_CAIRO_DRAWING_CONTEXT_H
