#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <map>
#include "Word_info.h"
#include "Syntax.h"

using std::string;
using std::vector;
using std::to_string;
using std::stoi;
using std::cout;
using std::endl;
using std::stoi;

Syntax::Syntax(vector<Word_info *> &input) {
    this->to_scan = input;
    this->idx = 0;
    this->tab_cnt = 0;
    this->lookahead = to_scan[0];
    this->result = "";
    this->to_scan.push_back(new Word_info(1, "$", "$"));
}

void Syntax::print_error() {
    int error_line = lookahead->line;
    if (lookahead->line != to_scan[idx-1]->line) {
        error_line = to_scan[idx-1]->line;
    }
    cout << "Error type (Syntactical) at line " << error_line << "." << endl;
    exit(0);
}

void Syntax::insert_node(const string key, int tab_cnt_arg) {
    string str = "";
    for (int i = 0; i < tab_cnt_arg; ++i) {
        str.push_back('\t');
    }
    str.append(key);
    str.append(" (" + to_string(lookahead->line) + ")\n");
    this->result.append(str);
}

void Syntax::insert_leaf(const string key, int tab_cnt_arg) {
    string str = "";
    for (int i = 0; i < tab_cnt_arg; ++i) {
        str.push_back('\t');
    }
    str.append(key);
    if (key == "ID" || key == "TYPE" || key == "FLOAT") {
        str.append(": " + this->lookahead->word);
    }
    else if (key == "INT") {
        int converted_num = stoi(this->lookahead->word, nullptr, 0);
        str.append(": " + to_string(converted_num));
    }
    str.push_back('\n');
    this->result.append(str);
}

void Syntax::syntax_analysis() {
    parse_Program();
    cout << "Syntactical Correct." << endl;
    cout << this->result;
}

void Syntax::match_token(const string &expected) {
    if (expected == "$") {
        return;
    }
    if (lookahead->type != expected) {
        print_error();
    }
    else {
        insert_leaf(expected, tab_cnt);
        get_token();
    }
}

void Syntax::get_token() {
    lookahead = to_scan[++idx];
}


void Syntax::parse_Program() {//1.2.1
    insert_node("Program", tab_cnt);
    int tab_cnt_bak = tab_cnt++;
    parse_ExtDefList();
    tab_cnt = tab_cnt_bak;
}


void Syntax::parse_ExtDefList() {//1.2.2
    if (lookahead->type == "$") {
        match_token("$");
    }
    else if (lookahead->type == "TYPE") {
        insert_node("ExtDefList", tab_cnt);
        int tab_cnt_bak = tab_cnt++;
        parse_ExtDef();
        parse_ExtDefList();
        tab_cnt = tab_cnt_bak;
    }
    else {
        print_error();
    }
}

void Syntax::parse_ExtDef() {//1.2.3
    insert_node("ExtDef", tab_cnt);
    int tab_cnt_bak = tab_cnt++;
    parse_Specifier();
    parse_FunDec();
    parse_Compst();
    tab_cnt = tab_cnt_bak;
}

void Syntax::parse_Specifier() {//1.3.1
    if (lookahead->type == "TYPE") {
        insert_node("Specifier", tab_cnt);
        int tab_cnt_bak = tab_cnt++;
        match_token("TYPE");
        tab_cnt = tab_cnt_bak;
    }
    else {
        print_error();
    }
}

void Syntax::parse_VarDec() {//1.4.1
    if (lookahead->type == "ID") {
        insert_node("VarDec", tab_cnt);
        int tab_cnt_bak = tab_cnt++;
        match_token("ID");
        tab_cnt = tab_cnt_bak;
    }
    else {
        print_error();
    }
}

void Syntax::parse_FunDec() {//1.4.2
    insert_node("FunDec", tab_cnt);
    int tab_cnt_bak = tab_cnt++;
    match_token("ID");
    match_token("LP");
    match_token("RP");
    tab_cnt = tab_cnt_bak;
}

void Syntax::parse_Compst() {//1.5.1
    insert_node("Compst", tab_cnt);
    int tab_cnt_bak = tab_cnt++;
    match_token("LC");
    parse_DefList();
    parse_StmtList();
    match_token("RC");
    tab_cnt = tab_cnt_bak;
}

