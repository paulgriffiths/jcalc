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
#include "contexts_common.h"
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

        virtual void translate(const double tx, const double ty);
        virtual void scale(const double sx, const double sy);
        virtual void rotate(const double degrees);

        virtual void move_to(const Point& pt);
        virtual void line_to(const Point& pt);
        virtual void rectangle(const Point& topleft,
                               const Point& bottomright);
        virtual void rectangle(const Point& topleft,
                               const double width,
                               const double height);
        virtual void arc(const Point& center, const double radius,
                         const double start_degrees,
                         const double end_degrees,
                         const bool reverse = false);

        virtual void stroke();
        virtual void stroke_preserve();
        virtual void fill();
        virtual void fill_preserve();
        virtual void close_path();
        virtual void paint();

        virtual void solid_line();
        virtual void scaled_dashed_line();

    private:
        Cairo::RefPtr<Cairo::Surface> m_surface;
        Cairo::RefPtr<Cairo::Context> m_cr;
};

}           //  namespace jcalc

#endif          // PG_JCALC_CAIRO_DRAWING_CONTEXT_H
