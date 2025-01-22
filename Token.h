#ifndef TOKEN_H
#define TOKEN_H

#include <string>

using namespace std;

enum class TokenType{
    NUMBER,
    BOOLEAN,
    OPERATOR,
    PARENTHESIS,
    VARIABLE,
    INOPERATIVE,
    END
};

class Token {
    private:
        TokenType type;
        string value;

    public:
        Token(TokenType type, const string& value);
        TokenType getType() const;
        string getValue() const;
};

#endif