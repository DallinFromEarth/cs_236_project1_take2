#ifndef LEXER_H
#define LEXER_H
#include <vector>
#include <sstream>
#include "Automaton.h"
#include "MatcherAutomaton.h"
#include "Token.h"
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"
#include "KeywordAutomaton.h"
#include "IDAutomaton.h"
#include "StringAutomaton.h"
#include "CommentAutomaton.h"

using namespace std;

class Lexer
{
private:
    vector<Automaton*> automata;
    vector<Token*> tokens;
    string stringToRead;

    void CreateAutomata();

    // TODO: add any other private methods here (if needed)

public:
    Lexer();
    ~Lexer();

    void Run(std::string& input);

    string getAllTokens();
    vector<Token*> getTokenVector() { return tokens; }

};

#endif // LEXER_H

