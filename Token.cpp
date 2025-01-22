#include "Token.h"

Token::Token(TokenType type, const std::string& value) : type(type), value(value) {}

TokenType Token::getType() const {
    return type;
}

string Token::getValue() const {
    return value;
}
