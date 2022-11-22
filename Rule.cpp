//
// Created by Dallin on 10/3/22.
//

#include "Rule.h"

string Rule::toString() const {
    stringstream out;
    out << headPredicate.at(0) << "(";
    for (unsigned int i = 1; i < headPredicate.size(); i++) {
        out << headPredicate.at(i);
        if (i != headPredicate.size() - 1) { out << ","; }
    }
    out << ") :- ";
    for (unsigned int i = 0; i < bodyPredicates.size(); i++) {
        out << bodyPredicates.at(i).toString();
        if (i != bodyPredicates.size() - 1) { out << ","; }
    }
    out << ".";
    return out.str();
}
