//
// Created by Dallin on 10/26/22.
//

#ifndef PROJECT_1_RELATION_H
#define PROJECT_1_RELATION_H

#include "Tuple.h"
#include "RelationHeader.h"
#include <iostream>

using namespace std;

class Relation {
private:
    string name;
    RelationHeader header;
    set<Tuple> table;

public:
    Relation(string inputName, vector<string> inputHeader) {
        name = inputName;
        header.addHeader(inputHeader);
    }

    Relation(string inputName, RelationHeader inputHeader) {
        name = inputName;
        header = inputHeader;
    }

    Relation(const Relation& original) {
        name = original.name;
        header = original.header;
        table = original.table;
    }

    string toString();
    string headerToString() { return header.toString(); }
    void addTuple(Tuple input){ table.insert(input); }
    set<Tuple> getTable() { return table; }
    void setTable(set<Tuple> newTable) { table = newTable; }
    string getName() { return name; }
    RelationHeader getHeader() { return header; }

    Relation select1(int colIndex, string value);
    Relation select2(int colIndex1, int colIndex2);
    Relation project(vector<int> columnsToProject);
    Relation rename(vector<string> newColumnNames);
};


#endif //PROJECT_1_RELATION_H
