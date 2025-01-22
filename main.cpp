#include "Parser.h"
#include "Scanner.h"
#include "Token.h"
#include "Expression.h"
#include "Literal.h"
#include "BinaryExpression.h"
#include <vector>
#include <iostream>
#include <string>

using namespace std;

int main() {
    int qtd_casos;
    cin >> qtd_casos;
    cin.ignore();

    for (int i = 0; i < qtd_casos; i++) {
        string exp;
        getline(cin, exp);

        Scanner scanner(exp);
        vector<Token> tokens = scanner.scan();

        int left_parenthesis = 0;
        int right_parenthesis = 0;

        for (int i = 0; i < tokens.size(); i++) {
            if (tokens[i].getValue() == "(") { left_parenthesis++; }
            else if (tokens[i].getValue() == ")") { right_parenthesis++; }
        }

        Parser parser(tokens);
        
        Expression* expression = parser.parseExp();

        if (parser.possibleExp() && (left_parenthesis == right_parenthesis)) {
            if (parser.isBool()) {
                if (expression->evaluate()){
                    cout << "true" << endl;
                }
                else {
                    cout << "false" << endl;
                }
            }
            else {
                cout << expression->evaluate() << endl;
            }
        }
        else {
            cout << "error" << endl;
        }
        delete expression;
    }

    return 0;
}