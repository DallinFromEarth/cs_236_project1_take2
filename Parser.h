//
// Created by Dallin on 9/28/22.
//

#ifndef PROJECT_1_PARSER_H
#define PROJECT_1_PARSER_H

#include "Token.h"
#include "Parameter.h"
#include "Predicate.h"
#include "Rule.h"
#include "DatalogProgram.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;


class Parser {
private:
    vector<Token*> tokens;
    DatalogProgram program;

    void syntaxError(Token* invalidToken);
    void matchToCurrentToken(TokenType);

    void parseDatalogProgram();
    void parseSchemeList(); //top level, pushes back into program on its own
    Predicate parseScheme();
    vector<string> parseIDList();
    void parseFactList(); //top level, pushes back into program on its own
    Predicate parseFact();
    vector<Parameter> parseStringList(); //treat strings as parameters
    void parseRuleList(); //top level, pushes back into program on its own
    Rule parseRule();
    vector<string> parseHeadPredicate();
    Predicate parsePredicate();
    vector<Predicate> parsePredicateList();
    Parameter parseParameter();
    vector<Parameter> parseParameterList();
    Predicate parseQuery();
    void parseQueryList(); //top level, pushes back into program on its own

public:
    Parser(vector<Token*> inputTokens) { tokens = inputTokens; }
    ~Parser() { }

    DatalogProgram parse();
};


#endif //PROJECT_1_PARSER_H
