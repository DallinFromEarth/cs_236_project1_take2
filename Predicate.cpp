//
// Created by Dallin on 9/30/22.
//

#include "Predicate.h"

string Predicate::toString() {
    stringstream out;
    out << id << "(";
    for (unsigned int i = 0; i < parameters.size(); i++) {
        out << parameters.at(i).getActualValue();
        if (i != parameters.size() - 1) {
            out << ",";
        }
    }
    out << ")";
    return out.str();
}
