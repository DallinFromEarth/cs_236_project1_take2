//
// Created by Dallin on 9/20/22.
//

#include "CommentAutomaton.h"

void CommentAutomaton::S0(const std::string &input) {
    if (input.at(0) == '#') {
        index++;
        inputRead++;
        S1(input);
    }
    else { return; }
}

void CommentAutomaton::S1(const std::string &input) {
    if (index >= input.size() || input.at(index) == '\n') { //EOF or NEWLINE
        S_line();
    }
    else if (input.at(index) == '|') {
        index++;
        inputRead++;
        S3(input);
    }
    else {
        index++;
        inputRead++;
        S2(input);
    }
}
void CommentAutomaton::S2(const std::string &input) {
    if (index >= input.size() || input.at(index) == '\n') { //EOF or NEWLINE
        S_line();
    }
    else {
        index++;
        inputRead++;
        S2(input);
    }
}
void CommentAutomaton::S3(const std::string &input) {
    if (index >= input.size()) { //EOF
        S_undef();
    }
    else if (input.at(index) == '|') {
        index++;
        inputRead++;
        S4(input);
    }
    else {
        if (input.at(index) == '\n') {
            newLines++;
        }
        index++;
        inputRead++;
        S3(input);
    }
}
void CommentAutomaton::S4(const std::string &input) {
    if (index >= input.size()) { //EOF
        S_undef();
    }
    else if (input.at(index) == '#') {
        index++;
        inputRead++;
        S_block();
    }
    else {
        index++;
        inputRead++;
        S3(input);
    }
}
void CommentAutomaton::S_line() { return; }
void CommentAutomaton::S_block() { return; }
void CommentAutomaton::S_undef() {
    type = TokenType::UNDEFINED;
    return;
}
