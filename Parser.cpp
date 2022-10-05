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
        throw tokens.at(0);
    } //ERROR, failed parse
}

DatalogProgram Parser::parse() {
    //This section removes all the comments
    for(unsigned int index = 0; index < tokens.size(); index++) {
        if(tokens.at(index)->getType() == TokenType::COMMENT) {
            tokens.erase(tokens.begin() + index);
            index = 0;
        }
    }
    try {
        parseDatalogProgram();
    } catch (Token* invalidToken) {
        cout << "Failure!" << endl;
        cout << "  " << invalidToken->toString() << endl;
        return program;
    }
    cout << "Success!" << endl;
    program.programSuccess();
    return program;
}

void Parser::parseDatalogProgram() {
    matchToCurrentToken(TokenType::SCHEMES);
    matchToCurrentToken(TokenType::COLON);
    program.addScheme(parseScheme());
    parseSchemeList();
    matchToCurrentToken(TokenType::FACTS);
    matchToCurrentToken(TokenType::COLON);
    parseFactList();
    matchToCurrentToken(TokenType::RULES);
    matchToCurrentToken(TokenType::COLON);
    parseRuleList();
    matchToCurrentToken(TokenType::QUERIES);
    matchToCurrentToken(TokenType::COLON);
    program.addQuery(parseQuery());
    parseQueryList();
    matchToCurrentToken(TokenType::EOF_TYPE);

    return;
}

//production -> scheme schemeList | lambda
void Parser::parseSchemeList() {
    if(tokens.at(0)->getType() == TokenType::ID) {
        program.addScheme(parseScheme());
        parseSchemeList();
    }
    return;
}

//production->ID LEFT_PAREN ID idList RIGHT_PAREN
Predicate Parser::parseScheme() {
    vector<Parameter> currentList;
    string schemeID = tokens.at(0)->getActualValue();
    matchToCurrentToken(TokenType::ID);
    matchToCurrentToken(TokenType::LEFT_PAREN);
    currentList.push_back( Parameter(tokens.at(0)->getActualValue()) );
    matchToCurrentToken(TokenType::ID);
    vector<string> stringList = parseIDList();
    for (unsigned int i = 0; i < stringList.size(); i++) {
        currentList.push_back( Parameter(stringList.at(i)) );
    }
    matchToCurrentToken(TokenType::RIGHT_PAREN);
    return Predicate(currentList, schemeID);
}

//production->COMMA ID idList | lambda
vector<string> Parser::parseIDList() {
    vector<string> currentList;
    if(tokens.at(0)->getType() == TokenType::COMMA) {
        matchToCurrentToken(TokenType::COMMA);
        currentList.push_back(tokens.at(0)->getActualValue());
        matchToCurrentToken(TokenType::ID);
        vector<string> listToAddOn = parseIDList();
        currentList.insert(currentList.end(),listToAddOn.begin(), listToAddOn.end());
    }
    return currentList;
}

//production -> fact factList | lambda
void Parser::parseFactList() {
    if(tokens.at(0)->getType() == TokenType::ID) {
        program.addFact(parseFact());
        parseFactList();
    }
    return;
}

//production -> ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
Predicate Parser::parseFact() {
    vector<Parameter> parameterList;
    string predicateID = tokens.at(0)->getActualValue();
    matchToCurrentToken(TokenType::ID);
    matchToCurrentToken(TokenType::LEFT_PAREN);
    parameterList.push_back( Parameter(tokens.at(0)->getActualValue()) );
    matchToCurrentToken(TokenType::STRING);
    vector<Parameter> listToAddOn = parseStringList();
    parameterList.insert(parameterList.end(),listToAddOn.begin(), listToAddOn.end());
    matchToCurrentToken(TokenType::RIGHT_PAREN);
    matchToCurrentToken(TokenType::PERIOD);
    return Predicate(parameterList, predicateID);
}

//production -> COMMA STRING stringList | lambda
vector<Parameter> Parser::parseStringList() {
    vector<Parameter> currentList;
    if(tokens.at(0)->getType() == TokenType::COMMA) {
        matchToCurrentToken(TokenType::COMMA);
        Parameter newParameter = Parameter(tokens.at(0)->getActualValue());
        currentList.push_back(newParameter);
        matchToCurrentToken(TokenType::STRING);
        vector<Parameter> listToAddOn = parseStringList();
        currentList.insert(currentList.end(),listToAddOn.begin(), listToAddOn.end());
    }
    return currentList;
}

