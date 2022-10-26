#include "Lexer.h"#include <iostream>#include <fstream>#include <sstream>#include "Parser.h"using namespace std;int main(int argc, char* argv[]) {    //////OPEN FILE AND PROCESS IT INTO "bigInputString" FOR LATER USE//////    string fileName = argv[1];    string bigInputString ="";    ifstream inputFile;    inputFile.open(fileName);    if(inputFile.is_open()) {        stringstream inputStringStream;        inputStringStream << inputFile.rdbuf();        inputFile.close();        bigInputString = inputStringStream.str();    }    else { cout << "ERROR OPENING FILE" << endl; return -1; }    Lexer* lexer = new Lexer();    lexer->Run(bigInputString);    vector<Token*> tokenVector = lexer->getTokenVector();    Parser* parser = new Parser(tokenVector);    DatalogProgram program = parser->parse();    if (program.isProgramValid()) {        cout << program.fullProgramToString();    }    cout << "Wahoo!" << endl;    delete lexer;    return 0;}