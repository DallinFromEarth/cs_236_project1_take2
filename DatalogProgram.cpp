//
// Created by Dallin on 9/30/22.
//

#include "DatalogProgram.h"

void DatalogProgram::addRule(Rule input) {
    rules.push_back(input);
}

void DatalogProgram::addScheme(Predicate input) {
    schemes.push_back(input);
}

void DatalogProgram::addFact(Predicate input) {
    facts.push_back(input);
}

void DatalogProgram::addQuery(Predicate input) {
    queries.push_back(input);
}

string DatalogProgram::rulesToString() {
    stringstream out;
    out << "Rules(" << rules.size() << "):" << endl;
    for (unsigned int i = 0; i < rules.size(); i++) {
        out << "  " << rules.at(i).toString() << endl;
    }
    return out.str();
}

string DatalogProgram::schemesToString() {
    stringstream out;
    out << "Schemes(" << schemes.size() << "):" << endl;
    for (unsigned int i = 0; i < schemes.size(); i++) {
        out << "  " << schemes.at(i).toString() << endl;
    }
    return out.str();
}

string DatalogProgram::factsToString() {
    stringstream out;
    out << "Facts(" << facts.size() << "):" << endl;
    for (unsigned int i = 0; i < facts.size(); i++) {
        out << "  " << facts.at(i).toString() << "." << endl;
    }
    return out.str();
}

string DatalogProgram::queriesToString() {
    stringstream out;
    out << "Queries(" << queries.size() << "):" << endl;
    for (unsigned int i = 0; i < queries.size(); i++) {
        out << "  " << queries.at(i).toString() << "?" << endl;
    }
    return out.str();
}

string DatalogProgram::domainToString() {
    set<string> domain = getDomain();
    stringstream out;
    out << "Domain(" << domain.size() << "):" << endl;
    for (auto x : domain) out << "  " << x << endl;
    return out.str();
}

set<string> DatalogProgram::getDomain() {
    set<string> domainSet;
    for (unsigned int i = 0; i < facts.size(); i++) {
        vector<Parameter> parameterList = facts.at(i).getParameters();
        for (unsigned int j = 0; j < parameterList.size(); j++) {
            domainSet.insert(parameterList.at(j).getActualValue());
        }
    }
    return domainSet;
}

string DatalogProgram::fullProgramToString() {
    stringstream out;
    out << schemesToString();
    out << factsToString();
    out << rulesToString();
    out << queriesToString();
    out << domainToString();
    return out.str();
}

/* std::set<std::string> sortedItems;

    for(int i = 1; i <= 5; ++i)
    {
        std::string name;
        std::cout << i << ". ";
        std::cin >> name;

        sortedItems.insert(name);
    }

    std::for_each(sortedItems.begin(), sortedItems.end(), &print);
    return 0; */