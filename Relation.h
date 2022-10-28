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

    string toString() {
        stringstream out;
        for (Tuple t : table) {
            for (unsigned int i = 0; i < header.numOfCol(); i++) {
                out << header.getHeaderAtCol(i) << "=";
                out << t.getEntryAtCol(i);
                if (i != header.numOfCol() - 1) {
                    out << ", ";
                }
            }
            out << endl;
        }
        return out.str();
    }
    void addTuple(Tuple input){ table.insert(input); }
};


#endif //PROJECT_1_RELATION_H
