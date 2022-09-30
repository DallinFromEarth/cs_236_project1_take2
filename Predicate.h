//
// Created by Dallin on 9/30/22.
//

#ifndef PROJECT_1_PREDICATE_H
#define PROJECT_1_PREDICATE_H
#include <vector>
#include <string>
#include "Parameter.h"

using namespace std;

class Predicate {
private:
    vector<Parameter> parameters;
    string id;

public:
    Predicate(string inputID) { id = inputID; }
    ~Predicate();

    void addParameter(Parameter input) { parameters.push_back(input); }

};


#endif //PROJECT_1_PREDICATE_H
