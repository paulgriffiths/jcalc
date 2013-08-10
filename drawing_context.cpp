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
#include "drawing_context.h"

using namespace jcalc;

DrawingContext::DrawingContext(const std::string& filename,
                               const int width,
                               const int height) :
    m_filename(filename),
    m_width(width),
    m_height(height) {
}

DrawingContext::~DrawingContext() {
}

double DrawingContext::width() const {
    return m_width;
}

double DrawingContext::height() const {
    return m_height;
}
