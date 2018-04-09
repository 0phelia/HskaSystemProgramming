#pragma once

#include <string.h> // TODO: DELETE THIS LATER!!! Prohibited library!
#include <stdlib.h>  // for strtol()
#include "Information.h"

#ifndef SIGN_ARRAY_SZ
#define SIGN_ARRAY_SZ 14
#endif
class Token {
	int tType;
	int line;
	int column;
	long int value;
	Information* information;
	char symbol;

	char signArray[14] = {'+','-','!','&',';','(',')','{','}','[',']'};
		// TODO: test if 14
	char* errorMessage;

public:
	Token(int type, int line, int column);
	Token(int state, int l, int c, Information* info);
	virtual ~Token();
	char* itoc(int number);
	int getType();
	Information* getInformation();
	char* getLexem();
	int getLine();
	int getColumn();
	long getValue();
	void setValue(long int value);
	char getSymbol();
	void setSymbol(char symbol);
		void setType(int type);

	void setInformation(Information* info);
	bool hasSameTypeAs (Token* other);
		char* getErrorMessage();
	void setErrorMessage(char* errorMessage);

};
