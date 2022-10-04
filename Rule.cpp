//
// Created by Dallin on 10/3/22.
//

#include "Rule.h"

string Rule::toString() {
    stringstream out;
    out << headPredicate.at(0) << "(";
    for (int i = 1; i < headPredicate.size(); i++) {
        out << headPredicate.at(i);
        if (i != headPredicate.size() - 1) { out << ","; }
    }
    out << ") :- ";
    for (int i = 0; i < bodyPredicates.size(); i++) {
        out << bodyPredicates.at(0).toString();
        if (i != bodyPredicates.size() - 1) { out << ","; }
    }
    out << ".";
    return out.str();
}
