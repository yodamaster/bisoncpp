// Generated by Bisonc++ V5.00.00 on Wed, 06 Apr 2016 13:41:57 +0530

#ifndef Parser_h_included
#define Parser_h_included

// added for mfcalc's memory
#include <unordered_map>
#include <string>

// $insert baseclass
#include "Parserbase.h"


#undef Parser
class Parser: public ParserBase
{
    typedef std::pair<char const *, double (*)(double)> FunctionPair;

    std::unordered_map<std::string, double> d_symbols;

    static std::unordered_map<std::string, double (*)(double)> s_functions;
    static FunctionPair s_funTab[];
            
        
    public:
        int parse();

    private:
        void error(char const *msg);    // called on (syntax) errors
        int lex();                      // returns the next token from the
                                        // lexical scanner. 
        void print();                   // use, e.g., d_token, d_loc

    // support functions for parse():
        void executeAction(int ruleNr);
        void errorRecovery();
        int lookup(bool recovery);
        void nextToken();
        void print__();
        void exceptionHandler__(std::exception const &exc);
};


#endif
