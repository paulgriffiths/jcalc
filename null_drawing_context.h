/*
 *  null_drawing_context.h
 *  =======================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Interface to a do-nothing drawing context.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#ifndef PG_JCALC_NULL_DRAWING_CONTEXT_H
#define PG_JCALC_NULL_DRAWING_CONTEXT_H

#include <string>
#include <memory>
#include "jcalc_common_types.h"

namespace jcalc {

class NullDrawingContext : public DrawingContext {
    public:
        explicit NullDrawingContext(const std::string& filename,
                                const int width,
                                const int height) :
            DrawingContext(filename, width, height) {}
        virtual ~NullDrawingContext() {};

#pragma GCC diagnostic ignored "-Wunused-parameter"

        //  Ignore GCCs -Wunused-parameter warnings, since tihs
        //  is a deliberate "do-nothing" class.

        virtual void save() {};
        virtual void restore() {};

        virtual void translate(const double tx, const double ty) {};
        virtual void scale(const double sx, const double sy) {};
        virtual void rotate(const double degrees) {};

        virtual void set_line_width(const double width) {};
        virtual void set_color(const RGB& rgb) {};
        virtual void set_color_alpha(const RGBA& rgba) {};
        virtual void move_to(const Point& pt) {};
        virtual void line_to(const Point& pt) {};
        virtual void rectangle(const Point& topleft,
                               const Point& bottomright) {};
        virtual void rectangle(const Point& topleft,
                               const double width,
                               const double height) {};
        virtual void arc(const Point& center, const double radius,
                         const double start_degrees,
                         const double end_degrees,
                         const bool reverse = false) {};
        virtual void stroke() {};
        virtual void stroke_preserve() {};
        virtual void fill() {};
        virtual void fill_preserve() {};
        virtual void paint() {};

        virtual void show_page() {};

#pragma GCC diagnostic pop

};

}

#endif          // PG_JCALC_NULL_DRAWING_CONTEXT_H
