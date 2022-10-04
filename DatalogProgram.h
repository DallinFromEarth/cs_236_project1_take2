//
// Created by Dallin on 9/30/22.
//

#ifndef PROJECT_1_DATALOGPROGRAM_H
#define PROJECT_1_DATALOGPROGRAM_H

#include "Predicate.h"
#include "Rule.h"
#include "Token.h"

class DatalogProgram {
private:
    vector<Rule> rules;
    vector<Predicate> schemes;
    vector<Predicate> facts; //they don't care about your feelings
    vector<Predicate> queries;
public:
    DatalogProgram() {}

    void addRule(Rule input);
    void addScheme(Predicate input);
    void addFact(Predicate input);
    void addQuery(Predicate input);

    string rulesToString();
    string schemesToString();
    string factsToString();
    string queriesToString();

};


#endif //PROJECT_1_DATALOGPROGRAM_H
