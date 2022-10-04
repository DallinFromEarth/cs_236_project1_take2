//
// Created by Dallin on 9/30/22.
//

#ifndef PROJECT_1_RULE_H
#define PROJECT_1_RULE_H
#include "Predicate.h"

class Rule {
private:
    vector<string> headPredicate;
    vector<Predicate> bodyPredicates;
public:
    Rule(vector<string> head, vector<Predicate> body) {
        headPredicate = head;
        bodyPredicates = body;
    }
};


#endif //PROJECT_1_RULE_H
