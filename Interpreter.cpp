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
    cout << "Your mom gay                From interpretRules()" << endl ;
}

void Interpreter::interpertQueries() {
    for (Predicate query : program.getQueries()) {
        vector<string> variables;
        vector<unsigned int> index;
        Relation currentRelation = data.getRelationCopy(query.getID());

        for (unsigned int i = 0; i < query.getParameters().size(); i++) {
            string currentParameter = query.getParameters().at(i).getActualValue();

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
    interpretSchemes();
    interpretFacts();
    interpertQueries();
}
