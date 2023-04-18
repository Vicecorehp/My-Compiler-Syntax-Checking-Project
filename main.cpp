#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <ios>
#include <vector>
#include "Syntax.h"
#include "Word_info.h"

using std::ofstream;
using std::vector;
using std::cout;
using std::endl;
using std::ios;
using std::map;

string type[] = { "int", "float" };
string key_words[] = { "struct", "return", "if", "else", "while" };
map<string, string> string_cast = { {"struct", "STRUCT"}, {"return", "RETURN"},
                                    {"if", "IF"}, {"else", "ELSE"}, {"while", "WHILE"} };
map<char, string> char_cast = { {'(', "LP"},   {')', "RP"},    {'{', "LC"},    {'}', "RC"},
                                {'[', "LB"},   {']', "RB"},    {',', "COMMA"}, {';', "SEMI"},
                                {'+', "PLUS"}, {'-', "MINUS"}, {'*', "STAR"},  {'/', "DIV"},
                                {'.', "DOT"},  {'!', "NOT"},   {'=', "ASSIGNOP"} };

vector<Word_info*> word_repo;
bool is_word_error = false;

void correct_line_write(int line, const string &main_key, const string &word);
void words_analysis(string &to_scan);
// ll(1) to learn
// Reconstruct everything when necessary
// Find a way to store the connection among the words
int main(int argc, char **argv) {
    string input_src;
    for (char ch = '\0'; (ch = getchar()) != EOF; ) {
        input_src.push_back(ch);
    }
    words_analysis(input_src);
    Syntax *syntax = new Syntax(word_repo);
    syntax->syntax_analysis();
    return 0;
}

void correct_line_write(int line, const string &main_key, const string &word) {
    Word_info *word_info = new Word_info(line, main_key, word);
    word_repo.push_back(word_info);
}

