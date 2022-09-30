//
// Created by Dallin on 9/30/22.
//

#include "Rule.h"

void Rule::setHeadPredicate(Predicate input) {
    headPredicate = input;
}

void Rule::addBodyPredicate(Predicate input) {
    bodyPredicates.push_back(input);
}
