//
// Created by Dallin on 9/19/22.
//

#ifndef PROJECT_1_KEYWORDAUTOMATON_H
#define PROJECT_1_KEYWORDAUTOMATON_H

#include "Automaton.h"

class KeywordAutomaton : public Automaton {
private:
    string stringToMatch;
public:
    KeywordAutomaton(TokenType inputType, string inputString) : Automaton(inputType) { stringToMatch = inputString; }  // Call the base constructor

    void S0(const std::string& input);
};


#endif //PROJECT_1_KEYWORDAUTOMATON_H