void words_analysis(string &to_scan) {
    int line = 1;
    int p = 0;
    char ch = '\0';
    int fg = 0;
    bool is_float = false;
    bool is_matched = false;
    string word = "";
    //读取第一个非空字符
    do {
        ch = to_scan[p++];
        if (ch == '\n')
            line++;
    } while (ch == ' ' || ch == '\n' || ch == '\t');

    while (ch != '\0') {
        while (ch == ' ' || ch == '\n' || ch == '\t') {
            if (ch == '\n') {
                ++line;
            }
            ch = to_scan[p++];
        }

        //处理保留字和字母开头的变量
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch == '_')) {
            fg = 0;
            word += ch;
            ch = to_scan[p++];
            while ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') ||
                (ch >= '0' && ch <= '9') || (ch == '_')) {
                word += ch;
                ch = to_scan[p++];
            }
            //识别是否为int或float
            for (int i = 0; i <= 2; ++i) {
                if (i == 2) {
                    ++fg;
                    break;
                }
                if (word == type[i]) {
                    correct_line_write(line, "TYPE", word);
                    word.clear();
                    break;
                }
            }

            //识别是否为关键词
            if (fg == 1) {
                for (int i = 0; i <= 5; ++i) {
                    if (i == 5) {
                        ++fg;
                        break;
                    }
                    if (word == key_words[i]) {
                        correct_line_write(line, string_cast[word], word);
                        word.clear();
                        break;
                    }
                }
            }
            //普通变量名称
            if (fg == 2) {
                correct_line_write(line, "ID", word);
                word.clear();
            }
            is_matched = true;
        }

        //处理数字
        if (ch >= '0' && ch <= '9') {
            is_float = false;
            if (ch == '0' && to_scan[p] != '.') {
                word += ch;
                ch = to_scan[p++];
                if (ch == 'x' || ch == 'X') {
                    word += ch;
                    ch = to_scan[p++];
                    while ((ch >= 'A' && ch <= 'F') || (ch >= 'a' && ch <= 'f') || (ch >= '0' && ch <= '9')) {
                        word += ch;
                        ch = to_scan[p++];
                    }
                } else if (ch >= '0' && ch <= '7') {
                    word += ch;
                    ch = to_scan[p++];
                    while ((ch >= '0' && ch <= '7')) {
                        word += ch;
                        ch = to_scan[p++];
                    }
                }
                correct_line_write(line, "INT", word);
                word.clear();
            } else {
                word += ch;
                ch = to_scan[p++];
                while ((ch >= '0' && ch <= '9') || (ch == '.') || (ch == 'e') ||
                    (ch == 'E')) {
                    if (ch == '.') {
                        is_float = true;
                        word += ch;
                        ch = to_scan[p++];
                        while ((ch >= '0' && ch <= '9') || (ch == 'e') || (ch == 'E') ||
                               (ch == '-') || (ch == '+')){
                            word += ch;
                            ch = to_scan[p++];
                        }
                        break;
                    } 
                    if (ch == 'e' || ch == 'E') {
                        is_float = true;
                        word += ch;
                        ch = to_scan[p++];
                        while ((ch >= '0' && ch <= '9') || (ch == '-') || ch == '+') {
                            word += ch;
                            ch = to_scan[p++];
                        }
                        break;
                    }
                    word += ch;
                    ch = to_scan[p++];
                }
                correct_line_write(line, (is_float ? "FLOAT" : "INT"), word);
                word.clear();
            }
            is_matched = true;
        }

        //处理符号
        switch (ch) {
        case '/': {
            if (to_scan[p] == '/') {
                while (true) {
                    ch = to_scan[p++];
                    if (ch == '\n' || ch == '\0') {
                        ch = to_scan[p++];
                        ++line;
                        break;
                    }
                }
            } else if (to_scan[p++] == '*') {
                char next_ch = '\0';
                int tmp;
                while (true) {
                    tmp = (p++);
                    ch = to_scan[tmp];
                    next_ch = to_scan[tmp+1];
                    if (ch == '\n') {
                        ++line;
                    }
                    if ((ch == '*' && next_ch == '/') || (next_ch == '\0')) {
                        ch = to_scan[tmp+1];
                        break;
                    }
                }
            } else {
                word += ch;
                correct_line_write(line, char_cast[ch], word);
                word.clear();
                ch = to_scan[p++];
            }
            is_matched = true;
            break;
        }
        case '=': case '<': case '>': case '!': {
            if (to_scan[p] == '=') {
                word += ch;
                ch = to_scan[p++];
                word += ch;
                ch = to_scan[p++];
                correct_line_write(line, "RELOP", word);
                word.clear();
                is_matched = true;
                break;
            } 
            if(ch == '<' || ch == '>') {
                word += ch;
                ch = to_scan[p++];
                correct_line_write(line, "RELOP", word);
                word.clear();
                break;
            }
            word += ch;
            correct_line_write(line, char_cast[ch], word);
            word.clear();
            ch = to_scan[p++];
            is_matched = true;
            break;
        }
        case '&': case '|': {
            if (to_scan[p] == '&' || to_scan[p] == '|') {
                word += ch;
                ch = to_scan[p++];
                word += ch;
                ch = to_scan[p++];
                correct_line_write(line, (to_scan[p-2] == '&') ? "AND" : "OR", word);
                word.clear();
                is_matched = true;
            }  
            break;
        }
        case '.': {
            int p_bak = p;
            int e_cnt = 0;
            bool is_num = false;
            word += ch;
            ch = to_scan[p++];
            is_num = (ch >= '0' && ch <= '9');
            if (!is_num) {
                correct_line_write(line, char_cast['.'], word);
                word.clear();
                break;
            }
            while ((ch >= '0' && ch <= '9') || (ch == 'e') || (ch == 'E') ||
                  (ch == '-') || (ch == '+')) {
                if (ch == 'e' || ch == 'E') {
                    e_cnt++;
                }
                word += ch;
                ch = to_scan[p++];
            }
            if (e_cnt) {
                correct_line_write(line, "FLOAT", word);
                word.clear();
                break;
            } else {
                word.clear();
                word += '.';
                correct_line_write(line, char_cast['.'], word);
                p = p_bak;
                ch = to_scan[p];
                word.clear();
            }
            is_matched = true;
            break;
        }
        case '+': case '-': {
            if (to_scan[p] == '+' || to_scan[p] == '-') {
                word += ch;
                ch = to_scan[p++];
                word += ch;
                ch = to_scan[p++];
                correct_line_write(line, (to_scan[p-2] == '+') ? "INC" : "DEC", word);
                word.clear();
                break;
            } else {
                word += ch;
                correct_line_write(line, char_cast[ch], word);
                word.clear();
                ch = to_scan[p++];
            }
            is_matched = true;
            break;
        }
        case '*': case ',': case ';': case '(': case ')': 
        case '[': case ']': case '{': case '}': {
            word += ch;
            correct_line_write(line, char_cast[ch], word);
            word.clear();
            ch = to_scan[p++];
            is_matched = true;
            break;
        }
        case ' ': case '\t':case '\n': {
            break;
        }
        default: {
            if (!is_matched) {
                if (p > int(to_scan.length())) {
                    break;
                }
                is_word_error = true;
                ch = to_scan[p++];
            }
            break;
        }
        }
        is_matched = false;
    }
}