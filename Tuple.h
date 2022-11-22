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

public:
    Tuple(vector<string> inputData) { data = inputData; }

    vector<string> data;

    string toString(vector<string> header);
    string getEntryAtCol(unsigned int col) { return data.at(col); }

    bool operator< (const Tuple &rhs) const {
        return data < rhs.data;
    }
};


#endif //PROJECT_1_TUPLE_H
