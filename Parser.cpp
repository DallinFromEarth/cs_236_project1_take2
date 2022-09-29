//
// Created by Dallin on 9/28/22.
//

#include "Parser.h"

void Parser::syntaxError(Token *invalidToken) {
    string errorMessage = "FAILURE! \n" + invalidToken->toString();
    throw errorMessage;
}

void Parser::matchToCurrentToken(TokenType currentType) {
    if (currentType == tokens.at(0)->getType()) {

    }
}

void Parser::parse() {
    parseDatalogProgram();
}

void Parser::parseDatalogProgram() {

}


