/*
 *  drawing_context.h
 *  =================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Interface to drawing context.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#ifndef PG_JCALC_DRAWING_CONTEXT_H
#define PG_JCALC_DRAWING_CONTEXT_H

#include <string>
#include "jcalc_common_types.h"

namespace jcalc {

class DrawingContext {
    public:
        explicit DrawingContext(const std::string& filename,
                                const int width,
                                const int height);
        virtual ~DrawingContext() = 0;

        virtual void save() = 0;
        virtual void restore() = 0;
        virtual void set_line_width(const double width) = 0;
        virtual void set_color(const RGB& rgb) = 0;
        virtual void set_color_alpha(const RGBA& rgba) = 0;
        virtual void move_to(const Point& pt) = 0;
        virtual void line_to(const Point& pt) = 0;
        virtual void rectangle(const Point& topleft,
                               const Point& bottomright) = 0;
        virtual void rectangle(const Point& topleft,
                               const double width,
                               const double height) = 0;
        virtual void stroke() = 0;

        double width() const;
        double height() const;
        virtual void show_page() = 0;

    private:
        const std::string m_filename;
        const int m_width;
        const int m_height;
};

}

#endif          // PG_JCALC_DRAWING_CONTEXT_H
