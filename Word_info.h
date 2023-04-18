#ifndef __WORD_INFO_H__
#define __WORD_INFO_H__
#include <string>
#include <iostream>

using std::string;

class Word_info {
public:
    Word_info(int line, string type, string word) {
        this->line = line;
        this->type = type;
        this->word = word;
    }
    int line;
    string type;
    string word;
};
#endif
