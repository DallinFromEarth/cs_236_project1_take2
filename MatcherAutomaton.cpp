//
// Created by Dallin on 9/19/22.
//

#include "MatcherAutomaton.h"

void MatcherAutomaton::S0(const std::string& input) {
    if (input[index] == charToMatch) {
        inputRead = 1;
    }
    else {
        Serr();
    }
}