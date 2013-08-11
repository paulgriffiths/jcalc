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
#include "drawn_circle_cross.h"

using namespace jcalc;

Page::Page(PDC dc) :
    m_dc(dc) {
}

void Page::show_page() {
    const int width = m_dc->width();
    const int height = m_dc->height();

    m_dc->set_color(RGB::stock_White);
    m_dc->paint();
    m_dc->set_color(RGB::stock_SpringGreen);
    Point p1(50, 50);
    Point p2(width - 50, height - 50);
    m_dc->rectangle(p1, p2);
    Point p3(100, 100);
    m_dc->rectangle(p3, width - 200, height - 200);
    m_dc->stroke();

    CircleCross ccross1(m_dc, Point(75, 75), 200, 200);
    ccross1.draw();

    CircleCross ccross2(m_dc, Point(150, 250), 400, 400);
    ccross2.draw();

    CircleCross ccross3(m_dc, Point(125, 500), 50, 50);
    ccross3.draw();

    CircleCross ccross4(m_dc, Point(400, 550), 100, 100);
    ccross4.draw();

    m_dc->show_page();
}
