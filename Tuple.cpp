//
// Created by Dallin on 10/26/22.
//

#include "Tuple.h"

string Tuple::toString(vector<string> header) const {
    stringstream out;
    out << "  ";
    //POTENTIAL BUG TO FIX - SEE RULE.H for call
    //Start should be 1 if you pass in a rule Head predicate, 0 if its just the table headers
    for (unsigned int i = 0; i < header.size(); i++) {
        out << header.at(i) << "=";
        out << data.at(i);
        if (i != header.size() - 1) {
            out << ", ";
        }
    }
    return out.str();
}
