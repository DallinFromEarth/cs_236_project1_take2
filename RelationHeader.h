//
// Created by Dallin on 10/26/22.
//

#ifndef PROJECT_1_RELATIONHEADER_H
#define PROJECT_1_RELATIONHEADER_H

#include <set>
#include <sstream>
#include <string>
#include "Tuple.h"

using namespace std;

class RelationHeader {
private:
    vector<string> data;

public:
    RelationHeader(vector<string> inputData) {data = inputData;}

    string toString() {
        stringstream out;
        out << "Header:(";
        vector<string>::iterator itr;
        for(itr = data.begin(); itr != data.end(); itr++){
            out << *itr;
            if (itr != data.end()) {
                out << ",";
            }
        }
        out << ")";
        return out.str();
    }
};


#endif //PROJECT_1_RELATIONHEADER_H
