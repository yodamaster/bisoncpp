#include "parser.ih"

string Parser::returnPolymorphic(AtDollar const &atd) const
{
    string ret;

    switch (semTag("tag", atd, &Parser::findTag))
    {
        case AUTO:          // use the %type specified semantic value
            ret =   ".get<" + 
                    (
                        atd.returnValue() ?
                            d_rules.sType() : d_rules.sType(atd.nr())
                    ) +
                    ">()";
        break;

        case EXPLICIT:
            ret = ".get<" + atd.id() + ">()";
        break;

        case NONE:
        break;
    }

    return ret;
}

