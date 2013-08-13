/*
 *  drawing_context.h
 *  =================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Interface to drawing context abstract base class.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#ifndef PG_JCALC_DRAWING_CONTEXT_H
#define PG_JCALC_DRAWING_CONTEXT_H

#include <string>
#include <memory>
#include "contexts_common.h"

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
        virtual void set_scaled_line_width(const double width) = 0;
        virtual void set_color(const RGB& rgb) = 0;
        virtual void set_color_alpha(const RGBA& rgba) = 0;

        virtual void translate(const double tx, const double ty) = 0;
        virtual void scale(const double sx, const double sy) = 0;
        virtual void rotate(const double degrees) = 0;

        virtual void move_to(const Point& pt) = 0;
        virtual void line_to(const Point& pt) = 0;
        virtual void rectangle(const Point& topleft,
                               const Point& bottomright) = 0;
        virtual void rectangle(const Point& topleft,
                               const double width,
                               const double height) = 0;
        virtual void arc(const Point& center, const double radius,
                         const double start_degrees,
                         const double end_degrees,
                         const bool reverse = false) = 0;

        virtual void stroke() = 0;
        virtual void stroke_preserve() = 0;
        virtual void fill() = 0;
        virtual void fill_preserve() = 0;
        virtual void close_path() = 0;
        virtual void paint() = 0;

        virtual void solid_line() = 0;
        virtual void scaled_dashed_line() = 0;

        double width() const;
        double height() const;
        virtual void show_page() = 0;

        //  Enumerations for factory function

        enum class Backend {null, cairo};
        enum class Output {pdf, svg, png};

    private:
        const std::string m_filename;
        const int m_width;
        const int m_height;
};


/*
 *  Typedef for polymorphic std::shared_ptr to a drawing context.
 */

typedef std::shared_ptr<DrawingContext> PDC;


/*
 *  Standalone factory function for creating drawing contexts.
 */

PDC drawing_context_factory(const DrawingContext::Backend backend,
                            const DrawingContext::Output output,
                            const std::string& filename,
                            const int width,
                            const int height);

}           //  namespace jcalc

#endif          // PG_JCALC_DRAWING_CONTEXT_H
