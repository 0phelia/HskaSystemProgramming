/*
 * symboltable.h
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#pragma once


#include "StringTab.h"
#include "SymtabEntry.h"
#include "../../scanner/include/Information.h"
#include <iostream>

#define TABLE_SIZE 1019 // prime number here! btw 2^x - 1 is always prime
#define R_CONST 31      // prime number here too!

class Symboltable {

	SymtabEntry *hashTab[TABLE_SIZE];
	int density[TABLE_SIZE] = {0};
	StringTab* strTab;

public:
	Symboltable();
	virtual ~Symboltable();

	int hash(const char *lexem);
	SymtabEntry* insert(const char *lexem, int size);
	Information* lookup(const char* lexem);
	void initSymbols();
	void print();
};
