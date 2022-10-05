//
// Created by Dallin on 9/30/22.
//

#ifndef PROJECT_1_DATALOGPROGRAM_H
#define PROJECT_1_DATALOGPROGRAM_H

#include "Predicate.h"
#include "Rule.h"
#include "Token.h"
#include <set>
#include <iostream>

class DatalogProgram {
private:
    vector<Rule> rules;
    vector<Predicate> schemes;
    vector<Predicate> facts; //they don't care about your feelings
    vector<Predicate> queries;
    bool validProgram;

public:
    DatalogProgram() { validProgram = false; }

    void addRule(Rule input);
    void addScheme(Predicate input);
    void addFact(Predicate input);
    void addQuery(Predicate input);

    string rulesToString();
    string schemesToString();
    string factsToString();
    string queriesToString();
    string domainToString();
    set<string> getDomain();

    string fullProgramToString();

    bool isProgramValid() { return validProgram; }
    void programSuccess() { validProgram = true; }
};


#endif //PROJECT_1_DATALOGPROGRAM_H
