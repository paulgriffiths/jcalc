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

void do_drawing();


int main(void) {
    try {
        do_drawing();
    } catch(jcalc::jcalc_exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    std::cout << "Drawing successfully created." << std::endl;

    return 0;
}


/*
 *  Temporary function for testing purposes, ultimately the type
 *  of object drawn and the parameters thereto will be obtained
 *  from the command line or a configuration file.
 */

void do_drawing() {
    jcalc::PDC pdc(jcalc::drawing_context_factory(
            jcalc::DrawingContext::Backend::cairo,
            jcalc::DrawingContext::Output::svg,
            "outfile.svg", 612, 792));
    jcalc::Page page(pdc);
    page.show_page();
}
