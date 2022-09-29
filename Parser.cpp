//
// Created by Dallin on 9/28/22.
//

#include "Parser.h"

void Parser::syntaxError(Token *invalidToken) {
    string errorMessage = "FAILURE! \n" + invalidToken->toString();
    cout << "throwing syntax error" << endl;
    throw errorMessage;
}

//called for every terminal
void Parser::matchToCurrentToken(TokenType currentType) {
    if (currentType == tokens.at(0)->getType()) {
        tokens.erase(tokens.begin()); //pop
        return;
    }
    else {
        cout << "Oops I did it again: " << tokens.at(0)->toString() << endl;
        throw tokens.at(0);
    } //ERROR, failed parse
}

void Parser::parse() {
    //This section removes all the comments
    for(unsigned int index = 0; index < tokens.size(); index++) {
        if(tokens.at(index)->getType() == TokenType::COMMENT) {
            tokens.erase(tokens.begin() + index);
            index = 0;
        }
    }
    parseDatalogProgram();
}

void Parser::parseDatalogProgram() {
    matchToCurrentToken(TokenType::SCHEMES);
    matchToCurrentToken(TokenType::COLON);
    parseScheme();
    parseSchemeList();
    matchToCurrentToken(TokenType::FACTS);
    matchToCurrentToken(TokenType::COLON);
    parseFactList();
    cout << "success" << endl;
}

//production -> scheme schemeList | lambda
void Parser::parseSchemeList() {
    if(tokens.at(0)->getType() == TokenType::ID) {
        parseScheme();
        parseSchemeList();
    }
    return;
}

//production->ID LEFT_PAREN ID idList RIGHT_PAREN
void Parser::parseScheme() {
    matchToCurrentToken(TokenType::ID);
    matchToCurrentToken(TokenType::LEFT_PAREN);
    matchToCurrentToken(TokenType::ID);
    parseIDList();
    matchToCurrentToken(TokenType::RIGHT_PAREN);
}

//production->COMMA ID idList | lambda
void Parser::parseIDList() {
    if(tokens.at(0)->getType() == TokenType::COMMA) {
        matchToCurrentToken(TokenType::COMMA);
        matchToCurrentToken(TokenType::ID);
        parseIDList();
    }
    return;
}

//production -> fact factList | lambda
void Parser::parseFactList() {
    if(tokens.at(0)->getType() == TokenType::FACTS) {
        parseFact();
        parseFactList();
    }
    return;
}

//production -> ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
void Parser::parseFact() {
    matchToCurrentToken(TokenType::ID);
    matchToCurrentToken(TokenType::LEFT_PAREN);
    matchToCurrentToken(TokenType::STRING);
    parseStringList();
    matchToCurrentToken(TokenType::RIGHT_PAREN);
    matchToCurrentToken(TokenType::PERIOD);
}

//production -> COMMA STRING stringList | lambda
void Parser::parseStringList() {
    if(tokens.at(0)->getType() == TokenType::COMMA) {
        matchToCurrentToken(TokenType::COMMA);
        matchToCurrentToken(TokenType::STRING);
        parseStringList();
    }
    return;
}




