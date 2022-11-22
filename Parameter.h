//
// Created by Dallin on 9/30/22.
//

#ifndef PROJECT_1_PARAMETER_H
#define PROJECT_1_PARAMETER_H
#include <string>

using namespace std;

class Parameter {
private:
    string actualValue;

public:
    Parameter(string inputValue) { actualValue = inputValue; }

    string getActualValue() const { return actualValue; }
};


#endif //PROJECT_1_PARAMETER_H
