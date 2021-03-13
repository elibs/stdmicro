#include "DejaVuSerif.h"

#include "Path.h"
/**
 * Font generated via use of converter.py, from DejaVuSerif font, which is
 * distributed under the license of:
 *
 * Bitstream Vera and Public Domain
 *
 * Converted to svg with FontForge.
 *
 * NOTE: Glyphs were removed to reduce overall size.
 */

DejaVuSerif::~DejaVuSerif(void)
{
}

glyph DejaVuSerif::operator[](int character) const
{
    switch (character)
    {
        case ' ': return space;
        case '!': return exclam;
        case '"': return quotedbl;
        case '#': return numbersign;
        case '$': return dollar;
        case '%': return percent;
        case '&': return ampersand;
        case '\'': return quotesingle;
        case '(': return parenleft;
        case ')': return parenright;
        case '*': return asterisk;
        case '+': return plus;
        case ',': return comma;
        case '-': return hyphen;
        case '.': return period;
        case '/': return slash;
        case '0': return zero;
        case '1': return one;
        case '2': return two;
        case '3': return three;
        case '4': return four;
        case '5': return five;
        case '6': return six;
        case '7': return seven;
        case '8': return eight;
        case '9': return nine;
        case ':': return colon;
        case ';': return semicolon;
        case '<': return less;
        case '=': return equal;
        case '>': return greater;
        case '?': return question;
        case '@': return at;
        case 'A': return A;
        case 'B': return B;
        case 'C': return C;
        case 'D': return D;
        case 'E': return E;
        case 'F': return F;
        case 'G': return G;
        case 'H': return H;
        case 'I': return I;
        case 'J': return J;
        case 'K': return K;
        case 'L': return L;
        case 'M': return M;
        case 'N': return N;
        case 'O': return O;
        case 'P': return P;
        case 'Q': return Q;
        case 'R': return R;
        case 'S': return S;
        case 'T': return T;
        case 'U': return U;
        case 'V': return V;
        case 'W': return W;
        case 'X': return X;
        case 'Y': return Y;
        case 'Z': return Z;
        case '[': return bracketleft;
        case '\\': return backslash;
        case ']': return bracketright;
        case '^': return asciicircum;
        case '_': return underscore;
        case '`': return grave;
        case 'a': return a;
        case 'b': return b;
        case 'c': return c;
        case 'd': return d;
        case 'e': return e;
        case 'f': return f;
        case 'g': return g;
        case 'h': return h;
        case 'i': return i;
        case 'j': return j;
        case 'k': return k;
        case 'l': return l;
        case 'm': return m;
        case 'n': return n;
        case 'o': return o;
        case 'p': return p;
        case 'q': return q;
        case 'r': return r;
        case 's': return s;
        case 't': return t;
        case 'u': return u;
        case 'v': return v;
        case 'w': return w;
        case 'x': return x;
        case 'y': return y;
        case 'z': return z;
        case '{': return braceleft;
        case '|': return bar;
        case '}': return braceright;
        case '~': return asciitilde;
        default:
            return none;
    }
}
em DejaVuSerif::space(EmBox* box)
{
    return 651;
}

