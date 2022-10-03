//
// Created by Dallin on 9/28/22.
//

#ifndef PROJECT_1_PARSER_H
#define PROJECT_1_PARSER_H

#include "Token.h"
#include "Parameter.h"
#include "Predicate.h"
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
    vector<string> parseIDList();
    void parseFactList();
    void parseFact();
    void parseStringList();
    void parseRuleList();
    void parseRule();
    vector<string> parseHeadPredicate();
    Predicate parsePredicate();
    vector<Predicate> parsePredicateList();
    Parameter parseParameter();
    vector<Parameter> parseParameterList();
    void parseQuery();
    void parseQueryList();

public:
    Parser(vector<Token*> inputTokens) { tokens = inputTokens; }
    ~Parser() { }

    void parse();
};


#endif //PROJECT_1_PARSER_H
