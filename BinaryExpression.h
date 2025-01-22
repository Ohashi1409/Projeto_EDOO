#ifndef BINARYEXPRESSION_H
#define BINARYEXPRESSION_H

#include "Expression.h"
#include <memory>
#include <string>

using namespace std;

class BinaryExpression : public Expression {
    private:
        string op;
        Expression* left;
        Expression* right;
    public:
        BinaryExpression(const string& op, Expression* left, Expression* right);
        int evaluate() const override;
        bool isBool() const override;
        ~BinaryExpression();
};

#endif