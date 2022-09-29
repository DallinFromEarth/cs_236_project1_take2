//
// Created by Dallin on 9/28/22.
//

#ifndef PROJECT_1_PARSER_H
#define PROJECT_1_PARSER_H

#include "token.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;


class Parser {
private:
    vector<Token*> tokens;

    void syntaxError(Token* invalidToken);
    void matchToCurrentToken(TokenType);

    void parseDatalogProgram();
    void parseSchemeList();
    void parseScheme();
    void parseIDList();
    void parseFactList();
    void parseFact();
    void parseStringList();

public:
    Parser(vector<Token*> inputTokens) { tokens = inputTokens; }
    ~Parser() { }

    void parse();

};


#endif //PROJECT_1_PARSER_H
