/*
 *  flange.h
 *  ========
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Interface to flange drawn object.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#ifndef PG_DRAWN_FLANGE_H
#define PG_DRAWN_FLANGE_H

#include "drawn_common.h"
#include "drawn_object.h"

namespace jcalc {

/*
 *  Struct for containing information about a flange
 */

struct FlangeInfo {
    const std::string name;
    const double hd;
    const double fd;
    const double ft;
    const double bcd;
    const double bhd;
    const double nb;
    const double rfd;
    const double rfh;

    static const FlangeInfo F100PN16;
    static const FlangeInfo F125PN16;
    static const FlangeInfo F150PN16;
    static const FlangeInfo F200PN16;
    static const FlangeInfo F250PN16;
    static const FlangeInfo F300PN16;
    static const FlangeInfo F400PN16;

    FlangeInfo(const std::string& name,
               const double hd, const double fd,
               const double ft, const double bcd,
               const double bhd, const double nb,
               const double rfd, const double rfh) :
        name(name),
        hd(hd), fd(fd), ft(ft), bcd(bcd),
        bhd(bhd), nb(nb), rfd(rfd), rfh(rfh) {}
    FlangeInfo(const FlangeInfo& flange) :
        name(flange.name),
        hd(flange.hd), fd(flange.fd),
        ft(flange.ft), bcd(flange.bcd),
        bhd(flange.bhd), nb(flange.nb),
        rfd(flange.rfd), rfh(flange.rfh) {}
};


/*
 *  Flange drawn object class.
 */

class Flange : public DrawnObject {
    public:
        explicit Flange(PDC dc, const Point& origin,
                        const double angle,
                        const FlangeInfo& fi);
        virtual ~Flange();

    private:
        virtual void draw_internal(PDC dc);
        void draw_profile(PDC dc, const double angle);

        const FlangeInfo& m_fi;
        const double m_angle;
};

}           //  namespace jcalc

#endif          // PG_DRAWN_FLANGE_H
