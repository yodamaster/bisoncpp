#include "parser.ih"

size_t Parser::s_nHidden;

ostringstream Parser::s_hiddenName;

string Parser::s_semanticValue {"d_val__"};   
                                    // name of the semantic value variable
                                    // used by the generated parser.
string Parser::s_semanticValueStack {"d_vsp__"};  
                                    // name of the semantic value stack
                                    // used by the generated parser
char Parser::s_locationValueStack[] = "d_lsp__";  
                                    // name of the location value stack
                                    // used by the generated parser
char Parser::s_locationValue[] = "d_loc__";  
                                    // name of the location value variable
                                    // used by the generated parser (@0)
char const Parser::s_stype__[] = "STYPE__";
                                    // generic semantic value for POLYMORPHIC

string const Parser::s_undefined{"<undefined>"};


Parser::ADmap Parser::s_single =
{
       {AtDollar::AA,       &Parser::loc},      // @@
       {AtDollar::An,       &Parser::locEl},    // @nr
                                
       {AtDollar::DD,       &Parser::dval},     // $$
       {AtDollar::refDD,    &Parser::dval},     // _$$
       {AtDollar::DDm,      &Parser::dvalMem},  // $$.
       {AtDollar::DDp,      &Parser::dvalPtr},  // $$->

       {AtDollar::Dn,       &Parser::svs},      // $nr
       {AtDollar::refDn,    &Parser::svs},      // _$nr
       {AtDollar::Dnm,      &Parser::svsMem},   // $nr.
       {AtDollar::Dnp,      &Parser::svsPtr},   // $nr->

       {AtDollar::D_,       &Parser::svs},      // $-nr
       {AtDollar::refD_,    &Parser::svs},      // _$-nr
       {AtDollar::D_m,      &Parser::svsMem},   // $-nr.
       {AtDollar::D_p,      &Parser::svsPtr},   // $-nr->
                                
       {AtDollar::Dt_,      &Parser::errNoTag}, // $<TAG>-nr
       {AtDollar::Dt_m,     &Parser::errNoTag}, // $<TAG>-nr.
       {AtDollar::Dt_p,     &Parser::errNoTag}, // $<TAG>-nr->
};

Parser::ADmap Parser::s_union =
{
       {AtDollar::AA,       &Parser::loc},              // @@
       {AtDollar::An,       &Parser::locEl},            // @nr
                                                    
       {AtDollar::DD,       &Parser::dvalUnion},        // $$
       {AtDollar::refDD,    &Parser::dval},             // _$$
       {AtDollar::DDm,      &Parser::dvalUnionMem},     // $$.
       {AtDollar::DDp,      &Parser::dvalUnionPtr},     // $$->
                                                    
       {AtDollar::Dn,       &Parser::svsUnion},         // $nr
       {AtDollar::refDn,    &Parser::svs},              // _$nr
       {AtDollar::Dnm,      &Parser::svsUnionMem},      // $nr.
       {AtDollar::Dnp,      &Parser::svsUnionPtr},      // $nr->
                                                    
       {AtDollar::D_,       &Parser::svs},              // $-nr
       {AtDollar::refD_,    &Parser::svs},              // _$-nr
       {AtDollar::D_m,      &Parser::svsMem},           // $-nr.
       {AtDollar::D_p,      &Parser::svsPtr},           // $-nr->
                                                    
       {AtDollar::Dt_,      &Parser::svsUnionTag},      // $<TAG>-nr
       {AtDollar::Dt_m,     &Parser::svsUnionTagMem},   // $<TAG>-nr.
       {AtDollar::Dt_p,     &Parser::svsUnionTagPtr},   // $<TAG>-nr->
};

Parser::ADmap Parser::s_polymorphic =
{
       {AtDollar::AA,       &Parser::loc},              // @@
       {AtDollar::An,       &Parser::locEl},            // @nr
                                                    
       {AtDollar::DD,       &Parser::dvalPoly},         // $$
       {AtDollar::refDD,    &Parser::dval},             // _$$
       {AtDollar::DDm,      &Parser::dvalPolyMem},      // $$.
       {AtDollar::DDp,      &Parser::dvalPolyPtr},      // $$->
                                                    
       {AtDollar::Dn,       &Parser::svsPoly},          // $nr
       {AtDollar::refDn,    &Parser::svs},              // _$nr
       {AtDollar::Dnm,      &Parser::svsPolyMem},       // $nr.
       {AtDollar::Dnp,      &Parser::svsPolyPtr},       // $nr->
                                                    
       {AtDollar::D_,       &Parser::svs},              // $-nr
       {AtDollar::refD_,    &Parser::svs},              // _$-nr
       {AtDollar::D_m,      &Parser::svsMem},           // $-nr.
       {AtDollar::D_p,      &Parser::svsPtr},           // $-nr->
                                                    
       {AtDollar::Dt_,      &Parser::svsPolyTag},       // $<TAG>-nr
       {AtDollar::Dt_m,     &Parser::svsPolyTagMem},    // $<TAG>-nr.
       {AtDollar::Dt_p,     &Parser::svsPolyTagPtr},    // $<TAG>-nr->
};
