//
// Created by Dallin on 10/26/22.
//

#include "Tuple.h"

string Tuple::toSting() {
    stringstream out;
    out << "(";
    vector<string>::iterator itr;
    for(itr = data.begin(); itr != data.end(); itr++){
        out << *itr;
        if (itr != data.end()) {
            out << ",";
        }
    }
    out << ")";
    return out.str();
}
