//
// Created by Dallin on 10/31/22.
//

#ifndef PROJECT_1_INTERPRETER_H
#define PROJECT_1_INTERPRETER_H

#include "Database.h"
#include "DatalogProgram.h"

class Interpreter {
private:
    Database data;
    DatalogProgram program;

public:
    Interpreter(DatalogProgram input) { program = input; }

    void interpretSchemes();
    void interpretFacts();
    void interpretRules();
    void interpertQueries();

    string getDataBaseString() { return data.toString(); }
};


#endif //PROJECT_1_INTERPRETER_H
