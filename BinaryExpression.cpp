#include "BinaryExpression.h"
#include <stdexcept>
#include <string>

using namespace std;

BinaryExpression::BinaryExpression(const string& op, Expression* left, Expression* right) : 
op(op), left(left), right(right) {}

BinaryExpression::~BinaryExpression(){
    delete left;
    delete right;
}

int BinaryExpression::evaluate() const {
    int leftVal = left->evaluate();
    int rightVal = right->evaluate();

    if (op == "+") {
        return leftVal + rightVal;
    } 
    else if (op == "-") {
        return leftVal - rightVal;
    } 
    else if (op == "*") {
        return leftVal * rightVal;
    } 
    else if (op == "/") {
        return leftVal / rightVal;
    } 
    else if (op == "%") {
        return leftVal % rightVal;
    } 
    else if (op == "<") {
        return leftVal < rightVal;
    } 
    else if (op == "<=") {
        return leftVal <= rightVal;
    } 
    else if (op == ">") {
        return leftVal > rightVal;
    } 
    else if (op == ">=") {
        return leftVal >= rightVal;
    } 
    else if (op == "||") {
        return leftVal || rightVal;
    } 
    else if (op == "&&") {
        return leftVal && rightVal;
    } 
    else if (op == "==") {
        return leftVal == rightVal;
    } 
    else if (op == "!=") {
        return leftVal != rightVal;
    } 
    else {
        return leftVal + rightVal; // não deve chegar aqui ( caso do error )
    }
}

bool BinaryExpression::isBool() const {
    return (op == "||" || op == "&&" || op == "==" || op == "!=" || op == ">" || op == "<" || op == ">=" || op == "<=");
}