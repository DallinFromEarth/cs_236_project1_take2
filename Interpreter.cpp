//
// Created by Dallin on 10/31/22.
//

#include "Interpreter.h"

void Interpreter::interpretRules() {
    for (const Rule &rule: program.getRules()) {
        interpretAndUpdate(rule);
    }
}

vector<Rule> Interpreter::findSelectedRules(set<int> rulesToFind) {
    vector<Rule> returnVector;
    vector<Rule> programRules = program.getRules();
    for (auto rule : rulesToFind) {
        returnVector.push_back(programRules.at(rule));
    }
    return returnVector;
}

int Interpreter::fixPointAlgorithm(set<int> component) {
    auto ruleList = findSelectedRules(component);
    int passThroughs = 0;

    bool moreToInterpret = true;
    vector<unsigned int> oldTotals;
    vector<unsigned int> newTotals;
    for (const auto& rule : ruleList) {
        oldTotals.push_back( data.getRelation( rule.getHeadPredicate().at(0) )->getNumOfRows() );
    }

    for (const Rule &rule: ruleList) {
        interpretAndUpdate(rule);
    }
    passThroughs++;

    for (const auto& rule : ruleList) {
        newTotals.push_back( data.getRelation( rule.getHeadPredicate().at(0) )->getNumOfRows() );
    }

    if (newTotals == oldTotals) {
        moreToInterpret = false;
    }

    auto steve = *component.begin();
    if ( (!forwardGraph.onlyHasSelfLoop(steve)) && component.size() == 1) {
        return 1;
    }

    oldTotals = newTotals;

    while (moreToInterpret) {
        for (const Rule &rule: ruleList) {
            interpretAndUpdate(rule);
        }
        passThroughs++;

        unsigned int i = 0;
        for (const auto& rule : ruleList) {
            newTotals.at(i) = data.getRelation( rule.getHeadPredicate().at(0) )->getNumOfRows();
            i++;
        }

        if (newTotals == oldTotals) {
            moreToInterpret = false;
        }

        oldTotals = newTotals;
    }
    return passThroughs;
}


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

void Interpreter::interpertQueries() {
    for (Predicate query : program.getQueries()) {
        Relation currentRelation = interpretPredicate(query);

        stringstream out;
        out << query.toString() << "? ";
        if (currentRelation.getNumOfRows()) { //If the table ain't blank jack
            out << "Yes(" << currentRelation.getNumOfRows() << ")" << endl;
            if ( currentRelation.getNumOfCols() > 0) {
                out << currentRelation.toString();
            }
        } else {
            out << "No" << endl;
        }
        answers += out.str();
    }
}

void Interpreter::run() {
    createGraphs();
    interpretSchemes();
    interpretFacts();
    cout << forwardGraph.toStringDependency() << endl;

    auto postorder = reverseGraph.dfsForestPostOrder();
    auto scc = forwardGraph.dfsForestSCC(postorder);


    cout << "Rule Evaluation" << endl;
    for (auto group : scc) {
        cout << "SCC: ";
        int counter = 0;
        for (auto element : group) {
            cout << "R" << element;
            if (counter != group.size() - 1){
                cout << ",";
            }
            counter++;
        }

        cout << endl << fixPointAlgorithm(group) << " passes: ";

        counter = 0;
        for (auto element : group) {
            cout << "R" << element;
            if (counter != group.size() - 1){
                cout << ",";
            }
            counter++;
        }
        cout << endl;
    }
    cout;






    //cout << endl << "Schemes populated after " << passThroughs << " passes through the Rules." << endl;

    cout << endl << "Query Evaluation" << endl;

    interpertQueries();
}

Relation Interpreter::interpretPredicate(Predicate inputPredicate) {
    vector<string> variables;
    vector<unsigned int> index;
    Relation currentRelation = data.getRelationCopy(inputPredicate.getID());

    for (unsigned int i = 0; i < inputPredicate.getParameters().size(); i++) {
        string currentParameter = inputPredicate.getParameters().at(i).getActualValue();

        //if this is a string/constant
        if (currentParameter[0] == '\'') {
            currentRelation = currentRelation.select1(i, currentParameter);
        } else { //is a variable
            //If the parameter is already in the variables vector
            if (find(variables.begin(), variables.end(), currentParameter) != variables.end()) {
                volatile unsigned int firstIndex = -1;
                for (unsigned int j = 0; j < variables.size(); j++) {
                    if (variables.at(j) == currentParameter) { firstIndex = j; break;}
                }
                currentRelation = currentRelation.select2(firstIndex, i);
            }else {
                variables.push_back(currentParameter);
                index.push_back(i);
            }
        }
    }

    currentRelation = currentRelation.project(index);
    currentRelation = currentRelation.rename(variables);

    return currentRelation;
}

Relation Interpreter::join(Relation table1, Relation table2, string newName) {
    vector<pair<int,int>> commonVariables = getCommonHeaders(table1, table2);
    vector<string> mergedHeader = mergeHeaders(table1, table2);
    Relation currentRelation(newName, mergedHeader);

    for (const auto& tuple1 : table1.getTable()) {
        for (const auto& tuple2 : table2.getTable()) {
            bool isJoinable = true;
            for (const auto& duo : commonVariables) {
                if (tuple1.getEntryAtCol(duo.first) != tuple2.getEntryAtCol(duo.second)) {
                    isJoinable = false;
                }
            }
            //isJoinable = true;

            //isJoinable(tuple1, tuple2, commonVariables)
            if (isJoinable) {
                currentRelation.addTuple( combineTuples(tuple1, tuple2, commonVariables) );
            }
        }
    }
    return currentRelation;
}

