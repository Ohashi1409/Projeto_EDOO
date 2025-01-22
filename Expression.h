#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <string>

class Expression {
public:
    virtual ~Expression() = default;
    virtual int evaluate() const = 0;
    virtual bool isBool() const = 0;
};

#endif