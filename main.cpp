#include "Lexer.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char* argv[]) {
    //////OPEN FILE AND PROCESS IT INTO "bigInputString" FOR LATER USE//////
    string fileName = argv[1];
    string bigInputString ="";
    ifstream inputFile;
    inputFile.open(fileName);

    if(inputFile.is_open()) {
        stringstream inputStringStream;
        inputStringStream << inputFile.rdbuf();

        inputFile.close();
        bigInputString = inputStringStream.str();
    }
    else { cout << "ERROR OPENING FILE" << endl; return -1; }

    Lexer* lexer = new Lexer();
    lexer->Run(bigInputString);
    cout << lexer->getAllTokens();
    /*
    Lexer* steve = new Lexer();
    string steveString = "#j \n    #| dksajfh \n\n\n\n\n# |# \n hey #|dfksajg";
    steve->Run(steveString);
    cout << steve->getAllTokens(); */

    // TODO

    delete lexer;

    return 0;
}