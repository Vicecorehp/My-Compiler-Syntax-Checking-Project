#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Word_info.h"
#include "Syntax.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;

Syntax::Syntax(vector<Word_info*> &input) {
    this->to_scan = input;
    this->idx = 0;
    this->lookahead = to_scan[0];
    this->syntax_error = false;
    Word_info *end_sign = new Word_info(-1, "$", "$");
    this->to_scan.push_back(end_sign);
}

void Syntax::print_error() {
    this->syntax_error = true;
    int error_line = lookahead->line;
    if (lookahead->line != to_scan[idx-1]->line) {
        error_line = to_scan[idx-1]->line;
    }
    cout << "Error type (Syntactical) at line "
         << error_line << "." << endl;
    exit(0);
}

void Syntax::syntax_analysis() {
    parse_Program();
    if (!syntax_error) {
        cout << "Syntactical Correct." << endl;
    }
}

void Syntax::match_token(const string &expected) {
    if (expected == "$") {
        return;
    }
    if (lookahead->type != expected) {
        print_error();
    } else {
        get_token();
    }
}

void Syntax::get_token() {
    lookahead = to_scan[++idx];
}

void Syntax::parse_Program() {//1.2.1
    parse_ExtDefList();
}

void Syntax::parse_ExtDefList() {//1.2.2
    if (lookahead->type == "$") {
        match_token("$");
    } else if (lookahead->type == "TYPE") {
        parse_ExtDef();
        parse_ExtDefList();
    } else {
        print_error();
    }
}

void Syntax::parse_ExtDef() {//1.2.3
    parse_Specifier();
    parse_FunDec();
    parse_Compst();
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

void Syntax::parse_StmtList() {//1.5.2
    if (lookahead->type == "$") {
        match_token("$");
    } else if (lookahead->type == "LP" || lookahead->type == "NOT" ||
               lookahead->type == "ID" || lookahead->type == "RETURN") {
        parse_Stmt();
        parse_StmtList();
    } else if (lookahead->type == "RC") {
        //do nothing
    } else {
        print_error();
    }
}

void Syntax::parse_Stmt() {//1.5.3
    if (lookahead->type == "$") {
        match_token("$");
    } else if (lookahead->type == "LP" || lookahead->type == "NOT" ||
               lookahead->type == "ID") {
        parse_Exp();
        match_token("SEMI");
    } else if (lookahead->type == "RETURN") {
        match_token("RETURN");
        parse_Exp();
        match_token("SEMI");
    } else {
        print_error();
    }
}

void Syntax::parse_DefList() {//1.6.1
    if (lookahead->type == "$") {
        match_token("$");
    } else if (lookahead->type == "TYPE") {
        parse_Def();
        parse_DefList();
    } else if (lookahead->type == "LP" || lookahead->type == "NOT" ||
               lookahead->type == "ID" || lookahead->type == "RETURN" || 
               lookahead->type == "RC") {
        //do nothing
    } else {
        print_error();
    }
}

void Syntax::parse_Def() {//1.6.2
    parse_Specifier();
    parse_DecList();
    match_token("SEMI");
}

void Syntax::parse_DecList() {//1.6.3
    parse_Dec();
}

void Syntax::parse_Dec() {//1.6.4
    parse_VarDec();
    match_token("ASSIGNOP");
    parse_Exp();
}

void Syntax::parse_Exp() {//1.7.1
    if (lookahead->type == "$") {
        match_token("$");
    } else if (lookahead->type == "LP") {
        match_token("LP");
        parse_Exp();
        match_token("OP");
    } else if (lookahead->type == "NOT") {
        match_token("NOT");
        parse_Exp();
    } else if (lookahead->type == "INT") {
        match_token("INT");
    } else if (lookahead->type == "FLOAT") {
        match_token("FLOAT");
    } else if (lookahead->type == "ID") {
        match_token("ID");
    } else {
        print_error();
    }
}