#include "Lexer.h"

Lexer::Lexer() {
    CreateAutomata();
}

Lexer::~Lexer() {
    while (automata.size() > 0) {
        delete automata.at(0);
        automata.erase(automata.begin());
    }
    while (tokens.size() > 0) {
        delete tokens.at(0);
        tokens.erase(tokens.begin());
    }
}

void Lexer::CreateAutomata() {
    automata.push_back(new MatcherAutomaton(TokenType::COMMA, ','));
    automata.push_back(new MatcherAutomaton(TokenType::PERIOD, '.'));
    automata.push_back(new MatcherAutomaton(TokenType::Q_MARK, '?'));
    automata.push_back(new MatcherAutomaton(TokenType::LEFT_PAREN, '('));
    automata.push_back(new MatcherAutomaton(TokenType::RIGHT_PAREN, ')'));
    automata.push_back(new MatcherAutomaton(TokenType::COLON, ':'));
    automata.push_back(new MatcherAutomaton(TokenType::MULTIPLY, '*'));
    automata.push_back(new MatcherAutomaton(TokenType::ADD, '+'));
    automata.push_back(new ColonDashAutomaton());
    automata.push_back(new KeywordAutomaton(TokenType::SCHEMES, "Schemes"));
    automata.push_back(new KeywordAutomaton(TokenType::FACTS, "Facts"));
    automata.push_back(new KeywordAutomaton(TokenType::RULES, "Rules"));
    automata.push_back(new KeywordAutomaton(TokenType::QUERIES, "Queries"));
    automata.push_back(new IDAutomaton());
    automata.push_back(new StringAutomaton());
    automata.push_back(new CommentAutomaton());
    // TODO: Add the other needed automata here
}

void Lexer::Run(std::string& input) {
    int lineNumber = 1;

    while( (input.size() != 0) && (isspace(input.at(0)))) { //Remove WhiteSpace
        if(input.at(0) == '\n') { lineNumber++; }
        input.erase(0, 1);
    }

    while(input.size() > 0) {
        int maxRead = 0;
        int inputRead = 0;
        Automaton* maxAutomaton = automata.at(0);

        for(Automaton* machine : automata) {
            inputRead = machine->Start(input);
            if(inputRead > maxRead) {
                maxRead = inputRead;
                maxAutomaton = machine;
            }
        }

        if(maxRead > 0) {
            Token* newToken = maxAutomaton->CreateToken(input.substr(0,maxRead), lineNumber);
            lineNumber += maxAutomaton->NewLinesRead();
            tokens.push_back(newToken);
        }
        else { //the only way I could figure this out, makes an undefined token
            maxRead = 1;
            Automaton* steve = new MatcherAutomaton(TokenType::UNDEFINED, input.at(0));
            Token* oofToken = steve->CreateToken(input.substr(0, maxRead), lineNumber);
            tokens.push_back(oofToken);
            delete steve;
        }
        input.erase(0, maxRead);
        while( (input.size() != 0) && (isspace(input.at(0)))) { //Remove WhiteSpace
            if(input.at(0) == '\n') { lineNumber++; }
            input.erase(0, 1);
        }
    }

    //This makes the EOF token
    lineNumber++;
    Automaton* endOfFileAuto = new MatcherAutomaton(TokenType::EOF_TYPE, 'Q'); //The Q means literally nothing!
    Token* oofToken = endOfFileAuto->CreateToken("", lineNumber);
    tokens.push_back(oofToken);
    delete endOfFileAuto;
}

string Lexer::getAllTokens() {
    stringstream outputStream;
    for(Token* currentToken : tokens) {
        outputStream << currentToken->toString() << endl;
    }
    outputStream << "Total Tokens = " << tokens.size();
    return outputStream.str();
}



// TODO: convert this pseudo-code with the algorithm into actual C++ code
/*
set lineNumber to 1
// While there are more characters to tokenize
loop while input.size() > 0 {
    set maxRead to 0
    set maxAutomaton to the first automaton in automata

    // TODO: you need to handle whitespace inbetween tokens

    // Here is the "Parallel" part of the algorithm
    //   Each automaton runs with the same input
    foreach automaton in automata (vector) {
        inputRead = automaton.Start(input)
        if (inputRead > maxRead) {
            set maxRead to inputRead
            set maxAutomaton to automaton
        }
    }
    // Here is the "Max" part of the algorithm
    if maxRead > 0 {
        set newToken to maxAutomaton.CreateToken(...)
            increment lineNumber by maxAutomaton.NewLinesRead()
            add newToken to collection of all tokens
    }
    // No automaton accepted input
    // Create single character undefined token
    else {
        set maxRead to 1
            set newToken to a  new undefined Token
            (with first character of input)
            add newToken to collection of all tokens
    }
    // Update `input` by removing characters read to create Token
    remove maxRead characters from input
}
add end of file token to all tokens
*/