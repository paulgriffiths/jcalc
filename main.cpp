/*
 *  main.cpp
 *  ========
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Entry point to jcalc.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */

#include <iostream>
#include "jcalc.h"

int main(void) {
    jcalc::CairoDrawingContext cdc("outfile", 400, 600);
    jcalc::Page page(cdc);
    std::cout << "Main is running." << std::endl;
    page.show_page();
    return 0;
}
