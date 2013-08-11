/*
 *  page.h
 *  ======
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Interface to jcalc page object.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#ifndef PG_JCALC_PAGE_H
#define PG_JCALC_PAGE_H

#include "context.h"

namespace jcalc {

class Page {
    public:
        explicit Page(PDC dc);

        void show_page();

    private:
        PDC m_dc;
};

}           //  namespace jcalc

#endif          // PG_JCALC_PAGE_H
