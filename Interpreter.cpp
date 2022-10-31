//
// Created by Dallin on 10/31/22.
//

#include "Interpreter.h"

void Interpreter::interpretSchemes() {
    for (Predicate scheme : program.getSchemes()) {
        vector<string> header;
        for (Parameter parameter : scheme.getParameters()) {
            header.push_back(parameter.getActualValue());
        }
        Relation* relation = new Relation(scheme.getID(), header);
        data.addTable(scheme.getID(), relation);
    }
}

void Interpreter::interpretFacts() {

}

void Interpreter::interpretRules() {

}

void Interpreter::interpertQueries() {

}
