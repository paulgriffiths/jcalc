/*
 *  cairo_pdf_drawing_context.h
 *  =======================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Interface to Cairo PDF drawing context.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#ifndef PG_JCALC_CAIRO_PDF_DRAWING_CONTEXT_H
#define PG_JCALC_CAIRO_PDF_DRAWING_CONTEXT_H

#include <string>
#include "cairo_drawing_context.h"

namespace jcalc {

class CairoPDFDrawingContext : public CairoDrawingContext {
    public:
        explicit CairoPDFDrawingContext(const std::string& filename,
                                        const int width,
                                        const int height);
        virtual ~CairoPDFDrawingContext();
};

}

#endif          // PG_JCALC_CAIRO_PDF_DRAWING_CONTEXT_H
