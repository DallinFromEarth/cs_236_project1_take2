//
// Created by Dallin on 10/27/22.
//

#ifndef PROJECT_1_DATABASE_H
#define PROJECT_1_DATABASE_H

#include <map>
#include <sstream>
#include <iostream>
#include <vector>
#include "Relation.h"

class Database {
private:
    map<string, Relation*> data;

public:
    Database() {}

    void addTable(string key, Relation* table) {
        data[key] = table;
    }

    Relation* getRelation(string relationName) {
        return data.at(relationName);
    }

    Relation getRelationCopy(string relationName) {
        Relation* old = getRelation(relationName);
        Relation steve = Relation(old->getName(), old->getHeader());
        steve.setTable(old->getTable());
        return steve;
    }
};

#endif //PROJECT_1_DATABASE_H
