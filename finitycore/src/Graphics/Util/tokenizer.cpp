#include <cmath>
#include <cctype>
#include <iomanip>
#include <cstdlib>
#include "tokenizer.h"

using namespace std;

static bool issep(char c) { return !isdigit(c) && !isalpha(c) && c != '.'; }

Tokenizer::Tokenizer(ifstream *_in) : in(_in) {}

Tokenizer::TokenType Tokenizer::nextToken() {
    State state = START_STATE;
    if (pushBack) {
        pushBack = false;
        return tokenType;
    }

    textToken = "";
    haveValidName = false;
    haveValidName = false;
    haveValidString = false;


    if (tokenType == TOKEN_BEGIN) {
        nextChar = readChar();
        if (in->eof())
            return TOKEN_END;
    } else if (tokenType == TOKEN_END) {
        return tokenType;
    }

    double integerValue = 0;
    double fractionValue = 0;
    bool sign = false;
    bool fracExp = false;
    double exponentValue = 0;
    bool exponentSign = false;

    TokenType newTok = TOKEN_BEGIN;
    while (newTok == TOKEN_BEGIN)
    {
        switch (state)
        {
            case START_STATE:
            if (isspace(nextChar))
        }
    }
}
