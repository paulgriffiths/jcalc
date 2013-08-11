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
#include "context.h"
#include "drawns/pipe_bend.h"

using namespace jcalc;

Page::Page(PDC dc) :
    m_dc(dc) {
}

void Page::show_page() {
    const int width = m_dc->width();
    const int height = m_dc->height();

    m_dc->set_color(RGB::stock_White);
    m_dc->paint();

    m_dc->set_color(RGB::stock_Black);
    m_dc->set_line_width(1);
    m_dc->rectangle(Point(50, 50), Point(width - 50, height - 50));
    m_dc->rectangle(Point(55, 550), Point(width - 55, height - 55));
    m_dc->stroke();

    PipeBendInfo pbi(60, 15, 300, 200, 170, 140, 100);
    PipeBend pb(m_dc, Point(60, 60), width - 120, 480, pbi);
    pb.draw();

    m_dc->show_page();
}