vector<pair<int, int>> Interpreter::getCommonHeaders(Relation table1, Relation table2) {
    vector<pair<int, int>> returnVector;
    vector<string> header1 = table1.getHeader().data;
    vector<string> header2 = table2.getHeader().data;
    for ( unsigned int i = 0; i < header1.size(); i++) {
        for ( unsigned int j = 0; j < header2.size(); j++ ) {
            if (header1.at(i) == header2.at(j)) {
                returnVector.push_back(pair<int, int>(i,j));
            }
        }
    }
    return returnVector;
}

vector<string> Interpreter::mergeHeaders(Relation table1, Relation table2) {
    vector<string> returnVector = table1.getHeader().data;
    vector<string> header2 = table2.getHeader().data;
    for (string headerInQuestion : header2) {
        if (find(returnVector.begin(), returnVector.end(), headerInQuestion) == returnVector.end()) {
            returnVector.push_back(headerInQuestion);
        }
    }
    return returnVector;
}

bool Interpreter::isJoinable(Tuple tuple1, Tuple tuple2, vector<pair<int, int>> indexes) {
    for (const auto& duo : indexes) {
        if (tuple1.getEntryAtCol(duo.first) != tuple2.getEntryAtCol(duo.second)) {
            return false;
        }
    }
    return true;
}

Tuple Interpreter::combineTuples(Tuple tuple1, Tuple tuple2, vector<pair<int, int>> indexes) {
    int i = 0;
    for (const auto& element : tuple2.data) {
        bool addElement = true;
        for (auto duo : indexes) {
            if (duo.second == i) { addElement = false;}
        }
        if (addElement) {
            tuple1.data.push_back(element);
        }
        i++;
    }
    return tuple1;
}

Relation Interpreter::unification(Relation table1, Relation table2) {
    //for each row in table1
    if (table1.getNumOfRows() == 0) {
        for(const auto& row2 : table2.getTable()) {
            if(table1.addTuple(row2)) {
                cout << row2.toString( table1.getHeader().data) << endl;
            }
        }
    }else {
        for(auto row2 : table2.getTable()) {
            if(table1.addTuple(row2)) {
                cout << row2.toString(table1.getHeader().data) << endl;
            }
        }
    }
    return table1;
}

string Interpreter::newTupleString(Relation oldRelation, Relation* newRelation) {
    stringstream out;
    unsigned int i = 0;
    unsigned int j = 0;
    vector<string> header = newRelation->getHeader().data;

    while (i < oldRelation.getNumOfRows()) {
        Tuple ithOldTuple = *std::next(oldRelation.getTable().begin(), i);
        Tuple jthNewTuple = *std::next(newRelation->getTable().begin(), j);
        if (ithOldTuple.data != jthNewTuple.data) {
            out << jthNewTuple.toString(header);
            j++;
        } else { i++; j++; }
    }
    while (j < newRelation->getNumOfRows()) {
        Tuple jthNewTuple = *std::next(newRelation->getTable().begin(), j);
        out << jthNewTuple.toString(header);
    }
    cout << "memes" << out.str() << endl;
    return out.str();
}

void Interpreter::interpretAndUpdate(const Rule rule) {
    vector<Relation> theTables;
    string newName = rule.getHeadPredicate().at(0);
    for (Predicate bodyPredicate : rule.getBodyPredicates()) {
        theTables.push_back( interpretPredicate(bodyPredicate) );
    }

    Relation joinedRelation = join(theTables.at(0), theTables.at(0), newName);

    for (unsigned int i = 1; i < theTables.size(); i++) {
        joinedRelation = join(joinedRelation, theTables.at(i), newName);
    }

    vector<unsigned int> columnIndexes;
    auto header = rule.getHeadPredicate();
    reverse(header.begin(), header.end());
    header.pop_back();
    std::reverse(header.begin(), header.end());


    for (const auto& headerValue : header) {
        auto currentTable = joinedRelation.getHeader().data;
        auto iter = find(currentTable.begin(), currentTable.end(), headerValue);
        int index = iter - currentTable.begin();
        columnIndexes.push_back(index);
    }

    Relation databaseRelation = data.getRelationCopy( rule.getHeadPredicate().at(0) );
    Relation projectedRelation = joinedRelation.project(columnIndexes);
    Relation renamedRelation = projectedRelation.rename( databaseRelation.getHeader().data );
    cout << rule.toString() << endl;
    Relation unifiedRelation = unification(databaseRelation, renamedRelation);

    data.getRelation( rule.getHeadPredicate().at(0) )->overRideData( unifiedRelation );
}

vector<set<int>> Interpreter::findDependencies() {
    vector<set<int>> returnVector;
    for (Rule rule : program.getRules()) {
        set<int> currentSet;
        for (auto body : rule.getBodyPredicates()) {
            int i = 0;
            for (Rule compare : program.getRules()) {
                if (compare.getHeadPredicate().at(0) == body.getID()) {
                    currentSet.insert(i);
                }
                i++;
            }
        }
        returnVector.push_back(currentSet);
    }
    return returnVector;
}

void Interpreter::createGraphs() {
    int numOfRules = program.getRules().size();
    forwardGraph.loadMap(numOfRules);
    reverseGraph.loadMap(numOfRules);

    int i = 0;
    auto foundDependencies = findDependencies();
    for(unsigned int i = 0; i < numOfRules; i++) {
        set<int> dependantRules = foundDependencies.at(i);
        for (const int& j : dependantRules) {
            forwardGraph.addEdge(i, j);
            reverseGraph.addEdge(j, i);
        }
    }
}





