//
// Created by Dallin on 9/30/22.
//

#ifndef PROJECT_1_RULE_H
#define PROJECT_1_RULE_H
#include "Predicate.h"

class Rule {
private:
    Predicate headPredicate;
    vector<Predicate> bodyPredicates;
public:
    Rule();

    void setHeadPredicate(Predicate input);
    void addBodyPredicate(Predicate input);
};


#endif //PROJECT_1_RULE_H
