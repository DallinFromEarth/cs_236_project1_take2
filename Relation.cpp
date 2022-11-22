//
// Created by Dallin on 10/26/22.
//

#include "Relation.h"

string Relation::toString() {
    stringstream out;
    for (Tuple t : table) {
        if(header.numOfCol() > 0) {
            out << "  ";
        }
        for (unsigned int i = 0; i < header.numOfCol(); i++) {
            out << header.getHeaderAtCol(i) << "=";
            out << t.getEntryAtCol(i);
            if (i != header.numOfCol() - 1) {
                out << ", ";
            }
        }
        out << endl;
    }
    return out.str();
}

Relation Relation::select1(int colIndex, string value) {
    Relation returnRelation(name, header);
    for(Tuple row : table) {
        if (row.data[colIndex] == value) {
            returnRelation.addTuple(row);
        }
    }
    return returnRelation;
}

Relation Relation::select2(int colIndex1, int colIndex2) {
    Relation returnRelation(name, header);
    for(Tuple row : table) {
        if (row.data[colIndex1] == row.data[colIndex2]) {
            returnRelation.addTuple(row);
        }
    }
    return returnRelation;
}

Relation Relation::project(vector<unsigned int> columnsToProject) {
    vector<string> newHeader;
    for (unsigned int i = 0; i < header.data.size(); i++) {
        //if the current column number is found in the vector columnsToProject
        if(find(columnsToProject.begin(), columnsToProject.end(), i) != columnsToProject.end()) {
            newHeader.push_back(header.data[i]);
        }
    }

    Relation returnRelation(name, newHeader);
    for(Tuple row : table) {
        vector<string> newRow;
        for (int i : columnsToProject) {
            newRow.push_back( row.getEntryAtCol(i) );
        }

        /*
        for (unsigned int i = 0; i < row.data.size(); i++) {
            //if the current column number is found in the vector columnsToProject
            if(find(columnsToProject.begin(), columnsToProject.end(), i) != columnsToProject.end()) {
                newRow.push_back(row.data[i]);
            }
        }*/

        returnRelation.addTuple(Tuple(newRow));
    }
    return returnRelation;
}

Relation Relation::rename(vector<string> newColumnNames) {
    if(newColumnNames.size() != header.data.size()) { throw "HEY! Relation::rename got a vector of column names that didn't match the size of the current table! Fix it!"; }

    vector<string> newHeader;
    for (unsigned int i = 0; i < newColumnNames.size(); i++) {
        newHeader.push_back(newColumnNames.at(i));
    }
    Relation returnRelation(name, newHeader);
    returnRelation.setTable(table);
    return returnRelation;
}
