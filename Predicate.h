//
// Created by Dallin on 9/30/22.
//

#ifndef PROJECT_1_PREDICATE_H
#define PROJECT_1_PREDICATE_H
#include <vector>
#include <string>
#include <sstream>
#include "Parameter.h"

using namespace std;

class Predicate {
private:
    string id;
    vector<Parameter> parameters;

public:
    Predicate(vector<Parameter> inputList, string inputID) {
        parameters = inputList;
        id = inputID;
    }

    void addParameter(Parameter input) { parameters.push_back(input); }

    string toString();
};


#endif //PROJECT_1_PREDICATE_H
