//
// Created by Dallin on 9/30/22.
//

#include "DatalogProgram.h"

void DatalogProgram::addRule(Rule input) {
    rules.push_back(input);
}

void DatalogProgram::addScheme(Predicate input) {
    schemes.push_back(input);
}

void DatalogProgram::addFact(Predicate input) {
    facts.push_back(input);
}

void DatalogProgram::addQuery(Predicate input) {
    queries.push_back(input);
}