//production -> rule ruleList | lambda
void Parser::parseRuleList() {
    if(tokens.at(0)->getType() == TokenType::ID) {
        program.addRule(parseRule());
        parseRuleList();
    }
    return;
}

//production -> headPredicate COLON_DASH predicate predicateList PERIOD
Rule Parser::parseRule() {
    vector<string> headPredicate = parseHeadPredicate();
    vector<Predicate> bodyPredicates;
    matchToCurrentToken(TokenType::COLON_DASH);
    bodyPredicates.push_back(parsePredicate());
    vector<Predicate> listToAddOn = parsePredicateList();
    bodyPredicates.insert(bodyPredicates.end(),listToAddOn.begin(), listToAddOn.end());
    matchToCurrentToken(TokenType::PERIOD);
    return Rule(headPredicate, bodyPredicates);
}

//production -> ID LEFT_PAREN ID idList RIGHT_PAREN
vector<string> Parser::parseHeadPredicate() {
    vector<string> currentList;
    currentList.push_back(tokens.at(0)->getActualValue());
    matchToCurrentToken(TokenType::ID);
    matchToCurrentToken(TokenType::LEFT_PAREN);
    currentList.push_back(tokens.at(0)->getActualValue());
    matchToCurrentToken(TokenType::ID);
    vector<string> listToAddOn = parseIDList();
    currentList.insert(currentList.end(),listToAddOn.begin(), listToAddOn.end());
    matchToCurrentToken(TokenType::RIGHT_PAREN);
    return currentList;
}

//production -> ID LEFT_PAREN parameter parameterList RIGHT_PAREN
Predicate Parser::parsePredicate() {
    vector<Parameter> parameterList;
    string predicateID = tokens.at(0)->getActualValue();
    matchToCurrentToken(TokenType::ID);
    matchToCurrentToken(TokenType::LEFT_PAREN);
    parameterList.push_back(parseParameter());
    vector<Parameter> listFromRecursion = parseParameterList();
    parameterList.insert(parameterList.end(), listFromRecursion.begin(), listFromRecursion.end());
    matchToCurrentToken(TokenType::RIGHT_PAREN);

    /* ///DEBUGGING STUFF/////
    cout << "Predicate list of parameters:" << endl;
    for (auto Parameter : parameterList) {
        cout << Parameter.getActualValue() << " --- ";
    }
    cout << endl;
    ////////////////////////// */

    return Predicate(parameterList, predicateID);
}

//production -> COMMA predicate predicateList | lambda
vector<Predicate> Parser::parsePredicateList() {
    vector<Predicate> currentList;
    if(tokens.at(0)->getType() == TokenType::COMMA) {
        matchToCurrentToken(TokenType::COMMA);
        currentList.push_back(parsePredicate());
        vector<Predicate> listToAddOn = parsePredicateList();
        currentList.insert(currentList.end(),listToAddOn.begin(), listToAddOn.end());
    }
    return currentList;
}

//production -> STRING | ID
Parameter Parser::parseParameter() {
    Parameter returnValue = Parameter(tokens.at(0)->getActualValue());
    if(tokens.at(0)->getType() == TokenType::STRING) {
        matchToCurrentToken(TokenType::STRING);
    } else {
        matchToCurrentToken(TokenType::ID);
        //If it should fail on this part, ID will throw for us
    }
    return returnValue;
}

//production -> COMMA parameter parameterList | lambda
vector<Parameter> Parser::parseParameterList() {
    vector<Parameter> currentList;
    if(tokens.at(0)->getType() == TokenType::COMMA) {
        matchToCurrentToken(TokenType::COMMA);
        currentList.push_back(parseParameter());
        vector<Parameter> listToAddOn = parseParameterList();
        currentList.insert(currentList.end(),listToAddOn.begin(), listToAddOn.end());
    }
    return currentList;
}

//production -> predicate Q_MARK
Predicate Parser::parseQuery() {
    Predicate returnValue = parsePredicate();
    matchToCurrentToken(TokenType::Q_MARK);
    return returnValue;
}

//production -> query queryList | lambda
void Parser::parseQueryList() {
    if(tokens.at(0)->getType() == TokenType::ID) {
        program.addQuery(parseQuery());
        parseQueryList();
    }
    return;
}


