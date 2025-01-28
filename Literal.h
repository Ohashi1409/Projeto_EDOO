#ifndef LITERAL_H
#define LITERAL_H

#include "Expression.h"
#include <string>

using namespace std;

class Literal : public Expression {
    private:
        string exp;
        bool boolean;
    public:
        Literal(); 
        Literal(string exp_);
        int evaluate() const override;
        bool isBool() const override;
    };

#endif