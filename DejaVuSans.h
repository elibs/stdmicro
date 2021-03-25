#ifndef __DEJA_VU_SANS_H
#define __DEJA_VU_SANS_H

#include "EmBox.h"
#include "FontCommon.h"
#include "FontFace.h"

/**
 * Font generated via use of converter.py, from DejaVuSans font, which is
 * distributed under the license of:
 *
 * Bitstream Vera and Public Domain
 *
 * Converted to svg with FontForge.
 *
 * NOTE: Glyphs were removed to reduce overall size.
 */
class DejaVuSans: public FontFace
{
public:
    virtual ~DejaVuSans(void);

    glyph operator[](int character) const override;
private:

    static em space(EmBox* box);

    static em exclam(EmBox* box);

    static em quotedbl(EmBox* box);

    static em numbersign(EmBox* box);

    static em dollar(EmBox* box);

    static em percent(EmBox* box);

    static em ampersand(EmBox* box);

    static em quotesingle(EmBox* box);

    static em parenleft(EmBox* box);

    static em parenright(EmBox* box);

    static em asterisk(EmBox* box);

    static em plus(EmBox* box);

    static em comma(EmBox* box);

    static em hyphen(EmBox* box);

    static em period(EmBox* box);

    static em slash(EmBox* box);

    static em zero(EmBox* box);

    static em one(EmBox* box);

    static em two(EmBox* box);

    static em three(EmBox* box);

    static em four(EmBox* box);

    static em five(EmBox* box);

    static em six(EmBox* box);

    static em seven(EmBox* box);

    static em eight(EmBox* box);

    static em nine(EmBox* box);

    static em colon(EmBox* box);

    static em semicolon(EmBox* box);

    static em less(EmBox* box);

    static em equal(EmBox* box);

    static em greater(EmBox* box);

    static em question(EmBox* box);

    static em at(EmBox* box);

    static em A(EmBox* box);

    static em B(EmBox* box);

    static em C(EmBox* box);

    static em D(EmBox* box);

    static em E(EmBox* box);

    static em F(EmBox* box);

    static em G(EmBox* box);

    static em H(EmBox* box);

    static em I(EmBox* box);

    static em J(EmBox* box);

    static em K(EmBox* box);

    static em L(EmBox* box);

    static em M(EmBox* box);

    static em N(EmBox* box);

    static em O(EmBox* box);

    static em P(EmBox* box);

    static em Q(EmBox* box);

    static em R(EmBox* box);

    static em S(EmBox* box);

    static em T(EmBox* box);

    static em U(EmBox* box);

    static em V(EmBox* box);

    static em W(EmBox* box);

    static em X(EmBox* box);

    static em Y(EmBox* box);

    static em Z(EmBox* box);

    static em bracketleft(EmBox* box);

    static em backslash(EmBox* box);

    static em bracketright(EmBox* box);

    static em asciicircum(EmBox* box);

    static em underscore(EmBox* box);

    static em grave(EmBox* box);

    static em a(EmBox* box);

    static em b(EmBox* box);

    static em c(EmBox* box);

    static em d(EmBox* box);

    static em e(EmBox* box);

    static em f(EmBox* box);

    static em g(EmBox* box);

    static em h(EmBox* box);

    static em i(EmBox* box);

    static em j(EmBox* box);

    static em k(EmBox* box);

    static em l(EmBox* box);

    static em m(EmBox* box);

    static em n(EmBox* box);

    static em o(EmBox* box);

    static em p(EmBox* box);

    static em q(EmBox* box);

    static em r(EmBox* box);

    static em s(EmBox* box);

    static em t(EmBox* box);

    static em u(EmBox* box);

    static em v(EmBox* box);

    static em w(EmBox* box);

    static em x(EmBox* box);

    static em y(EmBox* box);

    static em z(EmBox* box);

    static em braceleft(EmBox* box);

    static em bar(EmBox* box);

    static em braceright(EmBox* box);

    static em asciitilde(EmBox* box);

    static em nonbreakingspace(EmBox* box);

};

#endif
