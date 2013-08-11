/*
 *  drawing_context.cpp
 *  ===================
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Implementation of drawing context
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */

#include <string>
#include "contexts_common.h"
#include "drawing_context.h"
#include "contexts.h"

using namespace jcalc;


/*
 *  Constructor.
 */

DrawingContext::DrawingContext(const std::string& filename,
                               const int width,
                               const int height) :
    m_filename(filename),
    m_width(width),
    m_height(height) {
}


/*
 *  Provide definition for virtual destructor.
 */

DrawingContext::~DrawingContext() {
}


/*
 *  Returns the width of the drawing context.
 */

double DrawingContext::width() const {
    return m_width;
}


/*
 *  Returns the height of the drawing context.
 */

double DrawingContext::height() const {
    return m_height;
}


/*
 *  Standalone factory function for creating new drawing contexts.
 *
 *  Arguments:
 *    backend - the requested backend, e.g. 'cairo'
 *    output - the requested for of output, e.g. 'pdf', 'svg'
 *    filename - the name of the output file to be created.
 *    width - desired width of the drawing context.
 *    height - desired height of the drawing context.
 *
 *  Returns:
 *    A std::shared_ptr<DrawingContext> pointing at the newly created
 *    drawing context.
 */

PDC jcalc::drawing_context_factory(const DrawingContext::Backend backend,
                                   const DrawingContext::Output output,
                                   const std::string& filename,
                                   const int width,
                                   const int height) {
    switch ( backend ) {
        case DrawingContext::Backend::null:
            return PDC(new NullDrawingContext(filename, width, height));

        case DrawingContext::Backend::cairo:
            switch ( output ) {
                case DrawingContext::Output::pdf:
                    return PDC(new CairoPDFDrawingContext(filename,
                                                          width,
                                                          height));

                case DrawingContext::Output::svg:
                    return PDC(new CairoSVGDrawingContext(filename,
                                                          width,
                                                          height));

                case DrawingContext::Output::png:
                    throw unsupported_output("png");
            }
    }

    //  We shouldn't ever get here, but just in case.

    return nullptr;
}
