/*
 *  cairo_pdf_drawing_context.cpp
 *  =============================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Implementation of Cairo PDF drawing context
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */

#include <string>
#include <cairommconfig.h>
#include <cairomm/context.h>
#include <cairomm/surface.h>
#include "cairo_pdf_drawing_context.h"

using namespace jcalc;

CairoPDFDrawingContext::CairoPDFDrawingContext(const std::string& filename,
                                               const int width,
                                               const int height) :
    CairoDrawingContext(Cairo::PdfSurface::create(filename, width, height),
                        filename, width, height) {
}

CairoPDFDrawingContext::~CairoPDFDrawingContext() {
}
