//
// Created by Dallin on 9/28/22.
//

#ifndef PROJECT_1_PARSER_H
#define PROJECT_1_PARSER_H

#include "token.h"
#include <vector>
#include <string>


class Parser {
private:
    vector<Token*> tokens;

public:
    Parser(vector<Token*> inputTokens) { tokens = inputTokens; }
    ~Parser() { }

    void syntaxError(Token* invalidToken);
    void matchToCurrentToken(TokenType);

    void parse();
    void parseDatalogProgram();

};


#endif //PROJECT_1_PARSER_H
