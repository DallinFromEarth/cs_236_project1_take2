//
// Created by Dallin on 10/31/22.
//

#ifndef PROJECT_1_INTERPRETER_H
#define PROJECT_1_INTERPRETER_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>

#include "Database.h"
#include "DatalogProgram.h"

using namespace std;

class Interpreter {
private:
    Database data;
    DatalogProgram program;

    string answers;

public:
    Interpreter(DatalogProgram input) { program = input; }

    void interpretSchemes();
    void interpretFacts();
    void interpretRules();
    void interpertQueries();

    Relation interpretPredicate(Predicate table);

    void run();
    string getAnswers() { return answers; }

    string getDataBaseString() { return data.toString(); }

    Relation join(Relation table) { cout << "single table join"<< endl; return table; }
    Relation join(Relation table1, Relation table2, string newName);

    vector<pair<int,int>> getCommonHeaders(Relation table1, Relation table2);
    vector<string> mergeHeaders(Relation table1, Relation table2);

    bool isJoinable(Tuple, Tuple, vector<pair<int,int>>);
    Tuple combineTuples(Tuple, Tuple, vector<pair<int,int>>);
};


#endif //PROJECT_1_INTERPRETER_H
