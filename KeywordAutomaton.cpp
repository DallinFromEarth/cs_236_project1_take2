//
// Created by Dallin on 9/19/22.
//

#include "KeywordAutomaton.h"

void KeywordAutomaton::S0(const std::string &input) {
    if(input.substr(0, stringToMatch.size()) == stringToMatch ) {
        inputRead = stringToMatch.size();
    }
    else{
        Serr();
    }
}