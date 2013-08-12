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


/*
 *  Constructor, takes a base class pointer to a drawing context as
 *  an argument.
 */

Page::Page(PDC dc) :
    m_dc(dc) {
}


/*
 *  Draw and create the whole page.
 */

void Page::show_page() {
    const int width = m_dc->width();
    const int height = m_dc->height();
    const int margin = 50;
    const int padding = 5;
    const int int_margin = margin + padding;
    const int info_box_height = 200;

    //  Paint entire background white.

    m_dc->set_color(RGB::stock_White);
    m_dc->paint();

    //  Draw main margin and info box

    m_dc->set_color(RGB::stock_Black);
    m_dc->set_line_width(1);
    m_dc->rectangle(Point(margin, margin),
                    Point(width - margin, height - margin));
    m_dc->rectangle(Point(int_margin, height - int_margin - info_box_height),
                    Point(width - int_margin, height - int_margin));
    m_dc->stroke();

    // TODO: create, populate and draw the info box.

    //  For test purposes, create and draw pipe bend object. Ultimately
    //  the type of object and parameters thereto will be specified on
    //  the command line and/or in a configuration file.

    PipeBendInfo pbi(60, 15, 600, 250, 230, 200, 150);
    PipeBend pb(m_dc, Point(int_margin, int_margin), width - int_margin * 2,
                height - int_margin * 2 - padding - info_box_height, pbi,
                FlangeInfo::F150PN16);
    pb.draw();

    //  Create the page.

    m_dc->show_page();
}
