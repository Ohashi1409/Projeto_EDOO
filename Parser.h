#ifndef PARSER_H
#define PARSER_H

#include "Expression.h"
#include "Token.h"
#include <memory>
#include <string>
#include <vector>

class Parser {
    private:
        vector<Token> tokens;
        size_t position;

        bool boolean = false;
        bool possible_exp;

        Token peekToken() const;
        Token useToken();
        bool endOfExpression() const;

        Expression* parseOrExp();
        Expression* parseAndExp();
        Expression* parseEqExp();
        Expression* parseRelExp();
        Expression* parseAddExp();
        Expression* parseMulExp();
        Expression* parsePrimaryExp();
        Expression* parseUnaryExp();

    public:
        Parser();
        Parser(const vector<Token>& expression);
        Expression* parseExp();
        bool isBool() const;
        bool possibleExp() const;
};

#endif