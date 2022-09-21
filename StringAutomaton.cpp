//
// Created by Dallin on 9/20/22.
//

#include "StringAutomaton.h"

void StringAutomaton::S0(const std::string& input) {
    if (input.at(0) == '\'') {
        inputRead++;
        index++;
        S1(input);
    }
    else { Serr(); }
}

void StringAutomaton::S1(const std::string& input) {
    if (index >= input.size()) { S_undef(input); } //IF END OF FILE
    else {
        if (input.at(index) == '\n') { //IF NEW LINE
            newLines++;
        }
        if (input.at(index) != '\'') {
            inputRead++;
            index++;
            S1(input);
        } else if (input.at(index) == '\'') {
            inputRead++;
            index++;
            S2(input);
        } else {
            cout << "Unrecognized input in String Automaton" << endl;
            Serr();
        }
    }
}

void StringAutomaton::S2(const string& input) {
    if (index >= input.size()) { return; } //IF END OF FILE, we're done here
    else if (input.at(index) == '\'') {
        inputRead++;
        index++;
        S1(input);
    }
    else { return; }
}

void StringAutomaton::S_undef(const std::string &input) {
    type = TokenType::UNDEFINED;
    return;
}