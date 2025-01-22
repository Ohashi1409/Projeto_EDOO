#ifndef LEXSCAN_H
#define LEXSCAN_H

#include <string>
#include "Token.h"
#include <vector>

using namespace std;

class Scanner {
    private:
        string expression;
        size_t position;

        Token nextToken();
    public:
        Scanner(const string& expression);
        vector<Token> scan();
};
#endif