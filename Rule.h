//
// Created by Dallin on 9/30/22.
//

#ifndef PROJECT_1_RULE_H
#define PROJECT_1_RULE_H
#include "Predicate.h"
#include "Tuple.h"
#include <sstream>
#include <iostream>

class Rule {
private:
    vector<string> headPredicate;
    vector<Predicate> bodyPredicates;
    bool hasChanged;
    string evaluations;

public:
    Rule(vector<string> head, vector<Predicate> body) {
        headPredicate = head;
        bodyPredicates = body;
        hasChanged = false;
        evaluations = "";
    }

    string toString();

    vector<Predicate> getBodyPredicates() { return bodyPredicates; }
    vector<string> getHeadPredicate() { return headPredicate; }
};


#endif //PROJECT_1_RULE_H
