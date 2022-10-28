//
// Created by Dallin on 10/26/22.
//

#ifndef PROJECT_1_RELATIONHEADER_H
#define PROJECT_1_RELATIONHEADER_H

#include <set>
#include <sstream>
#include <string>
#include "Tuple.h"
#include <iostream>

using namespace std;

class RelationHeader {
private:
    vector<string> data;
    bool hasHeader;

public:
    RelationHeader() { hasHeader = false; }
    //constructor error work around
    void addHeader(vector<string> inputData) {
        if(hasHeader) { throw "Ya dingus, Header already added - first item: " + data.at(0); }
        data = inputData;
        hasHeader = true;
    }

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

    string getHeaderAtCol(unsigned int col) { return data.at(col); }

    unsigned int numOfCol() { return data.size(); }
};


#endif //PROJECT_1_RELATIONHEADER_H
