//
// Created by Dallin on 10/26/22.
//

#ifndef PROJECT_1_TUPLE_H
#define PROJECT_1_TUPLE_H

#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Tuple {
private:
    vector<string> data;

public:
    Tuple(vector<string> inputData) { data = inputData; }

    string toSting();
};


#endif //PROJECT_1_TUPLE_H
