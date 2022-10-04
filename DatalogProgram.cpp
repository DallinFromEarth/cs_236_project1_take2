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

string DatalogProgram::rulesToString() {
    stringstream out;
    out << "Rules(" << rules.size() << "):" << endl;
    for (int i = 0; i < rules.size(); i++) {
        out << "  " << rules.at(i).toString() << endl;
    }
    return out.str();
}
