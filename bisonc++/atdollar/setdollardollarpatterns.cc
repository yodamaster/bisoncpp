#include "atdollar.ih"

//          DD,             // $$
//          DDm,            // $$.
//          DDp,            // $$->

void AtDollar::setDollarDollarPatterns()
{
    switch (d_text.back())
    {
        case '$':
            d_pattern = DD;
        return;

        case '.':
            d_pattern = DDm;
        return;

        case '>':
            d_pattern = DDp;
        return;
    }
}
