// Generated by Flexc++ V0.09.50 on Wed, 08 Feb 2012 11:05:26 +0100

#ifndef Scanner_H_INCLUDED_
#define Scanner_H_INCLUDED_

// $insert baseclass_h
#include "scannerbase.h"

#include <iosfwd>

#include <string>
#include <utility>

#include "../block/block.h"

namespace FBB
{
    class Mstream;
}

// $insert classHead
class Scanner: public ScannerBase
{
    size_t      d_number;       // only valid after tokens NUMBER and
                                // after escape(), octal() and 
                                // hexadecimal(). Illegal (long)
                                // character constants (> 1 char) have bit
                                // 8 set.

    bool        d_include;      // set to true/false by lexer-actions

//FBB: remove?
    bool        d_warnAssign;   // see warnAssign() and lexer

    char        d_commentChar[2];   // set to ' ' in `lexer' when C
                                // comment without \n is matched,
                                // otherwise set to \n. See
                                // `lexer' for details

    Block       d_block;            // action block retrieved fm the input

    std::string d_rawString;        // Raw-string sentinel
    std::string d_canonicalQuote;   // canonical quoted ident.
    std::string const &d_matched;

    size_t          d_maxDepth;         // max. file inclusion depth
    size_t          d_inclusionDepth;   // actual inclusion depth

    public:
        Scanner(std::string const &infile);
        
        // $insert lexFunctionDecl
        int lex();
        Block &block();
        std::string const &canonicalQuote();
        void clearBlock();
        size_t number() const;
        bool hasBlock() const;

        void beginTypeSpec();

    private:
//FBB        void warnAssign();

        void print();
        int lex__();
        int executeAction__(size_t ruleNr);

        void preCode();     // re-implement this function for code that must 
                            // be exec'ed before the patternmatching starts

        void postCode(PostEnum__  type);

        bool handleXstring(size_t nRedo);   // performs pushStream
        int eoln();

        void returnTypeSpec();
        void returnQuoted(void (Scanner::*handler)());  // handle quoted
                                                        // constants
        void escape();
        void checkZeroNumber();
        void octal();
        void hexadecimal();
        void matched2();
        void matched1();
        void multiCharQuote();

        void rawString();
        void checkEndOfRawString();

        void setTags() const;
        void setLineNrs() const;

        bool popStream();
};

// $insert inlineLexFunction
inline int Scanner::lex()
{
    return lex__();
}

inline void Scanner::preCode() 
{
}

inline void Scanner::postCode(PostEnum__  type)
{
}

inline void Scanner::print() 
{
    print__();
}

inline Block &Scanner::block()
{
    return d_block;
}

inline void Scanner::clearBlock()
{
    d_block.clear();
}

inline size_t Scanner::number() const
{
    return d_number;
}

inline bool Scanner::hasBlock() const
{
    return not d_block.empty();
}

inline void Scanner::beginTypeSpec()
{
    begin(StartCondition__::typespec);
}

#endif // Scanner_H_INCLUDED_

