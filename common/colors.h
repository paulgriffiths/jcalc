/*
 *  color.h
 *  =======
 *  Copyright 2013 Paul Griffiths
 *  Email: mail@paulgriffiths.net
 *
 *  Interface to color structures and stock colors.
 *
 *  Distributed under the terms of the GNU General Public License.
 *  http://www.gnu.org/licenses/
 */


#ifndef PG_JCALC_COLORS_H
#define PG_JCALC_COLORS_H

namespace jcalc {

/*
 *  Struct for holding an RGB color tuple.
 *
 *  Also defines a number of stock colors represented as RGB structs,
 *  the colors being those defined in the HTML and CSS color
 *  specification.
 */

struct RGB {
    double red;
    double green;
    double blue;

    RGB() :
        red(0), green(0), blue(0) {}
    RGB(const double red, const double green, const double blue) :
        red(red), green(green), blue(blue) {}

    static const RGB stock_AliceBlue;
    static const RGB stock_AntiqueWhite;
    static const RGB stock_Aqua;
    static const RGB stock_Aquamarine;
    static const RGB stock_Azure;
    static const RGB stock_Beige;
    static const RGB stock_Bisque;
    static const RGB stock_Black;
    static const RGB stock_BlanchedAlmond;
    static const RGB stock_Blue;
    static const RGB stock_BlueViolet;
    static const RGB stock_Brown;
    static const RGB stock_BurlyWood;
    static const RGB stock_CadetBlue;
    static const RGB stock_Chartreuse;
    static const RGB stock_Chocolate;
    static const RGB stock_Coral;
    static const RGB stock_CornflowerBlue;
    static const RGB stock_Cornsilk;
    static const RGB stock_Crimson;
    static const RGB stock_Cyan;
    static const RGB stock_DarkBlue;
    static const RGB stock_DarkCyan;
    static const RGB stock_DarkGoldenRod;
    static const RGB stock_DarkGray;
    static const RGB stock_DarkGreen;
    static const RGB stock_DarkKhaki;
    static const RGB stock_DarkMagenta;
    static const RGB stock_DarkOliveGreen;
    static const RGB stock_DarkOrange;
    static const RGB stock_DarkOrchid;
    static const RGB stock_DarkRed;
    static const RGB stock_DarkSalmon;
    static const RGB stock_DarkSeaGreen;
    static const RGB stock_DarkSlateBlue;
    static const RGB stock_DarkSlateGray;
    static const RGB stock_DarkTurquoise;
    static const RGB stock_DarkViolet;
    static const RGB stock_DeepPink;
    static const RGB stock_DeepSkyBlue;
    static const RGB stock_DimGray;
    static const RGB stock_DodgerBlue;
    static const RGB stock_FireBrick;
    static const RGB stock_FloralWhite;
    static const RGB stock_ForestGreen;
    static const RGB stock_Fuchsia;
    static const RGB stock_Gainsboro;
    static const RGB stock_GhostWhite;
    static const RGB stock_Gold;
    static const RGB stock_GoldenRod;
    static const RGB stock_Gray;
    static const RGB stock_Green;
    static const RGB stock_GreenYellow;
    static const RGB stock_HoneyDew;
    static const RGB stock_HotPink;
    static const RGB stock_IndianRed;
    static const RGB stock_Indigo;
    static const RGB stock_Ivory;
    static const RGB stock_Khaki;
    static const RGB stock_Lavender;
    static const RGB stock_LavenderBlush;
    static const RGB stock_LawnGreen;
    static const RGB stock_LemonChiffon;
    static const RGB stock_LightBlue;
    static const RGB stock_LightCoral;
    static const RGB stock_LightCyan;
    static const RGB stock_LightGoldenRodYellow;
    static const RGB stock_LightGray;
    static const RGB stock_LightGreen;
    static const RGB stock_LightPink;
    static const RGB stock_LightSalmon;
    static const RGB stock_LightSeaGreen;
    static const RGB stock_LightSkyBlue;
    static const RGB stock_LightSlateGray;
    static const RGB stock_LightSteelBlue;
    static const RGB stock_LightYellow;
    static const RGB stock_Lime;
    static const RGB stock_LimeGreen;
    static const RGB stock_Linen;
    static const RGB stock_Magenta;
    static const RGB stock_Maroon;
    static const RGB stock_MediumAquaMarine;
    static const RGB stock_MediumBlue;
    static const RGB stock_MediumOrchid;
    static const RGB stock_MediumPurple;
    static const RGB stock_MediumSeaGreen;
    static const RGB stock_MediumSlateBlue;
    static const RGB stock_MediumSpringGreen;
    static const RGB stock_MediumTurquoise;
    static const RGB stock_MediumVioletRed;
    static const RGB stock_MidnightBlue;
    static const RGB stock_MintCream;
    static const RGB stock_MistyRose;
    static const RGB stock_Moccasin;
    static const RGB stock_NavajoWhite;
    static const RGB stock_Navy;
    static const RGB stock_OldLace;
    static const RGB stock_Olive;
    static const RGB stock_OliveDrab;
    static const RGB stock_Orange;
    static const RGB stock_OrangeRed;
    static const RGB stock_Orchid;
    static const RGB stock_PaleGoldenRod;
    static const RGB stock_PaleGreen;
    static const RGB stock_PaleTurquoise;
    static const RGB stock_PaleVioletRed;
    static const RGB stock_PapayaWhip;
    static const RGB stock_PeachPuff;
    static const RGB stock_Peru;
    static const RGB stock_Pink;
    static const RGB stock_Plum;
    static const RGB stock_PowderBlue;
    static const RGB stock_Purple;
    static const RGB stock_Red;
    static const RGB stock_RosyBrown;
    static const RGB stock_RoyalBlue;
    static const RGB stock_SaddleBrown;
    static const RGB stock_Salmon;
    static const RGB stock_SandyBrown;
    static const RGB stock_SeaGreen;
    static const RGB stock_SeaShell;
    static const RGB stock_Sienna;
    static const RGB stock_Silver;
    static const RGB stock_SkyBlue;
    static const RGB stock_SlateBlue;
    static const RGB stock_SlateGray;
    static const RGB stock_Snow;
    static const RGB stock_SpringGreen;
    static const RGB stock_SteelBlue;
    static const RGB stock_Tan;
    static const RGB stock_Teal;
    static const RGB stock_Thistle;
    static const RGB stock_Tomato;
    static const RGB stock_Turquoise;
    static const RGB stock_Violet;
    static const RGB stock_Wheat;
    static const RGB stock_White;
    static const RGB stock_WhiteSmoke;
    static const RGB stock_Yellow;
    static const RGB stock_YellowGreen;
};


/*
 *  Struct for RGB tuple plus alpha (transparency) information.
 */

struct RGBA {
    double red;
    double green;
    double blue;
    double alpha;

    RGBA() :
        red(0), green(0), blue(0), alpha(1) {}
    RGBA(const RGB& rgb, const double alpha) :
        red(rgb.red), green(rgb.green),
        blue(rgb.blue), alpha(alpha) {}
    RGBA(const double red, const double green,
         const double blue, const double alpha) :
        red(red), green(green), blue(blue), alpha(alpha) {}
};

}           //  namespace jcalc

#endif          // PG_JCALC_COLORS_H
