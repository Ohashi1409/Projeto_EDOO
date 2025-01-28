#include "Parser.h"
#include "Token.h"
#include "Literal.h"
#include "UnaryExpression.h"
#include "BinaryExpression.h"

using namespace std;

Parser::Parser(){};

Parser::Parser(const vector<Token>& tokens) 
: tokens(tokens), position(0), possible_exp(true) {}

Token Parser::peekToken() const {
    if (!endOfExpression()) {
        return tokens[position];
    }
    return Token(TokenType::END, "");
}

Token Parser::useToken() {
    if (!endOfExpression()) {
        return tokens[position++];
    }
    return Token(TokenType::END, "");
}

bool Parser::endOfExpression() const{
    return position >= tokens.size();
}

bool Parser::possibleExp() const {
    return possible_exp;
}

bool Parser::isBool() const {
    return boolean;
}

Expression* Parser::parseExp() {
    return parseOrExp();
}

Expression* Parser::parseOrExp(){
    Expression* left = parseAndExp();

    while (!endOfExpression() && peekToken().getValue() == "||") {
        this->boolean = true;
        Token op = useToken();
        Expression* right = parseAndExp();
        if (!left->isBool() || ! right->isBool()) { possible_exp = false; }
        left = new BinaryExpression(op.getValue(), left, right);
    }
    return left;
}

Expression* Parser::parseAndExp(){
    Expression* left = parseEqExp();

    while (!endOfExpression() && peekToken().getValue() == "&&") {
        this->boolean = true;
        Token op = useToken();
        Expression* right = parseEqExp();
        if (!left->isBool() || ! right->isBool()) { possible_exp = false; }
        left = new BinaryExpression(op.getValue(), left, right);
    }
    return left;
}

Expression* Parser::parseEqExp(){
    Expression* left = parseRelExp();

    while (!endOfExpression() && (peekToken().getValue() == "==" || peekToken().getValue() == "!=")) {
        this->boolean = true;
        Token op = useToken();
        Expression* right = parseRelExp();
        if ((left->isBool() && !right->isBool()) || (!left->isBool() && right->isBool())) {
            possible_exp = false;
        }
        left = new BinaryExpression(op.getValue(), left, right);
    }
    return left;
}

Expression* Parser::parseRelExp(){
    Expression* left = parseAddExp();

    while (!endOfExpression() && (peekToken().getValue() == "<" || peekToken().getValue() == "<=" || peekToken().getValue() == ">" || peekToken().getValue() == ">=")) {
        boolean = true;
        Token op = useToken();
        Expression* right = parseAddExp();
        if (left->isBool() || right->isBool()) { 
            possible_exp = false; 
        }
        left = new BinaryExpression(op.getValue(), left, right);
    }
    return left;
}

Expression* Parser::parseAddExp(){
    Expression* left = parseMulExp();

    while (!endOfExpression() && (peekToken().getValue() == "+" || peekToken().getValue() == "-")) {
        Token op = useToken();
        Expression* right = parseMulExp();
        if (left->isBool() || right->isBool()) {
            this->possible_exp = false;
        }
        left = new BinaryExpression(op.getValue(), left, right);
    }
    return left;
}

Expression* Parser::parseMulExp(){
    Expression* left = parseUnaryExp();

    while (!endOfExpression() && 
            (peekToken().getValue() == "*" || 
            peekToken().getValue() == "/" || 
            peekToken().getValue() == "%")) {
        Token op = useToken();
        Expression* right = parseUnaryExp();
        if ((left->isBool() || right->isBool()) || (op.getValue() == "/" && right->evaluate() == 0)) {
            this->possible_exp = false;
        }
        left = new BinaryExpression(op.getValue(), left, right);
    }
    return left;
}

Expression* Parser::parseUnaryExp() {
    Token token = peekToken();

    if (token.getType() == TokenType::OPERATOR && (token.getValue() == "-" || token.getValue() == "!")) {
        useToken();
        Expression* exp = parseUnaryExp();
        if (token.getValue() == "-" && exp->isBool()) { possible_exp = false; }
        if (token.getValue() == "!") {
            boolean = true;
            if (!exp->isBool()) { possible_exp = false; }
        }
        return new UnaryExpression(token.getValue(), exp);
    } 
    return parsePrimaryExp();
}

Expression* Parser::parsePrimaryExp() {
    Token token = peekToken();

    if (token.getType() == TokenType::NUMBER || token.getType() == TokenType::BOOLEAN) {
        Expression* literal = new Literal(token.getValue());
        useToken();
        return literal;
    } 
    else if (token.getValue() == "(") {
        useToken();
        Expression* exp = parseExp();
        useToken();
        return exp;
    }
    else {
        this->possible_exp = false;
        return new Literal("0");
    }
}