//
// Created by Dallin on 9/20/22.
//

#include "IDAutomaton.h"

void IDAutomaton::S0(const std::string& input) {
    if (isalpha(input.at(0))) {
        inputRead++;
        index++;
        S1(input);
    }
    else { Serr(); }
}

void IDAutomaton::S1(const std::string& input) {
    if (index >= input.size()) { return; } //IF END OF FILE
    else if (isalnum(input.at(index))) {
        inputRead++;
        index++;
        if(index >= input.size()) { return; } //END OF FILE
        S1(input);
    }
    else { return; }

    //This is what we thought it would be, but it looks like (after
    //reviewing output examples, IDs don't have to end with space
    //else if (isspace(input.at(index))) { return; } //Basically go to S2, final state
    //else { Serr(); }
}