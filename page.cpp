/*
 *  page.cpp
 *  ========
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Implementation of jcalc page object.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */

#include "page.h"
#include "drawing_context.h"

using namespace jcalc;

Page::Page(PDC dc) :
    m_dc(dc) {
}

void Page::show_page() {
    const int width = m_dc->width();
    const int height = m_dc->height();

    m_dc->set_color(RGB::stock_SpringGreen);
    Point p1(50, 50);
    Point p2(width - 50, height - 50);
    m_dc->rectangle(p1, p2);
    Point p3(100, 100);
    m_dc->rectangle(p3, width - 200, height - 200);
    m_dc->stroke();
    m_dc->show_page();
}
