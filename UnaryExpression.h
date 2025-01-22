#ifndef UNARYEXPRESSION_H
#define UNARYEXPRESSION_H

#include "Expression.h"
#include <string>

using namespace std;

class UnaryExpression : public Expression {
    private:
        string op;
        Expression* exp;
        bool boolean;
    public:
        UnaryExpression(const string& op, Expression* exp);
        int evaluate() const override;
        bool isBool() const override;
        ~UnaryExpression();
};

#endif