em DejaVuSerif::exclam(EmBox* box)
{
    Path pathSegment0 = Path::start({279.0, 104.0});
    pathSegment0.
        quadratic({279.0, 160.0}, {317.0, 199.0})->
        quadratic({355.0, 238.0}, {412.0, 238.0})->
        quadratic({467.0, 238.0}, {506.0, 199.0})->
        quadratic({545.0, 160.0}, {545.0, 104.0})->
        quadratic({545.0, 49.0}, {506.0, 10.0})->
        quadratic({467.0, -29.0}, {412.0, -29.0})->
        quadratic({355.0, -29.0}, {317.0, 9.5})->
        quadratic({279.0, 48.0}, {279.0, 104.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    Path pathSegment1 = Path::start({283.0, 1493.0});
    pathSegment1.
        line({541.0, 1493.0})->
        line({473.0, 672.0})->
        line({473.0, 420.0})->
        line({350.0, 420.0})->
        line({350.0, 672.0})->
        close(&pathSegment1);
    pathSegment1.drawTo(box);

    return 823;
}

em DejaVuSerif::quotedbl(EmBox* box)
{
    Path pathSegment0 = Path::start({360.0, 1493.0});
    pathSegment0.
        line({360.0, 938.0})->
        line({201.0, 938.0})->
        line({201.0, 1493.0})->
        line({360.0, 1493.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    Path pathSegment1 = Path::start({741.0, 1493.0});
    pathSegment1.
        line({741.0, 938.0})->
        line({582.0, 938.0})->
        line({582.0, 1493.0})->
        line({741.0, 1493.0})->
        close(&pathSegment1);
    pathSegment1.drawTo(box);

    return 942;
}

em DejaVuSerif::numbersign(EmBox* box)
{
    Path pathSegment0 = Path::start({1042.0, 901.0});
    pathSegment0.
        line({760.0, 901.0})->
        line({676.0, 567.0})->
        line({961.0, 567.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    Path pathSegment1 = Path::start({901.0, 1470.0});
    pathSegment1.
        line({799.0, 1055.0})->
        line({1081.0, 1055.0})->
        line({1184.0, 1470.0})->
        line({1356.0, 1470.0})->
        line({1251.0, 1055.0})->
        line({1559.0, 1055.0})->
        line({1559.0, 901.0})->
        line({1212.0, 901.0})->
        line({1130.0, 567.0})->
        line({1444.0, 567.0})->
        line({1444.0, 414.0})->
        line({1092.0, 414.0})->
        line({989.0, 0.0})->
        line({817.0, 0.0})->
        line({922.0, 414.0})->
        line({639.0, 414.0})->
        line({535.0, 0.0})->
        line({365.0, 0.0})->
        line({467.0, 414.0})->
        line({158.0, 414.0})->
        line({158.0, 567.0})->
        line({506.0, 567.0})->
        line({588.0, 901.0})->
        line({272.0, 901.0})->
        line({272.0, 1055.0})->
        line({627.0, 1055.0})->
        line({731.0, 1470.0})->
        line({901.0, 1470.0})->
        close(&pathSegment1);
    pathSegment1.drawTo(box);

    return 1716;
}

em DejaVuSerif::dollar(EmBox* box)
{
    Path pathSegment0 = Path::start({690.0, 68.0});
    pathSegment0.
        quadratic({803.0, 78.0}, {862.5, 133.0})->
        quadratic({922.0, 188.0}, {922.0, 283.0})->
        quadratic({922.0, 369.0}, {863.0, 429.0})->
        quadratic({804.0, 489.0}, {690.0, 520.0})->
        line({690.0, 68.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    Path pathSegment1 = Path::start({590.0, 1187.0});
    pathSegment1.
        quadratic({487.0, 1180.0}, {430.0, 1127.5})->
        quadratic({373.0, 1075.0}, {373.0, 987.0})->
        quadratic({373.0, 907.0}, {425.5, 854.0})->
        quadratic({478.0, 801.0}, {590.0, 768.0})->
        line({590.0, 1187.0})->
        close(&pathSegment1);
    pathSegment1.drawTo(box);

    Path pathSegment2 = Path::start({176.0, 72.0});
    pathSegment2.
        line({176.0, 348.0})->
        line({284.0, 348.0})->
        quadratic({288.0, 211.0}, {364.0, 141.0})->
        quadratic({440.0, 71.0}, {590.0, 68.0})->
        line({590.0, 553.0})->
        quadratic({360.0, 617.0}, {267.0, 700.5})->
        quadratic({174.0, 784.0}, {174.0, 922.0})->
        quadratic({174.0, 1082.0}, {284.0, 1179.0})->
        quadratic({394.0, 1276.0}, {590.0, 1288.0})->
        line({590.0, 1556.0})->
        line({690.0, 1556.0})->
        line({690.0, 1288.0})->
        quadratic({791.0, 1280.0}, {884.5, 1255.5})->
        quadratic({978.0, 1231.0}, {1067.0, 1190.0})->
        line({1067.0, 928.0})->
        line({958.0, 928.0})->
        quadratic({946.0, 1044.0}, {877.0, 1111.0})->
        quadratic({808.0, 1178.0}, {690.0, 1187.0})->
        line({690.0, 735.0})->
        quadratic({936.0, 668.0}, {1034.5, 581.5})->
        quadratic({1133.0, 495.0}, {1133.0, 350.0})->
        quadratic({1133.0, 184.0}, {1017.0, 84.0})->
        quadratic({901.0, -16.0}, {690.0, -31.0})->
        line({690.0, -301.0})->
        line({590.0, -301.0})->
        line({590.0, -31.0})->
        quadratic({494.0, -29.0}, {391.0, -3.5})->
        quadratic({288.0, 22.0}, {176.0, 72.0})->
        close(&pathSegment2);
    pathSegment2.drawTo(box);

    return 2000;
}

em DejaVuSerif::percent(EmBox* box)
{
    Path pathSegment0 = Path::start({459.0, 1427.0});
    pathSegment0.
        quadratic({371.0, 1427.0}, {321.5, 1344.0})->
        quadratic({272.0, 1261.0}, {272.0, 1112.0})->
        quadratic({272.0, 965.0}, {322.5, 881.0})->
        quadratic({373.0, 797.0}, {459.0, 797.0})->
        quadratic({544.0, 797.0}, {593.5, 880.5})->
        quadratic({643.0, 964.0}, {643.0, 1112.0})->
        quadratic({643.0, 1260.0}, {593.5, 1343.5})->
        quadratic({544.0, 1427.0}, {459.0, 1427.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    Path pathSegment1 = Path::start({1489.0, 694.0});
    pathSegment1.
        quadratic({1402.0, 694.0}, {1352.5, 610.0})->
        quadratic({1303.0, 526.0}, {1303.0, 377.0})->
        quadratic({1303.0, 230.0}, {1353.0, 146.5})->
        quadratic({1403.0, 63.0}, {1489.0, 63.0})->
        quadratic({1575.0, 63.0}, {1624.0, 146.5})->
        quadratic({1673.0, 230.0}, {1673.0, 377.0})->
        quadratic({1673.0, 525.0}, {1623.5, 609.5})->
        quadratic({1574.0, 694.0}, {1489.0, 694.0})->
        close(&pathSegment1);
    pathSegment1.drawTo(box);

    Path pathSegment2 = Path::start({1489.0, 784.0});
    pathSegment2.
        quadratic({1647.0, 784.0}, {1740.0, 674.0})->
        quadratic({1833.0, 564.0}, {1833.0, 377.0})->
        quadratic({1833.0, 190.0}, {1739.5, 80.5})->
        quadratic({1646.0, -29.0}, {1489.0, -29.0})->
        quadratic({1329.0, -29.0}, {1236.0, 80.5})->
        quadratic({1143.0, 190.0}, {1143.0, 377.0})->
        quadratic({1143.0, 565.0}, {1236.5, 674.5})->
        quadratic({1330.0, 784.0}, {1489.0, 784.0})->
        close(&pathSegment2);
    pathSegment2.drawTo(box);

    Path pathSegment3 = Path::start({1364.0, 1520.0});
    pathSegment3.
        line({1516.0, 1520.0})->
        line({582.0, -29.0})->
        line({430.0, -29.0})->
        close(&pathSegment3);
    pathSegment3.drawTo(box);

    Path pathSegment4 = Path::start({457.0, 1520.0});
    pathSegment4.
        quadratic({615.0, 1520.0}, {709.0, 1410.5})->
        quadratic({803.0, 1301.0}, {803.0, 1114.0})->
        quadratic({803.0, 925.0}, {709.5, 816.0})->
        quadratic({616.0, 707.0}, {457.0, 707.0})->
        quadratic({298.0, 707.0}, {205.5, 816.5})->
        quadratic({113.0, 926.0}, {113.0, 1114.0})->
        quadratic({113.0, 1300.0}, {206.0, 1410.0})->
        quadratic({299.0, 1520.0}, {457.0, 1520.0})->
        close(&pathSegment4);
    pathSegment4.drawTo(box);

    return 1946;
}

em DejaVuSerif::ampersand(EmBox* box)
{
    Path pathSegment0 = Path::start({1106.0, 231.0});
    pathSegment0.
        line({524.0, 844.0})->
        quadratic({437.0, 766.0}, {393.5, 675.5})->
        quadratic({350.0, 585.0}, {350.0, 483.0})->
        quadratic({350.0, 317.0}, {465.0, 204.5})->
        quadratic({580.0, 92.0}, {752.0, 92.0})->
        quadratic({854.0, 92.0}, {944.5, 127.5})->
        quadratic({1035.0, 163.0}, {1106.0, 231.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    Path pathSegment1 = Path::start({1726.0, 0.0});
    pathSegment1.
        line({1325.0, 0.0})->
        line({1188.0, 145.0})->
        quadratic({1083.0, 57.0}, {964.0, 14.0})->
        quadratic({845.0, -29.0}, {707.0, -29.0})->
        quadratic({449.0, -29.0}, {298.0, 103.0})->
        quadratic({147.0, 235.0}, {147.0, 461.0})->
        quadratic({147.0, 594.0}, {223.5, 709.5})->
        quadratic({300.0, 825.0}, {455.0, 926.0})->
        quadratic({404.0, 987.0}, {380.0, 1047.5})->
        quadratic({356.0, 1108.0}, {356.0, 1174.0})->
        quadratic({356.0, 1333.0}, {470.5, 1426.5})->
        quadratic({585.0, 1520.0}, {782.0, 1520.0})->
        quadratic({849.0, 1520.0}, {938.5, 1503.0})->
        quadratic({1028.0, 1486.0}, {1143.0, 1452.0})->
        line({1143.0, 1194.0})->
        line({1030.0, 1194.0})->
        quadratic({1016.0, 1301.0}, {952.0, 1357.0})->
        quadratic({888.0, 1413.0}, {778.0, 1413.0})->
        quadratic({675.0, 1413.0}, {611.0, 1356.5})->
        quadratic({547.0, 1300.0}, {547.0, 1210.0})->
        quadratic({547.0, 1149.0}, {581.0, 1088.5})->
        quadratic({615.0, 1028.0}, {723.0, 915.0})->
        line({1239.0, 371.0})->
        quadratic({1308.0, 451.0}, {1347.5, 543.5})->
        quadratic({1387.0, 636.0}, {1397.0, 741.0})->
        line({1217.0, 741.0})->
        line({1217.0, 848.0})->
        line({1690.0, 848.0})->
        line({1690.0, 741.0})->
        line({1518.0, 741.0})->
        quadratic({1501.0, 611.0}, {1451.5, 498.0})->
        quadratic({1402.0, 385.0}, {1319.0, 289.0})->
        line({1491.0, 106.0})->
        line({1726.0, 106.0})->
        line({1726.0, 0.0})->
        close(&pathSegment1);
    pathSegment1.drawTo(box);

    return 1823;
}

em DejaVuSerif::quotesingle(EmBox* box)
{
    Path pathSegment0 = Path::start({360.0, 1493.0});
    pathSegment0.
        line({360.0, 938.0})->
        line({201.0, 938.0})->
        line({201.0, 1493.0})->
        line({360.0, 1493.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    return 563;
}

em DejaVuSerif::parenleft(EmBox* box)
{
    Path pathSegment0 = Path::start({653.0, -319.0});
    pathSegment0.
        quadratic({410.0, -210.0}, {286.0, 26.5})->
        quadratic({162.0, 263.0}, {162.0, 618.0})->
        quadratic({162.0, 974.0}, {286.0, 1210.5})->
        quadratic({410.0, 1447.0}, {653.0, 1556.0})->
        line({653.0, 1458.0})->
        quadratic({499.0, 1352.0}, {432.0, 1159.5})->
        quadratic({365.0, 967.0}, {365.0, 618.0})->
        quadratic({365.0, 270.0}, {432.0, 77.5})->
        quadratic({499.0, -115.0}, {653.0, -221.0})->
        line({653.0, -319.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    return 799;
}

em DejaVuSerif::parenright(EmBox* box)
{
    Path pathSegment0 = Path::start({145.0, -319.0});
    pathSegment0.
        line({145.0, -221.0})->
        quadratic({299.0, -115.0}, {366.5, 77.5})->
        quadratic({434.0, 270.0}, {434.0, 618.0})->
        quadratic({434.0, 967.0}, {366.5, 1159.5})->
        quadratic({299.0, 1352.0}, {145.0, 1458.0})->
        line({145.0, 1556.0})->
        quadratic({389.0, 1447.0}, {513.0, 1210.5})->
        quadratic({637.0, 974.0}, {637.0, 618.0})->
        quadratic({637.0, 263.0}, {513.0, 26.5})->
        quadratic({389.0, -210.0}, {145.0, -319.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    return 799;
}

em DejaVuSerif::asterisk(EmBox* box)
{
    Path pathSegment0 = Path::start({991.0, 1237.0});
    pathSegment0.
        line({600.0, 1055.0})->
        line({991.0, 870.0})->
        line({915.0, 752.0})->
        line({567.0, 969.0})->
        line({580.0, 588.0})->
        line({444.0, 588.0})->
        line({457.0, 969.0})->
        line({109.0, 752.0})->
        line({33.0, 870.0})->
        line({424.0, 1053.0})->
        line({33.0, 1237.0})->
        line({109.0, 1356.0})->
        line({457.0, 1139.0})->
        line({444.0, 1520.0})->
        line({580.0, 1520.0})->
        line({567.0, 1139.0})->
        line({915.0, 1356.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    return 1024;
}

em DejaVuSerif::plus(EmBox* box)
{
    Path pathSegment0 = Path::start({938.0, 1284.0});
    pathSegment0.
        line({938.0, 723.0})->
        line({1499.0, 723.0})->
        line({1499.0, 561.0})->
        line({938.0, 561.0})->
        line({938.0, 0.0})->
        line({778.0, 0.0})->
        line({778.0, 561.0})->
        line({217.0, 561.0})->
        line({217.0, 723.0})->
        line({778.0, 723.0})->
        line({778.0, 1284.0})->
        line({938.0, 1284.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    return 1716;
}

em DejaVuSerif::comma(EmBox* box)
{
    Path pathSegment0 = Path::start({74.0, -199.0});
    pathSegment0.
        quadratic({168.0, -130.0}, {212.0, -36.5})->
        quadratic({256.0, 57.0}, {256.0, 190.0})->
        line({256.0, 227.0})->
        line({453.0, 227.0})->
        quadratic({445.0, 56.0}, {372.5, -66.5})->
        quadratic({300.0, -189.0}, {154.0, -279.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    return 651;
}

em DejaVuSerif::hyphen(EmBox* box)
{
    Path pathSegment0 = Path::start({90.0, 627.0});
    pathSegment0.
        line({602.0, 627.0})->
        line({602.0, 471.0})->
        line({90.0, 471.0})->
        line({90.0, 627.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    return 692;
}

em DejaVuSerif::period(EmBox* box)
{
    Path pathSegment0 = Path::start({193.0, 104.0});
    pathSegment0.
        quadratic({193.0, 160.0}, {231.0, 199.0})->
        quadratic({269.0, 238.0}, {326.0, 238.0})->
        quadratic({381.0, 238.0}, {420.0, 199.0})->
        quadratic({459.0, 160.0}, {459.0, 104.0})->
        quadratic({459.0, 49.0}, {420.0, 10.0})->
        quadratic({381.0, -29.0}, {326.0, -29.0})->
        quadratic({269.0, -29.0}, {231.0, 9.5})->
        quadratic({193.0, 48.0}, {193.0, 104.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    return 651;
}

em DejaVuSerif::slash(EmBox* box)
{
    Path pathSegment0 = Path::start({530.0, 1493.0});
    pathSegment0.
        line({690.0, 1493.0})->
        line({160.0, -190.0})->
        line({0.0, -190.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    return 690;
}

em DejaVuSerif::zero(EmBox* box)
{
    Path pathSegment0 = Path::start({651.0, 70.0});
    pathSegment0.
        quadratic({804.0, 70.0}, {880.0, 238.0})->
        quadratic({956.0, 406.0}, {956.0, 745.0})->
        quadratic({956.0, 1085.0}, {880.0, 1253.0})->
        quadratic({804.0, 1421.0}, {651.0, 1421.0})->
        quadratic({498.0, 1421.0}, {422.0, 1253.0})->
        quadratic({346.0, 1085.0}, {346.0, 745.0})->
        quadratic({346.0, 406.0}, {422.0, 238.0})->
        quadratic({498.0, 70.0}, {651.0, 70.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    Path pathSegment1 = Path::start({651.0, -29.0});
    pathSegment1.
        quadratic({408.0, -29.0}, {271.5, 175.0})->
        quadratic({135.0, 379.0}, {135.0, 745.0})->
        quadratic({135.0, 1112.0}, {271.5, 1316.0})->
        quadratic({408.0, 1520.0}, {651.0, 1520.0})->
        quadratic({895.0, 1520.0}, {1031.0, 1316.0})->
        quadratic({1167.0, 1112.0}, {1167.0, 745.0})->
        quadratic({1167.0, 379.0}, {1031.0, 175.0})->
        quadratic({895.0, -29.0}, {651.0, -29.0})->
        close(&pathSegment1);
    pathSegment1.drawTo(box);

    return 2000;
}

em DejaVuSerif::one(EmBox* box)
{
    Path pathSegment0 = Path::start({291.0, 0.0});
    pathSegment0.
        line({291.0, 106.0})->
        line({551.0, 106.0})->
        line({551.0, 1348.0})->
        line({250.0, 1153.0})->
        line({250.0, 1284.0})->
        line({614.0, 1520.0})->
        line({752.0, 1520.0})->
        line({752.0, 106.0})->
        line({1012.0, 106.0})->
        line({1012.0, 0.0})->
        line({291.0, 0.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    return 2000;
}

em DejaVuSerif::two(EmBox* box)
{
    Path pathSegment0 = Path::start({262.0, 1137.0});
    pathSegment0.
        line({150.0, 1137.0})->
        line({150.0, 1403.0})->
        quadratic({257.0, 1460.0}, {365.5, 1490.0})->
        quadratic({474.0, 1520.0}, {578.0, 1520.0})->
        quadratic({811.0, 1520.0}, {946.0, 1407.0})->
        quadratic({1081.0, 1294.0}, {1081.0, 1100.0})->
        quadratic({1081.0, 881.0}, {775.0, 576.0})->
        quadratic({751.0, 553.0}, {739.0, 541.0})->
        line({362.0, 164.0})->
        line({985.0, 164.0})->
        line({985.0, 348.0})->
        line({1102.0, 348.0})->
        line({1102.0, 0.0})->
        line({139.0, 0.0})->
        line({139.0, 109.0})->
        line({592.0, 561.0})->
        quadratic({742.0, 711.0}, {806.0, 836.5})->
        quadratic({870.0, 962.0}, {870.0, 1100.0})->
        quadratic({870.0, 1251.0}, {791.5, 1336.0})->
        quadratic({713.0, 1421.0}, {575.0, 1421.0})->
        quadratic({432.0, 1421.0}, {354.0, 1350.0})->
        quadratic({276.0, 1279.0}, {262.0, 1137.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    return 2000;
}

em DejaVuSerif::three(EmBox* box)
{
    Path pathSegment0 = Path::start({199.0, 1430.0});
    pathSegment0.
        quadratic({316.0, 1474.0}, {423.5, 1497.0})->
        quadratic({531.0, 1520.0}, {625.0, 1520.0})->
        quadratic({844.0, 1520.0}, {967.0, 1425.5})->
        quadratic({1090.0, 1331.0}, {1090.0, 1163.0})->
        quadratic({1090.0, 1028.0}, {1005.0, 937.5})->
        quadratic({920.0, 847.0}, {764.0, 815.0})->
        quadratic({948.0, 789.0}, {1049.5, 681.5})->
        quadratic({1151.0, 574.0}, {1151.0, 403.0})->
        quadratic({1151.0, 194.0}, {1010.5, 82.5})->
        quadratic({870.0, -29.0}, {606.0, -29.0})->
        quadratic({489.0, -29.0}, {377.5, -4.0})->
        quadratic({266.0, 21.0}, {156.0, 72.0})->
        line({156.0, 362.0})->
        line({268.0, 362.0})->
        quadratic({278.0, 218.0}, {365.0, 144.0})->
        quadratic({452.0, 70.0}, {610.0, 70.0})->
        quadratic({763.0, 70.0}, {851.5, 158.5})->
        quadratic({940.0, 247.0}, {940.0, 401.0})->
        quadratic({940.0, 577.0}, {849.0, 667.5})->
        quadratic({758.0, 758.0}, {582.0, 758.0})->
        line({487.0, 758.0})->
        line({487.0, 860.0})->
        line({537.0, 860.0})->
        quadratic({712.0, 860.0}, {799.5, 932.5})->
        quadratic({887.0, 1005.0}, {887.0, 1151.0})->
        quadratic({887.0, 1282.0}, {815.0, 1351.5})->
        quadratic({743.0, 1421.0}, {608.0, 1421.0})->
        quadratic({473.0, 1421.0}, {398.5, 1357.0})->
        quadratic({324.0, 1293.0}, {311.0, 1167.0})->
        line({199.0, 1167.0})->
        line({199.0, 1430.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    return 2000;
}

em DejaVuSerif::four(EmBox* box)
{
    Path pathSegment0 = Path::start({715.0, 506.0});
    pathSegment0.
        line({715.0, 1300.0})->
        line({205.0, 506.0})->
        line({715.0, 506.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    Path pathSegment1 = Path::start({1155.0, 0.0});
    pathSegment1.
        line({475.0, 0.0})->
        line({475.0, 106.0})->
        line({715.0, 106.0})->
        line({715.0, 399.0})->
        line({63.0, 399.0})->
        line({63.0, 508.0})->
        line({717.0, 1520.0})->
        line({915.0, 1520.0})->
        line({915.0, 506.0})->
        line({1200.0, 506.0})->
        line({1200.0, 399.0})->
        line({915.0, 399.0})->
        line({915.0, 106.0})->
        line({1155.0, 106.0})->
        line({1155.0, 0.0})->
        close(&pathSegment1);
    pathSegment1.drawTo(box);

    return 2000;
}

em DejaVuSerif::five(EmBox* box)
{
    Path pathSegment0 = Path::start({1030.0, 1493.0});
    pathSegment0.
        line({1030.0, 1329.0})->
        line({346.0, 1329.0})->
        line({346.0, 901.0})->
        quadratic({398.0, 937.0}, {467.5, 955.0})->
        quadratic({537.0, 973.0}, {623.0, 973.0})->
        quadratic({865.0, 973.0}, {1005.0, 839.0})->
        quadratic({1145.0, 705.0}, {1145.0, 473.0})->
        quadratic({1145.0, 236.0}, {1003.5, 103.5})->
        quadratic({862.0, -29.0}, {606.0, -29.0})->
        quadratic({503.0, -29.0}, {395.0, -4.0})->
        quadratic({287.0, 21.0}, {174.0, 72.0})->
        line({174.0, 362.0})->
        line({287.0, 362.0})->
        quadratic({296.0, 220.0}, {377.5, 145.0})->
        quadratic({459.0, 70.0}, {606.0, 70.0})->
        quadratic({764.0, 70.0}, {849.0, 174.0})->
        quadratic({934.0, 278.0}, {934.0, 473.0})->
        quadratic({934.0, 667.0}, {849.5, 770.5})->
        quadratic({765.0, 874.0}, {606.0, 874.0})->
        quadratic({516.0, 874.0}, {447.5, 842.0})->
        quadratic({379.0, 810.0}, {326.0, 743.0})->
        line({240.0, 743.0})->
        line({240.0, 1493.0})->
        line({1030.0, 1493.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    return 2000;
}

em DejaVuSerif::six(EmBox* box)
{
    Path pathSegment0 = Path::start({670.0, 70.0});
    pathSegment0.
        quadratic({811.0, 70.0}, {887.0, 173.5})->
        quadratic({963.0, 277.0}, {963.0, 471.0})->
        quadratic({963.0, 665.0}, {887.0, 768.5})->
        quadratic({811.0, 872.0}, {670.0, 872.0})->
        quadratic({527.0, 872.0}, {452.0, 772.0})->
        quadratic({377.0, 672.0}, {377.0, 483.0})->
        quadratic({377.0, 284.0}, {453.0, 177.0})->
        quadratic({529.0, 70.0}, {670.0, 70.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    Path pathSegment1 = Path::start({344.0, 822.0});
    pathSegment1.
        quadratic({412.0, 897.0}, {498.0, 934.0})->
        quadratic({584.0, 971.0}, {692.0, 971.0})->
        quadratic({915.0, 971.0}, {1044.5, 837.0})->
        quadratic({1174.0, 703.0}, {1174.0, 471.0})->
        quadratic({1174.0, 244.0}, {1034.5, 107.5})->
        quadratic({895.0, -29.0}, {662.0, -29.0})->
        quadratic({409.0, -29.0}, {273.0, 159.5})->
        quadratic({137.0, 348.0}, {137.0, 698.0})->
        quadratic({137.0, 1090.0}, {298.0, 1305.0})->
        quadratic({459.0, 1520.0}, {752.0, 1520.0})->
        quadratic({831.0, 1520.0}, {918.0, 1505.0})->
        quadratic({1005.0, 1490.0}, {1096.0, 1460.0})->
        line({1096.0, 1214.0})->
        line({983.0, 1214.0})->
        quadratic({971.0, 1315.0}, {906.0, 1368.0})->
        quadratic({841.0, 1421.0}, {731.0, 1421.0})->
        quadratic({537.0, 1421.0}, {442.0, 1274.0})->
        quadratic({347.0, 1127.0}, {344.0, 822.0})->
        close(&pathSegment1);
    pathSegment1.drawTo(box);

    return 2000;
}

em DejaVuSerif::seven(EmBox* box)
{
    Path pathSegment0 = Path::start({1155.0, 1391.0});
    pathSegment0.
        line({571.0, 0.0})->
        line({422.0, 0.0})->
        line({979.0, 1329.0})->
        line({289.0, 1329.0})->
        line({289.0, 1145.0})->
        line({172.0, 1145.0})->
        line({172.0, 1493.0})->
        line({1155.0, 1493.0})->
        line({1155.0, 1391.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    return 2000;
}

em DejaVuSerif::eight(EmBox* box)
{
    Path pathSegment0 = Path::start({954.0, 408.0});
    pathSegment0.
        quadratic({954.0, 568.0}, {874.5, 656.5})->
        quadratic({795.0, 745.0}, {651.0, 745.0})->
        quadratic({507.0, 745.0}, {427.5, 656.5})->
        quadratic({348.0, 568.0}, {348.0, 408.0})->
        quadratic({348.0, 247.0}, {427.5, 158.5})->
        quadratic({507.0, 70.0}, {651.0, 70.0})->
        quadratic({795.0, 70.0}, {874.5, 158.5})->
        quadratic({954.0, 247.0}, {954.0, 408.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    Path pathSegment1 = Path::start({913.0, 1133.0});
    pathSegment1.
        quadratic({913.0, 1269.0}, {844.0, 1345.0})->
        quadratic({775.0, 1421.0}, {651.0, 1421.0})->
        quadratic({528.0, 1421.0}, {458.5, 1345.0})->
        quadratic({389.0, 1269.0}, {389.0, 1133.0})->
        quadratic({389.0, 996.0}, {458.5, 920.0})->
        quadratic({528.0, 844.0}, {651.0, 844.0})->
        quadratic({775.0, 844.0}, {844.0, 920.0})->
        quadratic({913.0, 996.0}, {913.0, 1133.0})->
        close(&pathSegment1);
    pathSegment1.drawTo(box);

    Path pathSegment2 = Path::start({805.0, 795.0});
    pathSegment2.
        quadratic({975.0, 772.0}, {1070.0, 669.5})->
        quadratic({1165.0, 567.0}, {1165.0, 408.0})->
        quadratic({1165.0, 198.0}, {1032.0, 84.5})->
        quadratic({899.0, -29.0}, {651.0, -29.0})->
        quadratic({404.0, -29.0}, {270.5, 84.5})->
        quadratic({137.0, 198.0}, {137.0, 408.0})->
        quadratic({137.0, 567.0}, {232.0, 669.5})->
        quadratic({327.0, 772.0}, {498.0, 795.0})->
        quadratic({347.0, 822.0}, {266.5, 909.5})->
        quadratic({186.0, 997.0}, {186.0, 1133.0})->
        quadratic({186.0, 1313.0}, {310.0, 1416.5})->
        quadratic({434.0, 1520.0}, {651.0, 1520.0})->
        quadratic({868.0, 1520.0}, {992.0, 1416.5})->
        quadratic({1116.0, 1313.0}, {1116.0, 1133.0})->
        quadratic({1116.0, 997.0}, {1035.5, 909.5})->
        quadratic({955.0, 822.0}, {805.0, 795.0})->
        close(&pathSegment2);
    pathSegment2.drawTo(box);

    return 2000;
}

em DejaVuSerif::nine(EmBox* box)
{
    Path pathSegment0 = Path::start({958.0, 669.0});
    pathSegment0.
        quadratic({891.0, 594.0}, {804.0, 557.0})->
        quadratic({717.0, 520.0}, {608.0, 520.0})->
        quadratic({386.0, 520.0}, {257.5, 654.0})->
        quadratic({129.0, 788.0}, {129.0, 1020.0})->
        quadratic({129.0, 1247.0}, {268.5, 1383.5})->
        quadratic({408.0, 1520.0}, {641.0, 1520.0})->
        quadratic({894.0, 1520.0}, {1029.5, 1331.5})->
        quadratic({1165.0, 1143.0}, {1165.0, 793.0})->
        quadratic({1165.0, 401.0}, {1004.0, 186.0})->
        quadratic({843.0, -29.0}, {551.0, -29.0})->
        quadratic({472.0, -29.0}, {385.0, -14.0})->
        quadratic({298.0, 1.0}, {207.0, 31.0})->
        line({207.0, 279.0})->
        line({319.0, 279.0})->
        quadratic({332.0, 178.0}, {397.0, 124.0})->
        quadratic({462.0, 70.0}, {571.0, 70.0})->
        quadratic({765.0, 70.0}, {860.0, 216.5})->
        quadratic({955.0, 363.0}, {958.0, 669.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    Path pathSegment1 = Path::start({633.0, 1421.0});
    pathSegment1.
        quadratic({491.0, 1421.0}, {415.5, 1317.5})->
        quadratic({340.0, 1214.0}, {340.0, 1020.0})->
        quadratic({340.0, 826.0}, {415.5, 722.0})->
        quadratic({491.0, 618.0}, {633.0, 618.0})->
        quadratic({775.0, 618.0}, {850.5, 718.5})->
        quadratic({926.0, 819.0}, {926.0, 1008.0})->
        quadratic({926.0, 1207.0}, {850.0, 1314.0})->
        quadratic({774.0, 1421.0}, {633.0, 1421.0})->
        close(&pathSegment1);
    pathSegment1.drawTo(box);

    return 2000;
}

em DejaVuSerif::colon(EmBox* box)
{
    Path pathSegment0 = Path::start({213.0, 104.0});
    pathSegment0.
        quadratic({213.0, 160.0}, {251.5, 199.0})->
        quadratic({290.0, 238.0}, {346.0, 238.0})->
        quadratic({402.0, 238.0}, {440.5, 199.0})->
        quadratic({479.0, 160.0}, {479.0, 104.0})->
        quadratic({479.0, 48.0}, {441.0, 9.5})->
        quadratic({403.0, -29.0}, {346.0, -29.0})->
        quadratic({289.0, -29.0}, {251.0, 9.5})->
        quadratic({213.0, 48.0}, {213.0, 104.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    Path pathSegment1 = Path::start({213.0, 756.0});
    pathSegment1.
        quadratic({213.0, 812.0}, {251.5, 850.5})->
        quadratic({290.0, 889.0}, {346.0, 889.0})->
        quadratic({403.0, 889.0}, {441.0, 851.0})->
        quadratic({479.0, 813.0}, {479.0, 756.0})->
        quadratic({479.0, 699.0}, {441.0, 661.0})->
        quadratic({403.0, 623.0}, {346.0, 623.0})->
        quadratic({290.0, 623.0}, {251.5, 661.5})->
        quadratic({213.0, 700.0}, {213.0, 756.0})->
        close(&pathSegment1);
    pathSegment1.drawTo(box);

    return 690;
}

em DejaVuSerif::semicolon(EmBox* box)
{
    Path pathSegment0 = Path::start({74.0, -199.0});
    pathSegment0.
        quadratic({168.0, -130.0}, {212.0, -36.5})->
        quadratic({256.0, 57.0}, {256.0, 190.0})->
        line({256.0, 227.0})->
        line({453.0, 227.0})->
        quadratic({445.0, 56.0}, {372.5, -66.5})->
        quadratic({300.0, -189.0}, {154.0, -279.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    Path pathSegment1 = Path::start({217.0, 756.0});
    pathSegment1.
        quadratic({217.0, 812.0}, {255.5, 850.5})->
        quadratic({294.0, 889.0}, {350.0, 889.0})->
        quadratic({406.0, 889.0}, {444.5, 850.0})->
        quadratic({483.0, 811.0}, {483.0, 756.0})->
        quadratic({483.0, 700.0}, {444.5, 661.5})->
        quadratic({406.0, 623.0}, {350.0, 623.0})->
        quadratic({294.0, 623.0}, {255.5, 661.5})->
        quadratic({217.0, 700.0}, {217.0, 756.0})->
        close(&pathSegment1);
    pathSegment1.drawTo(box);

    return 690;
}

em DejaVuSerif::less(EmBox* box)
{
    Path pathSegment0 = Path::start({1499.0, 1020.0});
    pathSegment0.
        line({461.0, 641.0})->
        line({1499.0, 264.0})->
        line({1499.0, 94.0})->
        line({217.0, 559.0})->
        line({217.0, 725.0})->
        line({1499.0, 1190.0})->
        line({1499.0, 1020.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    return 1716;
}

em DejaVuSerif::equal(EmBox* box)
{
    Path pathSegment0 = Path::start({217.0, 926.0});
    pathSegment0.
        line({1499.0, 926.0})->
        line({1499.0, 766.0})->
        line({217.0, 766.0})->
        line({217.0, 926.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    Path pathSegment1 = Path::start({217.0, 518.0});
    pathSegment1.
        line({1499.0, 518.0})->
        line({1499.0, 358.0})->
        line({217.0, 358.0})->
        line({217.0, 518.0})->
        close(&pathSegment1);
    pathSegment1.drawTo(box);

    return 1716;
}

em DejaVuSerif::greater(EmBox* box)
{
    Path pathSegment0 = Path::start({217.0, 1020.0});
    pathSegment0.
        line({217.0, 1190.0})->
        line({1499.0, 725.0})->
        line({1499.0, 559.0})->
        line({217.0, 94.0})->
        line({217.0, 264.0})->
        line({1255.0, 641.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    return 1716;
}

em DejaVuSerif::question(EmBox* box)
{
    Path pathSegment0 = Path::start({360.0, 104.0});
    pathSegment0.
        quadratic({360.0, 160.0}, {398.5, 199.0})->
        quadratic({437.0, 238.0}, {494.0, 238.0})->
        quadratic({549.0, 238.0}, {588.0, 199.0})->
        quadratic({627.0, 160.0}, {627.0, 104.0})->
        quadratic({627.0, 49.0}, {588.0, 10.0})->
        quadratic({549.0, -29.0}, {494.0, -29.0})->
        quadratic({437.0, -29.0}, {398.5, 9.5})->
        quadratic({360.0, 48.0}, {360.0, 104.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    Path pathSegment1 = Path::start({139.0, 1427.0});
    pathSegment1.
        quadratic({245.0, 1474.0}, {340.5, 1497.0})->
        quadratic({436.0, 1520.0}, {520.0, 1520.0})->
        quadratic({742.0, 1520.0}, {870.5, 1413.0})->
        quadratic({999.0, 1306.0}, {999.0, 1124.0})->
        quadratic({999.0, 938.0}, {888.5, 820.0})->
        quadratic({778.0, 702.0}, {555.0, 651.0})->
        line({555.0, 397.0})->
        line({432.0, 397.0})->
        line({432.0, 725.0})->
        quadratic({609.0, 768.0}, {698.5, 869.0})->
        quadratic({788.0, 970.0}, {788.0, 1126.0})->
        quadratic({788.0, 1263.0}, {715.0, 1342.0})->
        quadratic({642.0, 1421.0}, {516.0, 1421.0})->
        quadratic({402.0, 1421.0}, {329.5, 1355.5})->
        quadratic({257.0, 1290.0}, {236.0, 1167.0})->
        line({139.0, 1167.0})->
        line({139.0, 1427.0})->
        close(&pathSegment1);
    pathSegment1.drawTo(box);

    return 1098;
}

em DejaVuSerif::at(EmBox* box)
{
    Path pathSegment0 = Path::start({1294.0, 248.0});
    pathSegment0.
        quadratic({1235.0, 166.0}, {1161.5, 126.0})->
        quadratic({1088.0, 86.0}, {995.0, 86.0})->
        quadratic({820.0, 86.0}, {711.0, 211.0})->
        quadratic({602.0, 336.0}, {602.0, 537.0})->
        quadratic({602.0, 738.0}, {711.0, 862.5})->
        quadratic({820.0, 987.0}, {995.0, 987.0})->
        quadratic({1088.0, 987.0}, {1161.5, 947.0})->
        quadratic({1235.0, 907.0}, {1294.0, 825.0})->
        line({1294.0, 967.0})->
        line({1450.0, 967.0})->
        line({1450.0, 195.0})->
        quadratic({1620.0, 232.0}, {1714.0, 357.0})->
        quadratic({1808.0, 482.0}, {1808.0, 670.0})->
        quadratic({1808.0, 781.0}, {1774.0, 880.0})->
        quadratic({1740.0, 979.0}, {1673.0, 1063.0})->
        quadratic({1567.0, 1196.0}, {1414.5, 1266.5})->
        quadratic({1262.0, 1337.0}, {1083.0, 1337.0})->
        quadratic({993.0, 1337.0}, {905.0, 1318.0})->
        quadratic({817.0, 1299.0}, {731.0, 1260.0})->
        quadratic({529.0, 1167.0}, {417.0, 978.5})->
        quadratic({305.0, 790.0}, {305.0, 543.0})->
        quadratic({305.0, 376.0}, {355.0, 235.5})->
        quadratic({405.0, 95.0}, {500.0, -8.0})->
        quadratic({609.0, -127.0}, {758.5, -189.5})->
        quadratic({908.0, -252.0}, {1081.0, -252.0})->
        quadratic({1210.0, -252.0}, {1322.0, -214.0})->
        quadratic({1434.0, -176.0}, {1530.0, -100.0})->
        line({1583.0, -170.0})->
        quadratic({1475.0, -263.0}, {1338.0, -309.5})->
        quadratic({1201.0, -356.0}, {1038.0, -356.0})->
        quadratic({855.0, -356.0}, {688.5, -289.5})->
        quadratic({522.0, -223.0}, {397.0, -100.0})->
        quadratic({268.0, 27.0}, {201.5, 190.5})->
        quadratic({135.0, 354.0}, {135.0, 543.0})->
        quadratic({135.0, 727.0}, {202.0, 890.0})->
        quadratic({269.0, 1053.0}, {397.0, 1180.0})->
        quadratic({524.0, 1306.0}, {696.5, 1374.0})->
        quadratic({869.0, 1442.0}, {1063.0, 1442.0})->
        quadratic({1277.0, 1442.0}, {1453.5, 1359.0})->
        quadratic({1630.0, 1276.0}, {1749.0, 1120.0})->
        quadratic({1825.0, 1022.0}, {1864.0, 907.0})->
        quadratic({1903.0, 792.0}, {1903.0, 668.0})->
        quadratic({1903.0, 400.0}, {1740.0, 244.5})->
        quadratic({1577.0, 89.0}, {1295.0, 86.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    Path pathSegment1 = Path::start({1294.0, 485.0});
    pathSegment1.
        line({1294.0, 590.0})->
        quadratic({1294.0, 715.0}, {1222.5, 792.5})->
        quadratic({1151.0, 870.0}, {1036.0, 870.0})->
        quadratic({915.0, 870.0}, {847.5, 782.5})->
        quadratic({780.0, 695.0}, {780.0, 537.0})->
        quadratic({780.0, 378.0}, {848.0, 290.5})->
        quadratic({916.0, 203.0}, {1038.0, 203.0})->
        quadratic({1152.0, 203.0}, {1223.0, 281.5})->
        quadratic({1294.0, 360.0}, {1294.0, 485.0})->
        close(&pathSegment1);
    pathSegment1.drawTo(box);

    return 2048;
}

em DejaVuSerif::A(EmBox* box)
{
    Path pathSegment0 = Path::start({410.0, 541.0});
    pathSegment0.
        line({958.0, 541.0})->
        line({684.0, 1251.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    Path pathSegment1 = Path::start({-12.0, 0.0});
    pathSegment1.
        line({-12.0, 106.0})->
        line({119.0, 106.0})->
        line({651.0, 1493.0})->
        line({819.0, 1493.0})->
        line({1352.0, 106.0})->
        line({1499.0, 106.0})->
        line({1499.0, 0.0})->
        line({956.0, 0.0})->
        line({956.0, 106.0})->
        line({1122.0, 106.0})->
        line({997.0, 434.0})->
        line({369.0, 434.0})->
        line({244.0, 106.0})->
        line({408.0, 106.0})->
        line({408.0, 0.0})->
        line({-12.0, 0.0})->
        close(&pathSegment1);
    pathSegment1.drawTo(box);

    return 1479;
}

em DejaVuSerif::B(EmBox* box)
{
    Path pathSegment0 = Path::start({506.0, 106.0});
    pathSegment0.
        line({805.0, 106.0})->
        quadratic({985.0, 106.0}, {1068.0, 184.0})->
        quadratic({1151.0, 262.0}, {1151.0, 432.0})->
        quadratic({1151.0, 601.0}, {1068.5, 678.5})->
        quadratic({986.0, 756.0}, {805.0, 756.0})->
        line({506.0, 756.0})->
        line({506.0, 106.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    Path pathSegment1 = Path::start({506.0, 862.0});
    pathSegment1.
        line({760.0, 862.0})->
        quadratic({924.0, 862.0}, {999.5, 925.0})->
        quadratic({1075.0, 988.0}, {1075.0, 1124.0})->
        quadratic({1075.0, 1261.0}, {999.5, 1323.5})->
        quadratic({924.0, 1386.0}, {760.0, 1386.0})->
        line({506.0, 1386.0})->
        line({506.0, 862.0})->
        close(&pathSegment1);
    pathSegment1.drawTo(box);

    Path pathSegment2 = Path::start({113.0, 0.0});
    pathSegment2.
        line({113.0, 106.0})->
        line({303.0, 106.0})->
        line({303.0, 1386.0})->
        line({113.0, 1386.0})->
        line({113.0, 1493.0})->
        line({850.0, 1493.0})->
        quadratic({1076.0, 1493.0}, {1190.5, 1400.5})->
        quadratic({1305.0, 1308.0}, {1305.0, 1124.0})->
        quadratic({1305.0, 991.0}, {1225.5, 912.0})->
        quadratic({1146.0, 833.0}, {993.0, 815.0})->
        quadratic({1183.0, 791.0}, {1281.5, 693.5})->
        quadratic({1380.0, 596.0}, {1380.0, 432.0})->
        quadratic({1380.0, 210.0}, {1240.0, 105.0})->
        quadratic({1100.0, 0.0}, {803.0, 0.0})->
        line({113.0, 0.0})->
        close(&pathSegment2);
    pathSegment2.drawTo(box);

    return 1505;
}

em DejaVuSerif::C(EmBox* box)
{
    Path pathSegment0 = Path::start({1444.0, 395.0});
    pathSegment0.
        quadratic({1378.0, 186.0}, {1222.5, 78.5})->
        quadratic({1067.0, -29.0}, {829.0, -29.0})->
        quadratic({683.0, -29.0}, {558.0, 21.0})->
        quadratic({433.0, 71.0}, {336.0, 168.0})->
        quadratic({224.0, 280.0}, {169.5, 422.5})->
        quadratic({115.0, 565.0}, {115.0, 745.0})->
        quadratic({115.0, 1093.0}, {316.0, 1306.5})->
        quadratic({517.0, 1520.0}, {846.0, 1520.0})->
        quadratic({968.0, 1520.0}, {1106.0, 1488.0})->
        quadratic({1244.0, 1456.0}, {1403.0, 1391.0})->
        line({1403.0, 1047.0})->
        line({1290.0, 1047.0})->
        quadratic({1253.0, 1235.0}, {1141.5, 1324.0})->
        quadratic({1030.0, 1413.0}, {829.0, 1413.0})->
        quadratic({590.0, 1413.0}, {467.0, 1243.5})->
        quadratic({344.0, 1074.0}, {344.0, 745.0})->
        quadratic({344.0, 417.0}, {467.0, 247.5})->
        quadratic({590.0, 78.0}, {829.0, 78.0})->
        quadratic({996.0, 78.0}, {1104.0, 157.5})->
        quadratic({1212.0, 237.0}, {1260.0, 395.0})->
        line({1444.0, 395.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    return 1567;
}

em DejaVuSerif::D(EmBox* box)
{
    Path pathSegment0 = Path::start({506.0, 106.0});
    pathSegment0.
        line({692.0, 106.0})->
        quadratic({983.0, 106.0}, {1138.5, 272.0})->
        quadratic({1294.0, 438.0}, {1294.0, 748.0})->
        quadratic({1294.0, 1058.0}, {1139.0, 1222.0})->
        quadratic({984.0, 1386.0}, {692.0, 1386.0})->
        line({506.0, 1386.0})->
        line({506.0, 106.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    Path pathSegment1 = Path::start({113.0, 0.0});
    pathSegment1.
        line({113.0, 106.0})->
        line({303.0, 106.0})->
        line({303.0, 1386.0})->
        line({113.0, 1386.0})->
        line({113.0, 1493.0})->
        line({707.0, 1493.0})->
        quadratic({1093.0, 1493.0}, {1308.5, 1296.0})->
        quadratic({1524.0, 1099.0}, {1524.0, 748.0})->
        quadratic({1524.0, 396.0}, {1308.0, 198.0})->
        quadratic({1092.0, 0.0}, {707.0, 0.0})->
        line({113.0, 0.0})->
        close(&pathSegment1);
    pathSegment1.drawTo(box);

    return 1642;
}

em DejaVuSerif::E(EmBox* box)
{
    Path pathSegment0 = Path::start({113.0, 0.0});
    pathSegment0.
        line({113.0, 106.0})->
        line({303.0, 106.0})->
        line({303.0, 1386.0})->
        line({113.0, 1386.0})->
        line({113.0, 1493.0})->
        line({1315.0, 1493.0})->
        line({1315.0, 1161.0})->
        line({1192.0, 1161.0})->
        line({1192.0, 1370.0})->
        line({506.0, 1370.0})->
        line({506.0, 870.0})->
        line({995.0, 870.0})->
        line({995.0, 1057.0})->
        line({1118.0, 1057.0})->
        line({1118.0, 561.0})->
        line({995.0, 561.0})->
        line({995.0, 748.0})->
        line({506.0, 748.0})->
        line({506.0, 123.0})->
        line({1208.0, 123.0})->
        line({1208.0, 332.0})->
        line({1331.0, 332.0})->
        line({1331.0, 0.0})->
        line({113.0, 0.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    return 1495;
}

em DejaVuSerif::F(EmBox* box)
{
    Path pathSegment0 = Path::start({113.0, 0.0});
    pathSegment0.
        line({113.0, 106.0})->
        line({303.0, 106.0})->
        line({303.0, 1386.0})->
        line({113.0, 1386.0})->
        line({113.0, 1493.0})->
        line({1335.0, 1493.0})->
        line({1335.0, 1161.0})->
        line({1212.0, 1161.0})->
        line({1212.0, 1370.0})->
        line({506.0, 1370.0})->
        line({506.0, 870.0})->
        line({1016.0, 870.0})->
        line({1016.0, 1057.0})->
        line({1139.0, 1057.0})->
        line({1139.0, 561.0})->
        line({1016.0, 561.0})->
        line({1016.0, 748.0})->
        line({506.0, 748.0})->
        line({506.0, 106.0})->
        line({745.0, 106.0})->
        line({745.0, 0.0})->
        line({113.0, 0.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    return 1421;
}

em DejaVuSerif::G(EmBox* box)
{
    Path pathSegment0 = Path::start({1311.0, 1047.0});
    pathSegment0.
        quadratic({1276.0, 1234.0}, {1165.0, 1323.5})->
        quadratic({1054.0, 1413.0}, {856.0, 1413.0})->
        quadratic({598.0, 1413.0}, {471.0, 1247.0})->
        quadratic({344.0, 1081.0}, {344.0, 745.0})->
        quadratic({344.0, 416.0}, {475.0, 247.0})->
        quadratic({606.0, 78.0}, {860.0, 78.0})->
        quadratic({973.0, 78.0}, {1076.0, 106.0})->
        quadratic({1179.0, 134.0}, {1272.0, 190.0})->
        line({1272.0, 575.0})->
        line({991.0, 575.0})->
        line({991.0, 682.0})->
        line({1475.0, 682.0})->
        line({1475.0, 125.0})->
        quadratic({1342.0, 48.0}, {1188.5, 9.5})->
        quadratic({1035.0, -29.0}, {860.0, -29.0})->
        quadratic({522.0, -29.0}, {318.5, 182.5})->
        quadratic({115.0, 394.0}, {115.0, 745.0})->
        quadratic({115.0, 1099.0}, {319.0, 1309.5})->
        quadratic({523.0, 1520.0}, {868.0, 1520.0})->
        quadratic({996.0, 1520.0}, {1132.5, 1490.5})->
        quadratic({1269.0, 1461.0}, {1423.0, 1401.0})->
        line({1423.0, 1047.0})->
        line({1311.0, 1047.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    return 1636;
}

em DejaVuSerif::H(EmBox* box)
{
    Path pathSegment0 = Path::start({113.0, 0.0});
    pathSegment0.
        line({113.0, 106.0})->
        line({303.0, 106.0})->
        line({303.0, 1386.0})->
        line({113.0, 1386.0})->
        line({113.0, 1493.0})->
        line({696.0, 1493.0})->
        line({696.0, 1386.0})->
        line({506.0, 1386.0})->
        line({506.0, 870.0})->
        line({1280.0, 870.0})->
        line({1280.0, 1386.0})->
        line({1090.0, 1386.0})->
        line({1090.0, 1493.0})->
        line({1673.0, 1493.0})->
        line({1673.0, 1386.0})->
        line({1483.0, 1386.0})->
        line({1483.0, 106.0})->
        line({1673.0, 106.0})->
        line({1673.0, 0.0})->
        line({1090.0, 0.0})->
        line({1090.0, 106.0})->
        line({1280.0, 106.0})->
        line({1280.0, 748.0})->
        line({506.0, 748.0})->
        line({506.0, 106.0})->
        line({696.0, 106.0})->
        line({696.0, 0.0})->
        line({113.0, 0.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    return 1786;
}

em DejaVuSerif::I(EmBox* box)
{
    Path pathSegment0 = Path::start({506.0, 106.0});
    pathSegment0.
        line({696.0, 106.0})->
        line({696.0, 0.0})->
        line({113.0, 0.0})->
        line({113.0, 106.0})->
        line({303.0, 106.0})->
        line({303.0, 1386.0})->
        line({113.0, 1386.0})->
        line({113.0, 1493.0})->
        line({696.0, 1493.0})->
        line({696.0, 1386.0})->
        line({506.0, 1386.0})->
        line({506.0, 106.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    return 809;
}

em DejaVuSerif::J(EmBox* box)
{
    Path pathSegment0 = Path::start({-172.0, -358.0});
    pathSegment0.
        line({-172.0, -123.0})->
        line({-58.0, -123.0})->
        quadratic({-55.0, -222.0}, {-11.0, -270.5})->
        quadratic({33.0, -319.0}, {121.0, -319.0})->
        quadratic({240.0, -319.0}, {287.0, -244.0})->
        quadratic({334.0, -169.0}, {334.0, 49.0})->
        line({334.0, 1386.0})->
        line({102.0, 1386.0})->
        line({102.0, 1493.0})->
        line({727.0, 1493.0})->
        line({727.0, 1386.0})->
        line({537.0, 1386.0})->
        line({537.0, 41.0})->
        quadratic({537.0, -206.0}, {438.0, -316.0})->
        quadratic({339.0, -426.0}, {119.0, -426.0})->
        quadratic({48.0, -426.0}, {-25.5, -409.0})->
        quadratic({-99.0, -392.0}, {-172.0, -358.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    return 821;
}

em DejaVuSerif::K(EmBox* box)
{
    Path pathSegment0 = Path::start({113.0, 0.0});
    pathSegment0.
        line({113.0, 106.0})->
        line({303.0, 106.0})->
        line({303.0, 1386.0})->
        line({113.0, 1386.0})->
        line({113.0, 1493.0})->
        line({696.0, 1493.0})->
        line({696.0, 1386.0})->
        line({506.0, 1386.0})->
        line({506.0, 821.0})->
        line({1149.0, 1386.0})->
        line({987.0, 1386.0})->
        line({987.0, 1493.0})->
        line({1483.0, 1493.0})->
        line({1483.0, 1386.0})->
        line({1315.0, 1386.0})->
        line({674.0, 823.0})->
        line({1391.0, 106.0})->
        line({1561.0, 106.0})->
        line({1561.0, 0.0})->
        line({1214.0, 0.0})->
        line({506.0, 709.0})->
        line({506.0, 106.0})->
        line({696.0, 106.0})->
        line({696.0, 0.0})->
        line({113.0, 0.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    return 1530;
}

em DejaVuSerif::L(EmBox* box)
{
    Path pathSegment0 = Path::start({113.0, 0.0});
    pathSegment0.
        line({113.0, 106.0})->
        line({303.0, 106.0})->
        line({303.0, 1386.0})->
        line({113.0, 1386.0})->
        line({113.0, 1493.0})->
        line({696.0, 1493.0})->
        line({696.0, 1386.0})->
        line({506.0, 1386.0})->
        line({506.0, 123.0})->
        line({1188.0, 123.0})->
        line({1188.0, 373.0})->
        line({1311.0, 373.0})->
        line({1311.0, 0.0})->
        line({113.0, 0.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    return 1360;
}

em DejaVuSerif::M(EmBox* box)
{
    Path pathSegment0 = Path::start({113.0, 0.0});
    pathSegment0.
        line({113.0, 106.0})->
        line({303.0, 106.0})->
        line({303.0, 1386.0})->
        line({102.0, 1386.0})->
        line({102.0, 1493.0})->
        line({537.0, 1493.0})->
        line({1061.0, 430.0})->
        line({1585.0, 1493.0})->
        line({1993.0, 1493.0})->
        line({1993.0, 1386.0})->
        line({1794.0, 1386.0})->
        line({1794.0, 106.0})->
        line({1985.0, 106.0})->
        line({1985.0, 0.0})->
        line({1401.0, 0.0})->
        line({1401.0, 106.0})->
        line({1591.0, 106.0})->
        line({1591.0, 1260.0})->
        line({1079.0, 219.0})->
        line({938.0, 219.0})->
        line({426.0, 1260.0})->
        line({426.0, 106.0})->
        line({616.0, 106.0})->
        line({616.0, 0.0})->
        line({113.0, 0.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    return 2097;
}

em DejaVuSerif::N(EmBox* box)
{
    Path pathSegment0 = Path::start({100.0, 0.0});
    pathSegment0.
        line({100.0, 106.0})->
        line({301.0, 106.0})->
        line({301.0, 1386.0})->
        line({100.0, 1386.0})->
        line({100.0, 1493.0})->
        line({483.0, 1493.0})->
        line({1378.0, 315.0})->
        line({1378.0, 1386.0})->
        line({1178.0, 1386.0})->
        line({1178.0, 1493.0})->
        line({1702.0, 1493.0})->
        line({1702.0, 1386.0})->
        line({1501.0, 1386.0})->
        line({1501.0, -29.0})->
        line({1380.0, -29.0})->
        line({424.0, 1229.0})->
        line({424.0, 106.0})->
        line({625.0, 106.0})->
        line({625.0, 0.0})->
        line({100.0, 0.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    return 1792;
}

em DejaVuSerif::O(EmBox* box)
{
    Path pathSegment0 = Path::start({840.0, 78.0});
    pathSegment0.
        quadratic({1085.0, 78.0}, {1210.0, 246.5})->
        quadratic({1335.0, 415.0}, {1335.0, 745.0})->
        quadratic({1335.0, 1076.0}, {1210.0, 1244.5})->
        quadratic({1085.0, 1413.0}, {840.0, 1413.0})->
        quadratic({594.0, 1413.0}, {469.0, 1244.5})->
        quadratic({344.0, 1076.0}, {344.0, 745.0})->
        quadratic({344.0, 415.0}, {469.0, 246.5})->
        quadratic({594.0, 78.0}, {840.0, 78.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    Path pathSegment1 = Path::start({840.0, -29.0});
    pathSegment1.
        quadratic({688.0, -29.0}, {560.5, 21.0})->
        quadratic({433.0, 71.0}, {336.0, 168.0})->
        quadratic({224.0, 280.0}, {169.5, 422.0})->
        quadratic({115.0, 564.0}, {115.0, 745.0})->
        quadratic({115.0, 926.0}, {169.5, 1068.5})->
        quadratic({224.0, 1211.0}, {336.0, 1323.0})->
        quadratic({434.0, 1421.0}, {560.0, 1470.5})->
        quadratic({686.0, 1520.0}, {840.0, 1520.0})->
        quadratic({1165.0, 1520.0}, {1365.0, 1307.0})->
        quadratic({1565.0, 1094.0}, {1565.0, 745.0})->
        quadratic({1565.0, 566.0}, {1510.0, 422.5})->
        quadratic({1455.0, 279.0}, {1343.0, 168.0})->
        quadratic({1245.0, 70.0}, {1119.0, 20.5})->
        quadratic({993.0, -29.0}, {840.0, -29.0})->
        close(&pathSegment1);
    pathSegment1.drawTo(box);

    return 1679;
}

em DejaVuSerif::P(EmBox* box)
{
    Path pathSegment0 = Path::start({506.0, 760.0});
    pathSegment0.
        line({770.0, 760.0})->
        quadratic({919.0, 760.0}, {997.0, 840.5})->
        quadratic({1075.0, 921.0}, {1075.0, 1073.0})->
        quadratic({1075.0, 1226.0}, {997.0, 1306.0})->
        quadratic({919.0, 1386.0}, {770.0, 1386.0})->
        line({506.0, 1386.0})->
        line({506.0, 760.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    Path pathSegment1 = Path::start({113.0, 0.0});
    pathSegment1.
        line({113.0, 106.0})->
        line({303.0, 106.0})->
        line({303.0, 1386.0})->
        line({113.0, 1386.0})->
        line({113.0, 1493.0})->
        line({819.0, 1493.0})->
        quadratic({1043.0, 1493.0}, {1174.0, 1379.5})->
        quadratic({1305.0, 1266.0}, {1305.0, 1073.0})->
        quadratic({1305.0, 881.0}, {1174.0, 767.0})->
        quadratic({1043.0, 653.0}, {819.0, 653.0})->
        line({506.0, 653.0})->
        line({506.0, 106.0})->
        line({737.0, 106.0})->
        line({737.0, 0.0})->
        line({113.0, 0.0})->
        close(&pathSegment1);
    pathSegment1.drawTo(box);

    return 1378;
}

em DejaVuSerif::Q(EmBox* box)
{
    Path pathSegment0 = Path::start({864.0, -29.0});
    pathSegment0.
        quadratic({521.0, -29.0}, {318.0, 181.5})->
        quadratic({115.0, 392.0}, {115.0, 745.0})->
        quadratic({115.0, 926.0}, {169.5, 1068.5})->
        quadratic({224.0, 1211.0}, {336.0, 1323.0})->
        quadratic({434.0, 1421.0}, {560.0, 1470.5})->
        quadratic({686.0, 1520.0}, {840.0, 1520.0})->
        quadratic({1165.0, 1520.0}, {1365.0, 1307.0})->
        quadratic({1565.0, 1094.0}, {1565.0, 745.0})->
        quadratic({1565.0, 449.0}, {1415.0, 247.5})->
        quadratic({1265.0, 46.0}, {1001.0, -12.0})->
        quadratic({1055.0, -79.0}, {1132.5, -111.0})->
        quadratic({1210.0, -143.0}, {1319.0, -143.0})->
        line({1350.0, -143.0})->
        line({1350.0, -328.0})->
        quadratic({1181.0, -320.0}, {1060.5, -245.5})->
        quadratic({940.0, -171.0}, {864.0, -29.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    Path pathSegment1 = Path::start({840.0, 78.0});
    pathSegment1.
        quadratic({1085.0, 78.0}, {1210.0, 246.5})->
        quadratic({1335.0, 415.0}, {1335.0, 745.0})->
        quadratic({1335.0, 1076.0}, {1210.0, 1244.5})->
        quadratic({1085.0, 1413.0}, {840.0, 1413.0})->
        quadratic({594.0, 1413.0}, {469.0, 1244.5})->
        quadratic({344.0, 1076.0}, {344.0, 745.0})->
        quadratic({344.0, 415.0}, {469.0, 246.5})->
        quadratic({594.0, 78.0}, {840.0, 78.0})->
        close(&pathSegment1);
    pathSegment1.drawTo(box);

    return 1679;
}

em DejaVuSerif::R(EmBox* box)
{
    Path pathSegment0 = Path::start({981.0, 741.0});
    pathSegment0.
        quadratic({1051.0, 722.0}, {1101.5, 676.5})->
        quadratic({1152.0, 631.0}, {1192.0, 549.0})->
        line({1409.0, 106.0})->
        line({1591.0, 106.0})->
        line({1591.0, 0.0})->
        line({1239.0, 0.0})->
        line({1006.0, 475.0})->
        quadratic({939.0, 613.0}, {883.0, 653.5})->
        quadratic({827.0, 694.0}, {729.0, 694.0})->
        line({506.0, 694.0})->
        line({506.0, 106.0})->
        line({717.0, 106.0})->
        line({717.0, 0.0})->
        line({113.0, 0.0})->
        line({113.0, 106.0})->
        line({303.0, 106.0})->
        line({303.0, 1386.0})->
        line({113.0, 1386.0})->
        line({113.0, 1493.0})->
        line({870.0, 1493.0})->
        quadratic({1088.0, 1493.0}, {1206.5, 1389.0})->
        quadratic({1325.0, 1285.0}, {1325.0, 1094.0})->
        quadratic({1325.0, 940.0}, {1238.5, 851.5})->
        quadratic({1152.0, 763.0}, {981.0, 741.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    Path pathSegment1 = Path::start({506.0, 801.0});
    pathSegment1.
        line({801.0, 801.0})->
        quadratic({952.0, 801.0}, {1024.0, 872.5})->
        quadratic({1096.0, 944.0}, {1096.0, 1094.0})->
        quadratic({1096.0, 1244.0}, {1024.0, 1315.0})->
        quadratic({952.0, 1386.0}, {801.0, 1386.0})->
        line({506.0, 1386.0})->
        line({506.0, 801.0})->
        close(&pathSegment1);
    pathSegment1.drawTo(box);

    return 1542;
}

em DejaVuSerif::S(EmBox* box)
{
    Path pathSegment0 = Path::start({190.0, 72.0});
    pathSegment0.
        line({190.0, 412.0})->
        line({305.0, 411.0})->
        quadratic({310.0, 241.0}, {403.5, 159.5})->
        quadratic({497.0, 78.0}, {688.0, 78.0})->
        quadratic({866.0, 78.0}, {959.5, 148.5})->
        quadratic({1053.0, 219.0}, {1053.0, 354.0})->
        quadratic({1053.0, 462.0}, {996.5, 520.0})->
        quadratic({940.0, 578.0}, {758.0, 633.0})->
        line({561.0, 692.0})->
        quadratic({347.0, 757.0}, {259.5, 854.0})->
        quadratic({172.0, 951.0}, {172.0, 1120.0})->
        quadratic({172.0, 1310.0}, {307.0, 1415.0})->
        quadratic({442.0, 1520.0}, {686.0, 1520.0})->
        quadratic({790.0, 1520.0}, {914.0, 1497.5})->
        quadratic({1038.0, 1475.0}, {1178.0, 1432.0})->
        line({1178.0, 1114.0})->
        line({1065.0, 1114.0})->
        quadratic({1048.0, 1272.0}, {959.5, 1342.5})->
        quadratic({871.0, 1413.0}, {690.0, 1413.0})->
        quadratic({532.0, 1413.0}, {449.5, 1348.5})->
        quadratic({367.0, 1284.0}, {367.0, 1161.0})->
        quadratic({367.0, 1054.0}, {429.0, 993.0})->
        quadratic({491.0, 932.0}, {692.0, 872.0})->
        line({877.0, 817.0})->
        quadratic({1080.0, 756.0}, {1166.5, 661.5})->
        quadratic({1253.0, 567.0}, {1253.0, 408.0})->
        quadratic({1253.0, 191.0}, {1114.0, 81.0})->
        quadratic({975.0, -29.0}, {700.0, -29.0})->
        quadratic({577.0, -29.0}, {449.5, -4.0})->
        quadratic({322.0, 21.0}, {190.0, 72.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    return 1403;
}

em DejaVuSerif::T(EmBox* box)
{
    Path pathSegment0 = Path::start({391.0, 0.0});
    pathSegment0.
        line({391.0, 106.0})->
        line({582.0, 106.0})->
        line({582.0, 1374.0})->
        line({143.0, 1374.0})->
        line({143.0, 1141.0})->
        line({20.0, 1141.0})->
        line({20.0, 1493.0})->
        line({1346.0, 1493.0})->
        line({1346.0, 1141.0})->
        line({1223.0, 1141.0})->
        line({1223.0, 1374.0})->
        line({784.0, 1374.0})->
        line({784.0, 106.0})->
        line({975.0, 106.0})->
        line({975.0, 0.0})->
        line({391.0, 0.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    return 1366;
}

em DejaVuSerif::U(EmBox* box)
{
    Path pathSegment0 = Path::start({287.0, 1386.0});
    pathSegment0.
        line({96.0, 1386.0})->
        line({96.0, 1493.0})->
        line({680.0, 1493.0})->
        line({680.0, 1386.0})->
        line({489.0, 1386.0})->
        line({489.0, 614.0})->
        quadratic({489.0, 328.0}, {582.5, 215.0})->
        quadratic({676.0, 102.0}, {905.0, 102.0})->
        quadratic({1134.0, 102.0}, {1227.5, 215.0})->
        quadratic({1321.0, 328.0}, {1321.0, 614.0})->
        line({1321.0, 1386.0})->
        line({1130.0, 1386.0})->
        line({1130.0, 1493.0})->
        line({1634.0, 1493.0})->
        line({1634.0, 1386.0})->
        line({1444.0, 1386.0})->
        line({1444.0, 594.0})->
        quadratic({1444.0, 253.0}, {1313.0, 112.0})->
        quadratic({1182.0, -29.0}, {868.0, -29.0})->
        quadratic({554.0, -29.0}, {420.5, 113.0})->
        quadratic({287.0, 255.0}, {287.0, 594.0})->
        line({287.0, 1386.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    return 1726;
}

em DejaVuSerif::V(EmBox* box)
{
    Path pathSegment0 = Path::start({358.0, 1386.0});
    pathSegment0.
        line({799.0, 240.0})->
        line({1239.0, 1386.0})->
        line({1071.0, 1386.0})->
        line({1071.0, 1493.0})->
        line({1509.0, 1493.0})->
        line({1509.0, 1386.0})->
        line({1364.0, 1386.0})->
        line({831.0, 0.0})->
        line({659.0, 0.0})->
        line({129.0, 1386.0})->
        line({-20.0, 1386.0})->
        line({-20.0, 1493.0})->
        line({524.0, 1493.0})->
        line({524.0, 1386.0})->
        line({358.0, 1386.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    return 1479;
}

em DejaVuSerif::W(EmBox* box)
{
    Path pathSegment0 = Path::start({1561.0, 0.0});
    pathSegment0.
        line({1397.0, 0.0})->
        line({1055.0, 1214.0})->
        line({713.0, 0.0})->
        line({549.0, 0.0})->
        line({158.0, 1386.0})->
        line({10.0, 1386.0})->
        line({10.0, 1493.0})->
        line({555.0, 1493.0})->
        line({555.0, 1386.0})->
        line({369.0, 1386.0})->
        line({680.0, 283.0})->
        line({1020.0, 1493.0})->
        line({1182.0, 1493.0})->
        line({1528.0, 270.0})->
        line({1841.0, 1386.0})->
        line({1669.0, 1386.0})->
        line({1669.0, 1493.0})->
        line({2099.0, 1493.0})->
        line({2099.0, 1386.0})->
        line({1952.0, 1386.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    return 2105;
}

em DejaVuSerif::X(EmBox* box)
{
    Path pathSegment0 = Path::start({678.0, 639.0});
    pathSegment0.
        line({313.0, 106.0})->
        line({506.0, 106.0})->
        line({506.0, 0.0})->
        line({12.0, 0.0})->
        line({12.0, 106.0})->
        line({184.0, 106.0})->
        line({614.0, 733.0})->
        line({178.0, 1386.0})->
        line({18.0, 1386.0})->
        line({18.0, 1493.0})->
        line({610.0, 1493.0})->
        line({610.0, 1386.0})->
        line({434.0, 1386.0})->
        line({754.0, 905.0})->
        line({1083.0, 1386.0})->
        line({891.0, 1386.0})->
        line({891.0, 1493.0})->
        line({1380.0, 1493.0})->
        line({1380.0, 1386.0})->
        line({1212.0, 1386.0})->
        line({817.0, 811.0})->
        line({1288.0, 106.0})->
        line({1448.0, 106.0})->
        line({1448.0, 0.0})->
        line({856.0, 0.0})->
        line({856.0, 106.0})->
        line({1034.0, 106.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    return 1458;
}

em DejaVuSerif::Y(EmBox* box)
{
    Path pathSegment0 = Path::start({387.0, 0.0});
    pathSegment0.
        line({387.0, 106.0})->
        line({578.0, 106.0})->
        line({578.0, 643.0})->
        line({117.0, 1386.0})->
        line({-23.0, 1386.0})->
        line({-23.0, 1493.0})->
        line({532.0, 1493.0})->
        line({532.0, 1386.0})->
        line({358.0, 1386.0})->
        line({731.0, 782.0})->
        line({1104.0, 1386.0})->
        line({936.0, 1386.0})->
        line({936.0, 1493.0})->
        line({1370.0, 1493.0})->
        line({1370.0, 1386.0})->
        line({1229.0, 1386.0})->
        line({780.0, 662.0})->
        line({780.0, 106.0})->
        line({971.0, 106.0})->
        line({971.0, 0.0})->
        line({387.0, 0.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    return 1352;
}

em DejaVuSerif::Z(EmBox* box)
{
    Path pathSegment0 = Path::start({92.0, 0.0});
    pathSegment0.
        line({92.0, 72.0})->
        line({1022.0, 1370.0})->
        line({250.0, 1370.0})->
        line({250.0, 1147.0})->
        line({127.0, 1147.0})->
        line({127.0, 1493.0})->
        line({1307.0, 1493.0})->
        line({1307.0, 1421.0})->
        line({377.0, 123.0})->
        line({1221.0, 123.0})->
        line({1221.0, 332.0})->
        line({1343.0, 332.0})->
        line({1343.0, 0.0})->
        line({92.0, 0.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    return 1423;
}

em DejaVuSerif::bracketleft(EmBox* box)
{
    Path pathSegment0 = Path::start({176.0, 1556.0});
    pathSegment0.
        line({641.0, 1556.0})->
        line({641.0, 1450.0})->
        line({367.0, 1450.0})->
        line({367.0, -164.0})->
        line({641.0, -164.0})->
        line({641.0, -270.0})->
        line({176.0, -270.0})->
        line({176.0, 1556.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    return 799;
}

em DejaVuSerif::backslash(EmBox* box)
{
    Path pathSegment0 = Path::start({160.0, 1493.0});
    pathSegment0.
        line({690.0, -190.0})->
        line({530.0, -190.0})->
        line({0.0, 1493.0})->
        line({160.0, 1493.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    return 690;
}

em DejaVuSerif::bracketright(EmBox* box)
{
    Path pathSegment0 = Path::start({623.0, 1556.0});
    pathSegment0.
        line({623.0, -270.0})->
        line({158.0, -270.0})->
        line({158.0, -164.0})->
        line({432.0, -164.0})->
        line({432.0, 1450.0})->
        line({158.0, 1450.0})->
        line({158.0, 1556.0})->
        line({623.0, 1556.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    return 799;
}

em DejaVuSerif::asciicircum(EmBox* box)
{
    Path pathSegment0 = Path::start({956.0, 1493.0});
    pathSegment0.
        line({1499.0, 936.0})->
        line({1346.0, 936.0})->
        line({858.0, 1317.0})->
        line({371.0, 936.0})->
        line({217.0, 936.0})->
        line({760.0, 1493.0})->
        line({956.0, 1493.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    return 1716;
}

em DejaVuSerif::underscore(EmBox* box)
{
    Path pathSegment0 = Path::start({1024.0, -403.0});
    pathSegment0.
        line({1024.0, -483.0})->
        line({0.0, -483.0})->
        line({0.0, -403.0})->
        line({1024.0, -403.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    return 1024;
}

em DejaVuSerif::grave(EmBox* box)
{
    Path pathSegment0 = Path::start({367.0, 1636.0});
    pathSegment0.
        line({627.0, 1260.0})->
        line({510.0, 1260.0})->
        line({170.0, 1636.0})->
        line({367.0, 1636.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    return 1024;
}

em DejaVuSerif::a(EmBox* box)
{
    Path pathSegment0 = Path::start({815.0, 334.0});
    pathSegment0.
        line({815.0, 559.0})->
        line({578.0, 559.0})->
        quadratic({441.0, 559.0}, {374.0, 500.0})->
        quadratic({307.0, 441.0}, {307.0, 319.0})->
        quadratic({307.0, 208.0}, {375.0, 143.0})->
        quadratic({443.0, 78.0}, {559.0, 78.0})->
        quadratic({674.0, 78.0}, {744.5, 149.0})->
        quadratic({815.0, 220.0}, {815.0, 334.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    Path pathSegment1 = Path::start({999.0, 664.0});
    pathSegment1.
        line({999.0, 106.0})->
        line({1163.0, 106.0})->
        line({1163.0, 0.0})->
        line({815.0, 0.0})->
        line({815.0, 115.0})->
        quadratic({754.0, 41.0}, {674.0, 6.0})->
        quadratic({594.0, -29.0}, {487.0, -29.0})->
        quadratic({310.0, -29.0}, {206.0, 65.0})->
        quadratic({102.0, 159.0}, {102.0, 319.0})->
        quadratic({102.0, 484.0}, {221.0, 575.0})->
        quadratic({340.0, 666.0}, {557.0, 666.0})->
        line({815.0, 666.0})->
        line({815.0, 739.0})->
        quadratic({815.0, 860.0}, {741.5, 926.5})->
        quadratic({668.0, 993.0}, {535.0, 993.0})->
        quadratic({425.0, 993.0}, {360.0, 943.0})->
        quadratic({295.0, 893.0}, {279.0, 795.0})->
        line({184.0, 795.0})->
        line({184.0, 1010.0})->
        quadratic({280.0, 1051.0}, {370.5, 1071.5})->
        quadratic({461.0, 1092.0}, {547.0, 1092.0})->
        quadratic({768.0, 1092.0}, {883.5, 982.5})->
        quadratic({999.0, 873.0}, {999.0, 664.0})->
        close(&pathSegment1);
    pathSegment1.drawTo(box);

    return 1221;
}

em DejaVuSerif::b(EmBox* box)
{
    Path pathSegment0 = Path::start({236.0, 106.0});
    pathSegment0.
        line({236.0, 1450.0})->
        line({59.0, 1450.0})->
        line({59.0, 1556.0})->
        line({420.0, 1556.0})->
        line({420.0, 897.0})->
        quadratic({474.0, 997.0}, {557.5, 1044.5})->
        quadratic({641.0, 1092.0}, {764.0, 1092.0})->
        quadratic({960.0, 1092.0}, {1084.0, 937.0})->
        quadratic({1208.0, 782.0}, {1208.0, 532.0})->
        quadratic({1208.0, 282.0}, {1084.0, 126.5})->
        quadratic({960.0, -29.0}, {764.0, -29.0})->
        quadratic({641.0, -29.0}, {557.5, 18.5})->
        quadratic({474.0, 66.0}, {420.0, 166.0})->
        line({420.0, 0.0})->
        line({59.0, 0.0})->
        line({59.0, 106.0})->
        line({236.0, 106.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    Path pathSegment1 = Path::start({420.0, 479.0});
    pathSegment1.
        quadratic({420.0, 287.0}, {493.5, 186.5})->
        quadratic({567.0, 86.0}, {707.0, 86.0})->
        quadratic({848.0, 86.0}, {920.5, 199.0})->
        quadratic({993.0, 312.0}, {993.0, 532.0})->
        quadratic({993.0, 753.0}, {920.5, 865.0})->
        quadratic({848.0, 977.0}, {707.0, 977.0})->
        quadratic({567.0, 977.0}, {493.5, 876.0})->
        quadratic({420.0, 775.0}, {420.0, 584.0})->
        line({420.0, 479.0})->
        close(&pathSegment1);
    pathSegment1.drawTo(box);

    return 1311;
}

em DejaVuSerif::c(EmBox* box)
{
    Path pathSegment0 = Path::start({1053.0, 319.0});
    pathSegment0.
        quadratic({1014.0, 149.0}, {903.0, 60.0})->
        quadratic({792.0, -29.0}, {616.0, -29.0})->
        quadratic({384.0, -29.0}, {243.0, 124.5})->
        quadratic({102.0, 278.0}, {102.0, 532.0})->
        quadratic({102.0, 787.0}, {243.0, 939.5})->
        quadratic({384.0, 1092.0}, {616.0, 1092.0})->
        quadratic({717.0, 1092.0}, {817.0, 1068.5})->
        quadratic({917.0, 1045.0}, {1018.0, 997.0})->
        line({1018.0, 725.0})->
        line({911.0, 725.0})->
        quadratic({890.0, 865.0}, {819.5, 929.0})->
        quadratic({749.0, 993.0}, {618.0, 993.0})->
        quadratic({469.0, 993.0}, {393.0, 877.5})->
        quadratic({317.0, 762.0}, {317.0, 532.0})->
        quadratic({317.0, 302.0}, {392.5, 186.0})->
        quadratic({468.0, 70.0}, {618.0, 70.0})->
        quadratic({737.0, 70.0}, {808.0, 132.0})->
        quadratic({879.0, 194.0}, {905.0, 319.0})->
        line({1053.0, 319.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    return 1147;
}

em DejaVuSerif::d(EmBox* box)
{
    Path pathSegment0 = Path::start({1075.0, 106.0});
    pathSegment0.
        line({1251.0, 106.0})->
        line({1251.0, 0.0})->
        line({891.0, 0.0})->
        line({891.0, 166.0})->
        quadratic({837.0, 66.0}, {753.5, 18.5})->
        quadratic({670.0, -29.0}, {547.0, -29.0})->
        quadratic({351.0, -29.0}, {226.5, 126.5})->
        quadratic({102.0, 282.0}, {102.0, 532.0})->
        quadratic({102.0, 782.0}, {226.0, 937.0})->
        quadratic({350.0, 1092.0}, {547.0, 1092.0})->
        quadratic({670.0, 1092.0}, {753.5, 1044.5})->
        quadratic({837.0, 997.0}, {891.0, 897.0})->
        line({891.0, 1450.0})->
        line({717.0, 1450.0})->
        line({717.0, 1556.0})->
        line({1075.0, 1556.0})->
        line({1075.0, 106.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    Path pathSegment1 = Path::start({891.0, 479.0});
    pathSegment1.
        line({891.0, 584.0})->
        quadratic({891.0, 775.0}, {817.5, 876.0})->
        quadratic({744.0, 977.0}, {604.0, 977.0})->
        quadratic({462.0, 977.0}, {389.5, 865.0})->
        quadratic({317.0, 753.0}, {317.0, 532.0})->
        quadratic({317.0, 312.0}, {389.5, 199.0})->
        quadratic({462.0, 86.0}, {604.0, 86.0})->
        quadratic({744.0, 86.0}, {817.5, 186.5})->
        quadratic({891.0, 287.0}, {891.0, 479.0})->
        close(&pathSegment1);
    pathSegment1.drawTo(box);

    return 1311;
}

em DejaVuSerif::e(EmBox* box)
{
    Path pathSegment0 = Path::start({1110.0, 512.0});
    pathSegment0.
        line({317.0, 512.0})->
        line({317.0, 504.0})->
        quadratic({317.0, 289.0}, {398.0, 179.5})->
        quadratic({479.0, 70.0}, {637.0, 70.0})->
        quadratic({758.0, 70.0}, {835.5, 133.5})->
        quadratic({913.0, 197.0}, {944.0, 322.0})->
        line({1092.0, 322.0})->
        quadratic({1048.0, 147.0}, {929.5, 59.0})->
        quadratic({811.0, -29.0}, {618.0, -29.0})->
        quadratic({385.0, -29.0}, {243.5, 124.5})->
        quadratic({102.0, 278.0}, {102.0, 532.0})->
        quadratic({102.0, 784.0}, {241.0, 938.0})->
        quadratic({380.0, 1092.0}, {606.0, 1092.0})->
        quadratic({847.0, 1092.0}, {976.0, 943.5})->
        quadratic({1105.0, 795.0}, {1110.0, 512.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    Path pathSegment1 = Path::start({893.0, 618.0});
    pathSegment1.
        quadratic({887.0, 804.0}, {814.5, 898.5})->
        quadratic({742.0, 993.0}, {606.0, 993.0})->
        quadratic({479.0, 993.0}, {406.0, 898.0})->
        quadratic({333.0, 803.0}, {317.0, 618.0})->
        line({893.0, 618.0})->
        close(&pathSegment1);
    pathSegment1.drawTo(box);

    return 1212;
}

em DejaVuSerif::f(EmBox* box)
{
    Path pathSegment0 = Path::start({881.0, 1305.0});
    pathSegment0.
        line({784.0, 1305.0})->
        quadratic({783.0, 1380.0}, {741.5, 1419.0})->
        quadratic({700.0, 1458.0}, {621.0, 1458.0})->
        quadratic({518.0, 1458.0}, {476.0, 1401.5})->
        quadratic({434.0, 1345.0}, {434.0, 1200.0})->
        line({434.0, 1063.0})->
        line({731.0, 1063.0})->
        line({731.0, 956.0})->
        line({434.0, 956.0})->
        line({434.0, 106.0})->
        line({670.0, 106.0})->
        line({670.0, 0.0})->
        line({74.0, 0.0})->
        line({74.0, 106.0})->
        line({250.0, 106.0})->
        line({250.0, 956.0})->
        line({74.0, 956.0})->
        line({74.0, 1063.0})->
        line({250.0, 1063.0})->
        line({250.0, 1196.0})->
        quadratic({250.0, 1374.0}, {342.5, 1465.0})->
        quadratic({435.0, 1556.0}, {614.0, 1556.0})->
        quadratic({681.0, 1556.0}, {748.0, 1544.0})->
        quadratic({815.0, 1532.0}, {881.0, 1507.0})->
        line({881.0, 1305.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    return 758;
}

em DejaVuSerif::g(EmBox* box)
{
    Path pathSegment0 = Path::start({1075.0, 956.0});
    pathSegment0.
        line({1075.0, 23.0})->
        quadratic({1075.0, -206.0}, {949.0, -330.5})->
        quadratic({823.0, -455.0}, {590.0, -455.0})->
        quadratic({485.0, -455.0}, {389.0, -436.0})->
        quadratic({293.0, -417.0}, {205.0, -379.0})->
        line({205.0, -156.0})->
        line({301.0, -156.0})->
        quadratic({319.0, -260.0}, {386.0, -308.0})->
        quadratic({453.0, -356.0}, {578.0, -356.0})->
        quadratic({740.0, -356.0}, {815.5, -264.5})->
        quadratic({891.0, -173.0}, {891.0, 23.0})->
        line({891.0, 166.0})->
        quadratic({837.0, 66.0}, {753.5, 18.5})->
        quadratic({670.0, -29.0}, {547.0, -29.0})->
        quadratic({351.0, -29.0}, {226.5, 126.5})->
        quadratic({102.0, 282.0}, {102.0, 532.0})->
        quadratic({102.0, 782.0}, {226.0, 937.0})->
        quadratic({350.0, 1092.0}, {547.0, 1092.0})->
        quadratic({670.0, 1092.0}, {753.5, 1044.5})->
        quadratic({837.0, 997.0}, {891.0, 897.0})->
        line({891.0, 1063.0})->
        line({1251.0, 1063.0})->
        line({1251.0, 956.0})->
        line({1075.0, 956.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    Path pathSegment1 = Path::start({891.0, 584.0});
    pathSegment1.
        quadratic({891.0, 775.0}, {817.5, 876.0})->
        quadratic({744.0, 977.0}, {604.0, 977.0})->
        quadratic({462.0, 977.0}, {389.5, 865.0})->
        quadratic({317.0, 753.0}, {317.0, 532.0})->
        quadratic({317.0, 312.0}, {389.5, 199.0})->
        quadratic({462.0, 86.0}, {604.0, 86.0})->
        quadratic({744.0, 86.0}, {817.5, 186.5})->
        quadratic({891.0, 287.0}, {891.0, 479.0})->
        line({891.0, 584.0})->
        close(&pathSegment1);
    pathSegment1.drawTo(box);

    return 1311;
}

em DejaVuSerif::h(EmBox* box)
{
    Path pathSegment0 = Path::start({84.0, 0.0});
    pathSegment0.
        line({84.0, 106.0})->
        line({250.0, 106.0})->
        line({250.0, 1450.0})->
        line({74.0, 1450.0})->
        line({74.0, 1556.0})->
        line({434.0, 1556.0})->
        line({434.0, 874.0})->
        quadratic({485.0, 982.0}, {566.5, 1037.0})->
        quadratic({648.0, 1092.0}, {756.0, 1092.0})->
        quadratic({932.0, 1092.0}, {1015.0, 991.0})->
        quadratic({1098.0, 890.0}, {1098.0, 676.0})->
        line({1098.0, 106.0})->
        line({1262.0, 106.0})->
        line({1262.0, 0.0})->
        line({754.0, 0.0})->
        line({754.0, 106.0})->
        line({913.0, 106.0})->
        line({913.0, 618.0})->
        quadratic({913.0, 813.0}, {865.5, 884.5})->
        quadratic({818.0, 956.0}, {696.0, 956.0})->
        quadratic({568.0, 956.0}, {501.0, 863.0})->
        quadratic({434.0, 770.0}, {434.0, 592.0})->
        line({434.0, 106.0})->
        line({594.0, 106.0})->
        line({594.0, 0.0})->
        line({84.0, 0.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    return 1319;
}

em DejaVuSerif::i(EmBox* box)
{
    Path pathSegment0 = Path::start({199.0, 1393.0});
    pathSegment0.
        quadratic({199.0, 1439.0}, {232.5, 1473.0})->
        quadratic({266.0, 1507.0}, {313.0, 1507.0})->
        quadratic({359.0, 1507.0}, {392.5, 1473.0})->
        quadratic({426.0, 1439.0}, {426.0, 1393.0})->
        quadratic({426.0, 1346.0}, {393.0, 1313.0})->
        quadratic({360.0, 1280.0}, {313.0, 1280.0})->
        quadratic({266.0, 1280.0}, {232.5, 1313.0})->
        quadratic({199.0, 1346.0}, {199.0, 1393.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    Path pathSegment1 = Path::start({434.0, 106.0});
    pathSegment1.
        line({608.0, 106.0})->
        line({608.0, 0.0})->
        line({74.0, 0.0})->
        line({74.0, 106.0})->
        line({250.0, 106.0})->
        line({250.0, 956.0})->
        line({74.0, 956.0})->
        line({74.0, 1063.0})->
        line({434.0, 1063.0})->
        line({434.0, 106.0})->
        close(&pathSegment1);
    pathSegment1.drawTo(box);

    return 655;
}

em DejaVuSerif::j(EmBox* box)
{
    Path pathSegment0 = Path::start({205.0, 1393.0});
    pathSegment0.
        quadratic({205.0, 1439.0}, {238.5, 1473.0})->
        quadratic({272.0, 1507.0}, {319.0, 1507.0})->
        quadratic({365.0, 1507.0}, {398.5, 1473.0})->
        quadratic({432.0, 1439.0}, {432.0, 1393.0})->
        quadratic({432.0, 1346.0}, {399.5, 1313.0})->
        quadratic({367.0, 1280.0}, {319.0, 1280.0})->
        quadratic({272.0, 1280.0}, {238.5, 1313.0})->
        quadratic({205.0, 1346.0}, {205.0, 1393.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    Path pathSegment1 = Path::start({250.0, 956.0});
    pathSegment1.
        line({76.0, 956.0})->
        line({76.0, 1063.0})->
        line({434.0, 1063.0})->
        line({434.0, -104.0})->
        quadratic({434.0, -268.0}, {336.5, -361.5})->
        quadratic({239.0, -455.0}, {68.0, -455.0})->
        quadratic({-4.0, -455.0}, {-69.5, -438.5})->
        quadratic({-135.0, -422.0}, {-197.0, -389.0})->
        line({-197.0, -170.0})->
        line({-102.0, -170.0})->
        quadratic({-95.0, -266.0}, {-52.5, -311.0})->
        quadratic({-10.0, -356.0}, {72.0, -356.0})->
        quadratic({163.0, -356.0}, {206.5, -294.5})->
        quadratic({250.0, -233.0}, {250.0, -104.0})->
        line({250.0, 956.0})->
        close(&pathSegment1);
    pathSegment1.drawTo(box);

    return 635;
}

em DejaVuSerif::k(EmBox* box)
{
    Path pathSegment0 = Path::start({586.0, 0.0});
    pathSegment0.
        line({70.0, 0.0})->
        line({70.0, 106.0})->
        line({236.0, 106.0})->
        line({236.0, 1450.0})->
        line({59.0, 1450.0})->
        line({59.0, 1556.0})->
        line({420.0, 1556.0})->
        line({420.0, 543.0})->
        line({868.0, 956.0})->
        line({715.0, 956.0})->
        line({715.0, 1063.0})->
        line({1196.0, 1063.0})->
        line({1196.0, 956.0})->
        line({1014.0, 956.0})->
        line({698.0, 664.0})->
        line({1102.0, 106.0})->
        line({1255.0, 106.0})->
        line({1255.0, 0.0})->
        line({731.0, 0.0})->
        line({731.0, 106.0})->
        line({883.0, 106.0})->
        line({565.0, 543.0})->
        line({420.0, 408.0})->
        line({420.0, 106.0})->
        line({586.0, 106.0})->
        line({586.0, 0.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    return 1241;
}

em DejaVuSerif::l(EmBox* box)
{
    Path pathSegment0 = Path::start({420.0, 106.0});
    pathSegment0.
        line({594.0, 106.0})->
        line({594.0, 0.0})->
        line({59.0, 0.0})->
        line({59.0, 106.0})->
        line({236.0, 106.0})->
        line({236.0, 1450.0})->
        line({59.0, 1450.0})->
        line({59.0, 1556.0})->
        line({420.0, 1556.0})->
        line({420.0, 106.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    return 655;
}

em DejaVuSerif::m(EmBox* box)
{
    Path pathSegment0 = Path::start({1061.0, 856.0});
    pathSegment0.
        quadratic({1114.0, 973.0}, {1196.5, 1032.5})->
        quadratic({1279.0, 1092.0}, {1389.0, 1092.0})->
        quadratic({1556.0, 1092.0}, {1638.0, 988.5})->
        quadratic({1720.0, 885.0}, {1720.0, 676.0})->
        line({1720.0, 106.0})->
        line({1886.0, 106.0})->
        line({1886.0, 0.0})->
        line({1376.0, 0.0})->
        line({1376.0, 106.0})->
        line({1536.0, 106.0})->
        line({1536.0, 655.0})->
        quadratic({1536.0, 818.0}, {1488.0, 887.0})->
        quadratic({1440.0, 956.0}, {1329.0, 956.0})->
        quadratic({1206.0, 956.0}, {1141.5, 863.0})->
        quadratic({1077.0, 770.0}, {1077.0, 592.0})->
        line({1077.0, 106.0})->
        line({1237.0, 106.0})->
        line({1237.0, 0.0})->
        line({733.0, 0.0})->
        line({733.0, 106.0})->
        line({893.0, 106.0})->
        line({893.0, 662.0})->
        quadratic({893.0, 821.0}, {845.0, 888.5})->
        quadratic({797.0, 956.0}, {686.0, 956.0})->
        quadratic({563.0, 956.0}, {498.5, 863.0})->
        quadratic({434.0, 770.0}, {434.0, 592.0})->
        line({434.0, 106.0})->
        line({594.0, 106.0})->
        line({594.0, 0.0})->
        line({84.0, 0.0})->
        line({84.0, 106.0})->
        line({250.0, 106.0})->
        line({250.0, 958.0})->
        line({74.0, 958.0})->
        line({74.0, 1063.0})->
        line({434.0, 1063.0})->
        line({434.0, 874.0})->
        quadratic({485.0, 980.0}, {564.0, 1036.0})->
        quadratic({643.0, 1092.0}, {743.0, 1092.0})->
        quadratic({867.0, 1092.0}, {950.0, 1030.5})->
        quadratic({1033.0, 969.0}, {1061.0, 856.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    return 1942;
}

em DejaVuSerif::n(EmBox* box)
{
    Path pathSegment0 = Path::start({84.0, 0.0});
    pathSegment0.
        line({84.0, 106.0})->
        line({250.0, 106.0})->
        line({250.0, 956.0})->
        line({74.0, 956.0})->
        line({74.0, 1063.0})->
        line({434.0, 1063.0})->
        line({434.0, 874.0})->
        quadratic({485.0, 982.0}, {566.5, 1037.0})->
        quadratic({648.0, 1092.0}, {756.0, 1092.0})->
        quadratic({932.0, 1092.0}, {1015.0, 991.0})->
        quadratic({1098.0, 890.0}, {1098.0, 676.0})->
        line({1098.0, 106.0})->
        line({1262.0, 106.0})->
        line({1262.0, 0.0})->
        line({754.0, 0.0})->
        line({754.0, 106.0})->
        line({913.0, 106.0})->
        line({913.0, 618.0})->
        quadratic({913.0, 813.0}, {865.0, 885.5})->
        quadratic({817.0, 958.0}, {696.0, 958.0})->
        quadratic({568.0, 958.0}, {501.0, 864.5})->
        quadratic({434.0, 771.0}, {434.0, 592.0})->
        line({434.0, 106.0})->
        line({594.0, 106.0})->
        line({594.0, 0.0})->
        line({84.0, 0.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    return 1319;
}

em DejaVuSerif::o(EmBox* box)
{
    Path pathSegment0 = Path::start({616.0, 70.0});
    pathSegment0.
        quadratic({764.0, 70.0}, {839.5, 187.0})->
        quadratic({915.0, 304.0}, {915.0, 532.0})->
        quadratic({915.0, 760.0}, {839.5, 876.5})->
        quadratic({764.0, 993.0}, {616.0, 993.0})->
        quadratic({468.0, 993.0}, {392.5, 876.5})->
        quadratic({317.0, 760.0}, {317.0, 532.0})->
        quadratic({317.0, 304.0}, {393.0, 187.0})->
        quadratic({469.0, 70.0}, {616.0, 70.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    Path pathSegment1 = Path::start({616.0, -29.0});
    pathSegment1.
        quadratic({384.0, -29.0}, {243.0, 124.5})->
        quadratic({102.0, 278.0}, {102.0, 532.0})->
        quadratic({102.0, 786.0}, {242.5, 939.0})->
        quadratic({383.0, 1092.0}, {616.0, 1092.0})->
        quadratic({849.0, 1092.0}, {989.5, 939.0})->
        quadratic({1130.0, 786.0}, {1130.0, 532.0})->
        quadratic({1130.0, 278.0}, {989.5, 124.5})->
        quadratic({849.0, -29.0}, {616.0, -29.0})->
        close(&pathSegment1);
    pathSegment1.drawTo(box);

    return 1233;
}

em DejaVuSerif::p(EmBox* box)
{
    Path pathSegment0 = Path::start({420.0, 584.0});
    pathSegment0.
        line({420.0, 479.0})->
        quadratic({420.0, 287.0}, {493.5, 186.5})->
        quadratic({567.0, 86.0}, {707.0, 86.0})->
        quadratic({848.0, 86.0}, {920.5, 199.0})->
        quadratic({993.0, 312.0}, {993.0, 532.0})->
        quadratic({993.0, 753.0}, {920.5, 865.0})->
        quadratic({848.0, 977.0}, {707.0, 977.0})->
        quadratic({567.0, 977.0}, {493.5, 876.0})->
        quadratic({420.0, 775.0}, {420.0, 584.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    Path pathSegment1 = Path::start({236.0, 956.0});
    pathSegment1.
        line({59.0, 956.0})->
        line({59.0, 1063.0})->
        line({420.0, 1063.0})->
        line({420.0, 897.0})->
        quadratic({474.0, 997.0}, {557.5, 1044.5})->
        quadratic({641.0, 1092.0}, {764.0, 1092.0})->
        quadratic({960.0, 1092.0}, {1084.0, 937.0})->
        quadratic({1208.0, 782.0}, {1208.0, 532.0})->
        quadratic({1208.0, 282.0}, {1084.0, 126.5})->
        quadratic({960.0, -29.0}, {764.0, -29.0})->
        quadratic({641.0, -29.0}, {557.5, 18.5})->
        quadratic({474.0, 66.0}, {420.0, 166.0})->
        line({420.0, -319.0})->
        line({594.0, -319.0})->
        line({594.0, -426.0})->
        line({59.0, -426.0})->
        line({59.0, -319.0})->
        line({236.0, -319.0})->
        line({236.0, 956.0})->
        close(&pathSegment1);
    pathSegment1.drawTo(box);

    return 1311;
}

em DejaVuSerif::q(EmBox* box)
{
    Path pathSegment0 = Path::start({1075.0, 956.0});
    pathSegment0.
        line({1075.0, -319.0})->
        line({1251.0, -319.0})->
        line({1251.0, -426.0})->
        line({717.0, -426.0})->
        line({717.0, -319.0})->
        line({891.0, -319.0})->
        line({891.0, 166.0})->
        quadratic({837.0, 66.0}, {753.5, 18.5})->
        quadratic({670.0, -29.0}, {547.0, -29.0})->
        quadratic({351.0, -29.0}, {226.5, 126.5})->
        quadratic({102.0, 282.0}, {102.0, 532.0})->
        quadratic({102.0, 782.0}, {226.0, 937.0})->
        quadratic({350.0, 1092.0}, {547.0, 1092.0})->
        quadratic({670.0, 1092.0}, {753.5, 1044.5})->
        quadratic({837.0, 997.0}, {891.0, 897.0})->
        line({891.0, 1063.0})->
        line({1251.0, 1063.0})->
        line({1251.0, 956.0})->
        line({1075.0, 956.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    Path pathSegment1 = Path::start({891.0, 584.0});
    pathSegment1.
        quadratic({891.0, 775.0}, {817.5, 876.0})->
        quadratic({744.0, 977.0}, {604.0, 977.0})->
        quadratic({462.0, 977.0}, {389.5, 865.0})->
        quadratic({317.0, 753.0}, {317.0, 532.0})->
        quadratic({317.0, 312.0}, {389.5, 199.0})->
        quadratic({462.0, 86.0}, {604.0, 86.0})->
        quadratic({744.0, 86.0}, {817.5, 186.5})->
        quadratic({891.0, 287.0}, {891.0, 479.0})->
        line({891.0, 584.0})->
        close(&pathSegment1);
    pathSegment1.drawTo(box);

    return 1311;
}

em DejaVuSerif::r(EmBox* box)
{
    Path pathSegment0 = Path::start({979.0, 1065.0});
    pathSegment0.
        line({979.0, 799.0})->
        line({873.0, 799.0})->
        quadratic({868.0, 878.0}, {829.0, 917.0})->
        quadratic({790.0, 956.0}, {715.0, 956.0})->
        quadratic({579.0, 956.0}, {506.5, 862.0})->
        quadratic({434.0, 768.0}, {434.0, 592.0})->
        line({434.0, 106.0})->
        line({647.0, 106.0})->
        line({647.0, 0.0})->
        line({84.0, 0.0})->
        line({84.0, 106.0})->
        line({250.0, 106.0})->
        line({250.0, 958.0})->
        line({74.0, 958.0})->
        line({74.0, 1063.0})->
        line({434.0, 1063.0})->
        line({434.0, 874.0})->
        quadratic({488.0, 985.0}, {573.0, 1038.5})->
        quadratic({658.0, 1092.0}, {780.0, 1092.0})->
        quadratic({825.0, 1092.0}, {874.5, 1085.0})->
        quadratic({924.0, 1078.0}, {979.0, 1065.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    return 979;
}

em DejaVuSerif::s(EmBox* box)
{
    Path pathSegment0 = Path::start({115.0, 59.0});
    pathSegment0.
        line({115.0, 307.0})->
        line({221.0, 307.0})->
        quadratic({225.0, 188.0}, {295.5, 129.0})->
        quadratic({366.0, 70.0}, {504.0, 70.0})->
        quadratic({628.0, 70.0}, {693.0, 116.5})->
        quadratic({758.0, 163.0}, {758.0, 252.0})->
        quadratic({758.0, 322.0}, {710.5, 365.0})->
        quadratic({663.0, 408.0}, {510.0, 457.0})->
        line({377.0, 502.0})->
        quadratic({240.0, 546.0}, {178.5, 612.0})->
        quadratic({117.0, 678.0}, {117.0, 780.0})->
        quadratic({117.0, 926.0}, {224.0, 1009.0})->
        quadratic({331.0, 1092.0}, {520.0, 1092.0})->
        quadratic({604.0, 1092.0}, {697.0, 1070.0})->
        quadratic({790.0, 1048.0}, {889.0, 1006.0})->
        line({889.0, 774.0})->
        line({783.0, 774.0})->
        quadratic({779.0, 877.0}, {711.0, 935.0})->
        quadratic({643.0, 993.0}, {526.0, 993.0})->
        quadratic({410.0, 993.0}, {350.5, 952.0})->
        quadratic({291.0, 911.0}, {291.0, 829.0})->
        quadratic({291.0, 762.0}, {336.0, 721.5})->
        quadratic({381.0, 681.0}, {516.0, 639.0})->
        line({662.0, 594.0})->
        quadratic({813.0, 547.0}, {879.5, 476.5})->
        quadratic({946.0, 406.0}, {946.0, 295.0})->
        quadratic({946.0, 144.0}, {830.5, 57.5})->
        quadratic({715.0, -29.0}, {512.0, -29.0})->
        quadratic({409.0, -29.0}, {311.0, -7.0})->
        quadratic({213.0, 15.0}, {115.0, 59.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    return 1051;
}

em DejaVuSerif::t(EmBox* box)
{
    Path pathSegment0 = Path::start({221.0, 956.0});
    pathSegment0.
        line({59.0, 956.0})->
        line({59.0, 1063.0})->
        line({221.0, 1063.0})->
        line({221.0, 1393.0})->
        line({406.0, 1393.0})->
        line({406.0, 1063.0})->
        line({752.0, 1063.0})->
        line({752.0, 956.0})->
        line({406.0, 956.0})->
        line({406.0, 281.0})->
        quadratic({406.0, 146.0}, {432.0, 108.0})->
        quadratic({458.0, 70.0}, {528.0, 70.0})->
        quadratic({600.0, 70.0}, {633.0, 112.5})->
        quadratic({666.0, 155.0}, {668.0, 250.0})->
        line({807.0, 250.0})->
        quadratic({799.0, 105.0}, {728.0, 38.0})->
        quadratic({657.0, -29.0}, {512.0, -29.0})->
        quadratic({353.0, -29.0}, {287.0, 41.5})->
        quadratic({221.0, 112.0}, {221.0, 281.0})->
        line({221.0, 956.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    return 823;
}

em DejaVuSerif::u(EmBox* box)
{
    Path pathSegment0 = Path::start({725.0, 1063.0});
    pathSegment0.
        line({1069.0, 1063.0})->
        line({1069.0, 106.0})->
        line({1243.0, 106.0})->
        line({1243.0, 0.0})->
        line({885.0, 0.0})->
        line({885.0, 188.0})->
        quadratic({834.0, 82.0}, {753.0, 26.5})->
        quadratic({672.0, -29.0}, {565.0, -29.0})->
        quadratic({388.0, -29.0}, {304.5, 71.5})->
        quadratic({221.0, 172.0}, {221.0, 387.0})->
        line({221.0, 956.0})->
        line({55.0, 956.0})->
        line({55.0, 1063.0})->
        line({406.0, 1063.0})->
        line({406.0, 444.0})->
        quadratic({406.0, 250.0}, {453.5, 178.0})->
        quadratic({501.0, 106.0}, {623.0, 106.0})->
        quadratic({751.0, 106.0}, {818.0, 200.0})->
        quadratic({885.0, 294.0}, {885.0, 473.0})->
        line({885.0, 956.0})->
        line({725.0, 956.0})->
        line({725.0, 1063.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    return 1319;
}

em DejaVuSerif::v(EmBox* box)
{
    Path pathSegment0 = Path::start({506.0, 0.0});
    pathSegment0.
        line({115.0, 956.0})->
        line({-6.0, 956.0})->
        line({-6.0, 1063.0})->
        line({483.0, 1063.0})->
        line({483.0, 956.0})->
        line({313.0, 956.0})->
        line({612.0, 225.0})->
        line({911.0, 956.0})->
        line({752.0, 956.0})->
        line({752.0, 1063.0})->
        line({1151.0, 1063.0})->
        line({1151.0, 956.0})->
        line({1032.0, 956.0})->
        line({641.0, 0.0})->
        line({506.0, 0.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    return 1157;
}

em DejaVuSerif::w(EmBox* box)
{
    Path pathSegment0 = Path::start({983.0, 1063.0});
    pathSegment0.
        line({1255.0, 233.0})->
        line({1495.0, 956.0})->
        line({1341.0, 956.0})->
        line({1341.0, 1063.0})->
        line({1726.0, 1063.0})->
        line({1726.0, 956.0})->
        line({1608.0, 956.0})->
        line({1292.0, 0.0})->
        line({1139.0, 0.0})->
        line({877.0, 795.0})->
        line({614.0, 0.0})->
        line({467.0, 0.0})->
        line({152.0, 956.0})->
        line({33.0, 956.0})->
        line({33.0, 1063.0})->
        line({514.0, 1063.0})->
        line({514.0, 956.0})->
        line({342.0, 956.0})->
        line({580.0, 233.0})->
        line({854.0, 1063.0})->
        line({983.0, 1063.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    return 1753;
}

em DejaVuSerif::x(EmBox* box)
{
    Path pathSegment0 = Path::start({596.0, 649.0});
    pathSegment0.
        line({819.0, 956.0})->
        line({676.0, 956.0})->
        line({676.0, 1063.0})->
        line({1085.0, 1063.0})->
        line({1085.0, 956.0})->
        line({944.0, 956.0})->
        line({659.0, 563.0})->
        line({991.0, 106.0})->
        line({1130.0, 106.0})->
        line({1130.0, 0.0})->
        line({639.0, 0.0})->
        line({639.0, 106.0})->
        line({774.0, 106.0})->
        line({543.0, 424.0})->
        line({311.0, 106.0})->
        line({449.0, 106.0})->
        line({449.0, 0.0})->
        line({45.0, 0.0})->
        line({45.0, 106.0})->
        line({186.0, 106.0})->
        line({479.0, 510.0})->
        line({156.0, 956.0})->
        line({25.0, 956.0})->
        line({25.0, 1063.0})->
        line({500.0, 1063.0})->
        line({500.0, 956.0})->
        line({373.0, 956.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    return 1155;
}

em DejaVuSerif::y(EmBox* box)
{
    Path pathSegment0 = Path::start({442.0, -195.0});
    pathSegment0.
        line({512.0, -18.0})->
        line({115.0, 956.0})->
        line({-6.0, 956.0})->
        line({-6.0, 1063.0})->
        line({483.0, 1063.0})->
        line({483.0, 956.0})->
        line({313.0, 956.0})->
        line({612.0, 225.0})->
        line({911.0, 956.0})->
        line({752.0, 956.0})->
        line({752.0, 1063.0})->
        line({1151.0, 1063.0})->
        line({1151.0, 956.0})->
        line({1032.0, 956.0})->
        line({545.0, -240.0})->
        quadratic({495.0, -364.0}, {434.0, -409.5})->
        quadratic({373.0, -455.0}, {262.0, -455.0})->
        quadratic({215.0, -455.0}, {165.5, -447.0})->
        quadratic({116.0, -439.0}, {66.0, -424.0})->
        line({66.0, -221.0})->
        line({160.0, -221.0})->
        quadratic({166.0, -289.0}, {194.5, -318.5})->
        quadratic({223.0, -348.0}, {283.0, -348.0})->
        quadratic({338.0, -348.0}, {371.5, -317.5})->
        quadratic({405.0, -287.0}, {442.0, -195.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    return 1157;
}

em DejaVuSerif::z(EmBox* box)
{
    Path pathSegment0 = Path::start({82.0, 0.0});
    pathSegment0.
        line({82.0, 86.0})->
        line({748.0, 956.0})->
        line({221.0, 956.0})->
        line({221.0, 772.0})->
        line({115.0, 772.0})->
        line({115.0, 1063.0})->
        line({985.0, 1063.0})->
        line({985.0, 977.0})->
        line({319.0, 106.0})->
        line({897.0, 106.0})->
        line({897.0, 299.0})->
        line({1004.0, 299.0})->
        line({1004.0, 0.0})->
        line({82.0, 0.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    return 1079;
}

em DejaVuSerif::braceleft(EmBox* box)
{
    Path pathSegment0 = Path::start({1047.0, -229.0});
    pathSegment0.
        line({1047.0, -334.0})->
        line({985.0, -334.0})->
        quadratic({736.0, -334.0}, {651.5, -260.0})->
        quadratic({567.0, -186.0}, {567.0, 35.0})->
        line({567.0, 293.0})->
        quadratic({567.0, 443.0}, {513.0, 501.0})->
        quadratic({459.0, 559.0}, {317.0, 559.0})->
        line({256.0, 559.0})->
        line({256.0, 664.0})->
        line({317.0, 664.0})->
        quadratic({459.0, 664.0}, {513.0, 722.0})->
        quadratic({567.0, 780.0}, {567.0, 930.0})->
        line({567.0, 1188.0})->
        quadratic({567.0, 1409.0}, {651.5, 1482.5})->
        quadratic({736.0, 1556.0}, {985.0, 1556.0})->
        line({1047.0, 1556.0})->
        line({1047.0, 1452.0})->
        line({979.0, 1452.0})->
        quadratic({838.0, 1452.0}, {795.0, 1408.0})->
        quadratic({752.0, 1364.0}, {752.0, 1223.0})->
        line({752.0, 936.0})->
        quadratic({752.0, 778.0}, {702.0, 710.0})->
        quadratic({652.0, 642.0}, {522.0, 612.0})->
        quadratic({654.0, 578.0}, {703.0, 511.0})->
        quadratic({752.0, 444.0}, {752.0, 287.0})->
        line({752.0, 0.0})->
        quadratic({752.0, -141.0}, {795.0, -185.0})->
        quadratic({838.0, -229.0}, {979.0, -229.0})->
        line({1047.0, -229.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    return 2000;
}

em DejaVuSerif::bar(EmBox* box)
{
    Path pathSegment0 = Path::start({426.0, 1565.0});
    pathSegment0.
        line({426.0, -483.0})->
        line({264.0, -483.0})->
        line({264.0, 1565.0})->
        line({426.0, 1565.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    return 690;
}

em DejaVuSerif::braceright(EmBox* box)
{
    Path pathSegment0 = Path::start({256.0, -229.0});
    pathSegment0.
        line({326.0, -229.0})->
        quadratic({466.0, -229.0}, {508.5, -185.5})->
        quadratic({551.0, -142.0}, {551.0, 0.0})->
        line({551.0, 287.0})->
        quadratic({551.0, 444.0}, {600.0, 511.0})->
        quadratic({649.0, 578.0}, {780.0, 612.0})->
        quadratic({650.0, 642.0}, {600.5, 710.0})->
        quadratic({551.0, 778.0}, {551.0, 936.0})->
        line({551.0, 1223.0})->
        quadratic({551.0, 1365.0}, {508.5, 1408.5})->
        quadratic({466.0, 1452.0}, {326.0, 1452.0})->
        line({256.0, 1452.0})->
        line({256.0, 1556.0})->
        line({319.0, 1556.0})->
        quadratic({568.0, 1556.0}, {651.5, 1482.5})->
        quadratic({735.0, 1409.0}, {735.0, 1188.0})->
        line({735.0, 930.0})->
        quadratic({735.0, 780.0}, {789.0, 722.0})->
        quadratic({843.0, 664.0}, {985.0, 664.0})->
        line({1047.0, 664.0})->
        line({1047.0, 559.0})->
        line({985.0, 559.0})->
        quadratic({843.0, 559.0}, {789.0, 501.0})->
        quadratic({735.0, 443.0}, {735.0, 293.0})->
        line({735.0, 35.0})->
        quadratic({735.0, -186.0}, {651.5, -260.0})->
        quadratic({568.0, -334.0}, {319.0, -334.0})->
        line({256.0, -334.0})->
        line({256.0, -229.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    return 2000;
}

em DejaVuSerif::asciitilde(EmBox* box)
{
    Path pathSegment0 = Path::start({1499.0, 807.0});
    pathSegment0.
        line({1499.0, 659.0})->
        quadratic({1399.0, 571.0}, {1309.0, 529.0})->
        quadratic({1219.0, 487.0}, {1126.0, 487.0})->
        quadratic({1030.0, 487.0}, {856.0, 553.0})->
        line({846.0, 557.0})->
        quadratic({835.0, 561.0}, {813.0, 570.0})->
        quadratic({666.0, 627.0}, {571.0, 627.0})->
        quadratic({479.0, 627.0}, {392.5, 590.5})->
        quadratic({306.0, 554.0}, {217.0, 477.0})->
        line({217.0, 629.0})->
        quadratic({317.0, 716.0}, {406.5, 756.5})->
        quadratic({496.0, 797.0}, {590.0, 797.0})->
        quadratic({686.0, 797.0}, {860.0, 731.0})->
        line({870.0, 727.0})->
        quadratic({881.0, 723.0}, {901.0, 715.0})->
        quadratic({1046.0, 657.0}, {1143.0, 657.0})->
        quadratic({1235.0, 657.0}, {1323.0, 694.0})->
        quadratic({1411.0, 731.0}, {1499.0, 807.0})->
        close(&pathSegment0);
    pathSegment0.drawTo(box);

    return 1716;
}

em DejaVuSerif::nonbreakingspace(EmBox* box)
{
    return 651;
}
