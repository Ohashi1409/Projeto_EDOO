#include "Literal.h"

using namespace std;

Literal::Literal(string expr_) : exp(expr_) {
    if (exp == "true" || exp == "false") {
        boolean = true;
    }
    else {
        boolean = false;
    }
} 

int Literal::evaluate() const {
    if (exp == "true"){
        return 1;
    }
    else if (exp == "false"){
        return 0;
    }
    else {
        return stoi(exp);
    }
}

bool Literal::isBool() const {
    return boolean;
}