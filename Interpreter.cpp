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
    for (Predicate fact : program.getFacts()) {
        string id = fact.getID();
        vector<string> stuff;
        for (Parameter parameter : fact.getParameters()) {
            stuff.push_back(parameter.getActualValue());
        }
        data.getRelation(id)->addTuple(stuff);
    }
}

void Interpreter::interpretRules() {

}

void Interpreter::interpertQueries() {

}
