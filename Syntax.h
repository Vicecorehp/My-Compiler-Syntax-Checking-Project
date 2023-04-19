#ifndef __SYNTAX_H__
#define __SYNTAX_H__

#include <string>
#include <vector>
#include "Word_info.h"
using std::string;
using std::vector;
class Syntax {
public:
    Syntax(vector<Word_info*> &input);
    void syntax_analysis();
private:
    int idx;
    bool syntax_error;
    Word_info *lookahead;
    vector<Word_info*> to_scan;
    void get_token();
    void print_error();
    void match_token(const string &token);
    void parse_Program();
    void parse_ExtDefList();
    void parse_ExtDef();
    void parse_Specifier();
    void parse_VarDec();
    void parse_FunDec();
    void parse_Compst();
    void parse_StmtList();
    void parse_Stmt();
    void parse_DefList();
    void parse_Def();
    void parse_DecList();
    void parse_Dec();
    void parse_Exp();
};

#endif