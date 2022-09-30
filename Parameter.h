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
    string type; //ID or String type from token
public:
    Parameter(string inputValue, string inputType) {
        actualValue = inputValue;
        type = inputType;
    }
    ~Parameter();

    string getActualValue() { return actualValue; }
    string getType() { return type; }

};


#endif //PROJECT_1_PARAMETER_H
