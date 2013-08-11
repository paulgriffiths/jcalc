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
    std::cout << "Main is running." << std::endl;
    try {
        do_drawing();
    } catch(jcalc::jcalc_exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}

void do_drawing() {
    //jcalc::PDC pdc(jcalc::drawing_context_factory(
    //        jcalc::DrawingContext::Backend::null,
    //        jcalc::DrawingContext::Output::pdf,
    //        "outfile", 400, 600));

    jcalc::PDC pdc(jcalc::drawing_context_factory(
           jcalc::DrawingContext::Backend::cairo,
            jcalc::DrawingContext::Output::svg,
            "outfile", 400, 600));

    jcalc::Page page(pdc);
    page.show_page();
}
