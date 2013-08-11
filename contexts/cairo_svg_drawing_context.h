/*
 *  cairo_svg_drawing_context.h
 *  ===========================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Interface to Cairo SVG drawing context.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#ifndef PG_JCALC_CAIRO_SVG_DRAWING_CONTEXT_H
#define PG_JCALC_CAIRO_SVG_DRAWING_CONTEXT_H

#include <string>
#include "contexts_common.h"
#include "cairo_drawing_context.h"

namespace jcalc {

class CairoSVGDrawingContext : public CairoDrawingContext {
    public:
        explicit CairoSVGDrawingContext(const std::string& filename,
                                        const int width,
                                        const int height);
        virtual ~CairoSVGDrawingContext();
};

}           //  namespace jcalc

#endif          // PG_JCALC_CAIRO_SVG_DRAWING_CONTEXT_H
