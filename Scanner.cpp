#include "Scanner.h"

using namespace std;

Scanner::Scanner(const string& expression) : 
expression(expression), position(0) {}

vector<Token> Scanner::scan() {
    vector<Token> tokens;
    Token token = nextToken();
    while (token.getType() != TokenType::END) {
        tokens.push_back(token);
        token = nextToken();
    }
    return tokens;
}

Token Scanner::nextToken() {
    while (position < expression.size() && expression[position] == ' ') {
        position++;
    }

    if (position >= expression.size()) {
        return Token(TokenType::END, "");
    }

    if (isdigit(expression[position])) {
        size_t begin = position;
        while (position < expression.size() && isdigit(expression[position])) {
            position++;
        }
        return Token(TokenType::NUMBER, expression.substr(begin, position - begin));
    }

    if (isalpha(expression[position])) {
        size_t begin = position;
        while (position < expression.size() && isalnum(expression[position])) {
            position++;
        }
        string str = expression.substr(begin, position - begin);
        if (str == "true" || str == "false") {
            return Token(TokenType::BOOLEAN, str);
        }
        return Token(TokenType::VARIABLE, str);
    }

    if (expression[position] == '+' || expression[position] == '-' || 
        expression[position] == '*' || expression[position] == '/' || 
        expression[position] == '%' || expression[position] == '(' || 
        expression[position] == ')') {
        return Token(TokenType::OPERATOR, expression.substr(position++, 1));
    }

    if (expression[position] == '<') {
        position++;
        if (position < expression.length() && expression[position] == '=') {
            position++;
            return Token(TokenType::OPERATOR, "<=");
        }
        return Token(TokenType::OPERATOR, "<");
    }

    if (expression[position] == '>') {
        position++;
        if (position < expression.length() && expression[position] == '=') {
            position++;
            return Token(TokenType::OPERATOR, ">=");
        }
        return Token(TokenType::OPERATOR, ">");
    }

    if (expression[position] == '=') {
        position++;
        if (position < expression.length() && expression[position] == '=') {
            position++;
            return Token(TokenType::OPERATOR, "==");
        }
        return Token(TokenType::INOPERATIVE, "=");
    }

    if (expression[position] == '!') {
        position++;
        if (position < expression.length() && expression[position] == '=') {
            position++;
            return Token(TokenType::OPERATOR, "!=");
        }
        return Token(TokenType::OPERATOR, "!");
    }

    if (expression[position] == '&') {
        position++;
        if (position < expression.length() && expression[position] == '&') {
            position++;
            return Token(TokenType::OPERATOR, "&&");
        }
        return Token(TokenType::INOPERATIVE, "&");
    }

    if (expression[position] == '|') {
        position++;
        if (position < expression.length() && expression[position] == '|') {
            position++;
            return Token(TokenType::OPERATOR, "||");
        }
        return Token(TokenType::INOPERATIVE, "|");
    }

    if (expression[position] == '(') {
        position++;
        return Token(TokenType::PARENTHESIS, "(");
    }

    if (expression[position] == ')') {
        position++;
        return Token(TokenType::PARENTHESIS, ")");
    }

    if (expression[position] == '+' || expression[position] == '-' || expression[position] == '*' || expression[position] == '/' || expression[position] == '<' || expression[position] == '>') {
        position++;
        return Token(TokenType::OPERATOR, string(1, expression[position]));
    }

    return Token(TokenType::INOPERATIVE, string(1, expression[position]));

    throw runtime_error("Error");
}