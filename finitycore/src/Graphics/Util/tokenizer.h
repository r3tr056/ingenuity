/* Copyright (C) 2021 Finity Division - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the Lesser GNU GPL license, which unfortunately 
 * won't be written for another century.
 *
 * You should have received a copy of the Lesser GPL license
 * with this file. If not, please write to: , or visit :
 * 
 * Author : hopeJRD@finity.io
 * 
 */

#pragma once
#ifndef _TOKENIZER_H_
#define _TOKENIZER_H_

#include <string>
#include <iosfwd>
#include <fstream>

class Tokenizer {
public:
    enum TokenType {
        TOKEN_NAME = 0,
        TOKEN_STRING,
        TOKEN_NUMBER,
        TOKEN_BEGIN,
        TOKEN_END,
        TOKEN_NULL,
        TOKEN_BEGIN_GROUP,
        TOKEN_END_GROUP,
        TOKEN_BEGIN_ARRAY,
        TOKEN_END_ARRAY,

    };

    Tokenizer(std::ifstream*);
    TokenType getTokenType();
    TokenType nextToken();
    void pushBack();
    double getNumberValue();
    std::string getNameValue();
    std::string getStringValue();

    int getLineNumber();

private:
    enum State {
        START_STATE = 0,
        NAME_STATE,
        NUMBER_STATE,
        FRACTION_STATE,
        EXPONENT_STATE,
        EXPONENT_FIRST_STATE,
        DOT_STATE,
        COMMENT_STATE,
        STRING_STATE,
        ERROR_STATE,
        STRING_ESCAPE_STATE,
        UNICODE_ESCAPE_STATE
    };

    std::ifstream* in;
    int nextChar;
    TokenType tokenType{ TOKEN_BEGIN };
    bool haveValidNumber { false };
    bool haveValidName { false };
    bool haveValidString { false };

    unsigned int unicodeValue{ 0 };
    unsigned int unicodeEscapeDigits{ 0 };

    bool pushBack{ false };
    int readChar();
    void syntaxError(const char*);
    double numberValue { 0.0 };
    std::string textToken;
    int lineNum{ 1 };
};

#endif