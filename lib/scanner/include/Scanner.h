/*
 * Scanner.h
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */
#pragma once

#include <iostream>
#include <stdio.h>
#include "../../symboltable/include/Symboltable.h"
#include "../../buffer/include/Buffer.h"
#include "../../automat/include/Automat.h"
#include "../../automat/include/Syntax.h"
#include "Token.h"


class Scanner {
    Symboltable *stab;
    Buffer *buffer;
    Automat *automat;
    Syntax *syntax;
public:
    Scanner(char *filename);

    Scanner(char *filename, Symboltable *st);

    int mapStateToType(int state, const char *lexem);

    void getNumberToken(const char *lexem, Token *t);

    Token *nextToken();

    virtual ~Scanner();

    Information *getInfo(char *lexem);

    void mapRightCheckableTypeToInfo(Information *info, int tokenType);

};