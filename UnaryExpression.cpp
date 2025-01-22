#include "UnaryExpression.h"

using namespace std;

UnaryExpression::UnaryExpression(const string& op, Expression* exp) : op(op), exp(exp) {
    if (op == "-") {
        boolean = false;
    }
    else {
        boolean = true;
    }
}

UnaryExpression::~UnaryExpression(){
    delete exp;
}

int UnaryExpression::evaluate() const {
    int expVal = exp->evaluate();

    if (op == "-") {
        return -expVal;
    }
    if (op == "!"){
        return !expVal;
    }
    else {
        return expVal;   //não deve chegar aqui ( caso do error )
    }
}

bool UnaryExpression::isBool() const {
    return boolean;
}