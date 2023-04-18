#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Word_info.h"
#include "Syntax.h"

using std::string;
using std::vector;
using std::cout;

void Syntax::syntax_analysis(const vector<Word_info*> &to_scan) {
    parse_Program();
}

void Syntax::match_token(const string &expected) {
    if(lookahead != expected) {
        cout << "Error type (Syntactical) at line xx.";
    }
}

void Syntax::get_token() {

}

void Syntax::parse_Program() {//1.2.1
    parse_ExtDefList();
}

void Syntax::parse_ExtDefList() {//1.2.2
    parse_Def();
    parse_ExtDefList();
}

void Syntax::parse_ExtDef() {

}

void Syntax::parse_Specifier() {//1.3.1
    match_token("TYPE");
}

void Syntax::parse_VarDec() {//1.4.1
    match_token("ID");
}

void Syntax::parse_FunDec() {//1.4.2
    match_token("ID");
    match_token("LP");
    match_token("RP");
}

void Syntax::parse_Compst() {//1.5.1
    match_token("LC");
    parse_DefList();
    parse_StmtList();
    match_token("RC");
}

void Syntax::parse_StmtList() {

}

void Syntax::parse_Stmt() {

}

void Syntax::parse_DefList() {

}

void Syntax::parse_Def() {

}

void Syntax::parse_DecList() {

}

void Syntax::parse_Dec() {

}

void Syntax::parse_Exp() {//1.7.1
    
}