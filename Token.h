#ifndef TOKEN_H
#define TOKEN_H
#include <string>

using namespace std;

enum class TokenType {
    COMMA,
    PERIOD,
    Q_MARK,
    LEFT_PAREN,
    RIGHT_PAREN,
    COLON,
    COLON_DASH,
    MULTIPLY,
    ADD,
    SCHEMES,
    FACTS,
    RULES,
    QUERIES,
    ID,
    STRING,
    COMMENT,
    UNDEFINED,
    EOF_TYPE,
};

class Token
{
private:
    string actualValue;
    int lineNumber;
    TokenType typeOfToken;
    static string tokenTypeToString(TokenType);

public:
    Token(TokenType type, std::string description, int line);
    string toString();
    // TODO: add other needed methods
};

#endif // TOKEN_H

