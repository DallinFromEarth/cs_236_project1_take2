//
// Created by Dallin on 9/19/22.
//

#ifndef PROJECT_1_MATCHERAUTOMATON_H
#define PROJECT_1_MATCHERAUTOMATON_H

#include "Automaton.h"

class MatcherAutomaton : public Automaton {
private:
    char charToMatch;
public:
    MatcherAutomaton(TokenType inputType, char inputSymbol) : Automaton(inputType) { charToMatch = inputSymbol; }  // Call the base constructor

    void S0(const std::string& input);
};


#endif //PROJECT_1_MATCHERAUTOMATON_H