void Syntax::parse_StmtList() {//1.5.2
    if (lookahead->type == "$") {
        match_token("$");
    }
    else if (lookahead->type == "LP" || lookahead->type == "NOT" ||
        lookahead->type == "ID" || lookahead->type == "RETURN") {
        insert_node("StmtList", tab_cnt);
        int tab_cnt_bak = tab_cnt++;
        parse_Stmt();
        parse_StmtList();
        tab_cnt = tab_cnt_bak;
    }
    else if (lookahead->type == "RC") {
        //do nothing
    }
    else {
        print_error();
    }
}

void Syntax::parse_Stmt() {//1.5.3
    if (lookahead->type == "$") {
        match_token("$");
    }
    else if (lookahead->type == "LP" || lookahead->type == "NOT" ||
        lookahead->type == "ID") {
        insert_node("Stmt", tab_cnt);
        int tab_cnt_bak = tab_cnt++;
        parse_Exp();
        match_token("SEMI");
        tab_cnt = tab_cnt_bak;
    }
    else if (lookahead->type == "RETURN") {
        insert_node("Stmt", tab_cnt);
        int tab_cnt_bak = tab_cnt++;
        match_token("RETURN");
        parse_Exp();
        match_token("SEMI");
        tab_cnt = tab_cnt_bak;
    }
    else {
        print_error();
    }
}

void Syntax::parse_DefList() {//1.6.1
    if (lookahead->type == "$") {
        match_token("$");
    }
    else if (lookahead->type == "TYPE") {
        insert_node("DefList", tab_cnt);
        int tab_cnt_bak = tab_cnt++;
        parse_Def();
        parse_DefList();
        tab_cnt = tab_cnt_bak;
    }
    else if (lookahead->type == "LP" || lookahead->type == "NOT" ||
        lookahead->type == "ID" || lookahead->type == "RETURN" ||
        lookahead->type == "RC" || lookahead->type == "INT") {
        //do nothing
    }
    else {
        print_error();
    }
}

void Syntax::parse_Def() {//1.6.2
    insert_node("Def", tab_cnt);
    int tab_cnt_bak = tab_cnt++;
    parse_Specifier();
    parse_DecList();
    match_token("SEMI");
    tab_cnt = tab_cnt_bak;
}

void Syntax::parse_DecList() {//1.6.3
    insert_node("DecList", tab_cnt);
    int tab_cnt_bak = tab_cnt++;
    parse_Dec();
    tab_cnt = tab_cnt_bak;
}

void Syntax::parse_Dec() {//1.6.4
    insert_node("Dec", tab_cnt);
    int tab_cnt_bak = tab_cnt++;
    parse_VarDec();
    match_token("ASSIGNOP");
    parse_Exp();
    tab_cnt = tab_cnt_bak;
}

void Syntax::parse_Exp() {//1.7.1
    if (lookahead->type == "$") {
        match_token("$");
    }
    else if (lookahead->type == "LP") {
        insert_node("Exp", tab_cnt);
        int tab_cnt_bak = tab_cnt++;
        match_token("LP");
        parse_Exp();
        match_token("RP");
        tab_cnt = tab_cnt_bak;
    }
    else if (lookahead->type == "NOT") {
        insert_node("Exp", tab_cnt);
        int tab_cnt_bak = tab_cnt++;
        match_token("NOT");
        parse_Exp();
        tab_cnt = tab_cnt_bak;
    }
    else if (lookahead->type == "INT") {
        insert_node("Exp", tab_cnt);
        int tab_cnt_bak = tab_cnt++;
        match_token("INT");
        tab_cnt = tab_cnt_bak;
    }
    else if (lookahead->type == "FLOAT") {
        insert_node("Exp", tab_cnt);
        int tab_cnt_bak = tab_cnt++;
        match_token("FLOAT");
        tab_cnt = tab_cnt_bak;
    }
    else if (lookahead->type == "ID") {
        insert_node("Exp", tab_cnt);
        int tab_cnt_bak = tab_cnt++;
        match_token("ID"); 
        tab_cnt = tab_cnt_bak;
    }
    else {
        print_error();
    }
}