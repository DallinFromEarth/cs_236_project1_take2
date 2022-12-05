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
#include "Graph.h"

using namespace std;

class Interpreter {
private:
    Database data;
    DatalogProgram program;

    string answers;

    //int passThroughs;

    Graph forwardGraph;
    Graph reverseGraph;

public:
    Interpreter(DatalogProgram input) { program = input; passThroughs = 0; }

    void interpretSchemes();
    void interpretFacts();
    void interpretRules();
    void interpertQueries();

    int fixPointAlgorithm(set<int> component);

    Relation interpretPredicate(Predicate table);

    void run();
    string getAnswers() { return answers; }

    string getDataBaseString() { return data.toString(); }

    Relation join(Relation table1, Relation table2, string newName);
    Relation unification(Relation table1, Relation table2);

    vector<pair<int,int>> getCommonHeaders(Relation table1, Relation table2);
    vector<string> mergeHeaders(Relation table1, Relation table2);

    bool isJoinable(Tuple, Tuple, vector<pair<int,int>>);
    Tuple combineTuples(Tuple, Tuple, vector<pair<int,int>>);

    string newTupleString(Relation oldRelation, Relation* newRelation);

    void interpretAndUpdate(const Rule rule);

    vector<set<int>> findDependencies();

    void createGraphs();

    vector<Rule> findSelectedRules(set<int> rulesToFind);
};


#endif //PROJECT_1_INTERPRETER_H
