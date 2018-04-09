/*
 * Information.h
 *
 *  Created on: Nov 11, 2015
 *      Author: arty
 */

#pragma once

//#include "TerminalType.h"
//#include "../../Parser/include/Node.h"

class Information {
	char* lexem;
	int checkType;

	int additionalShitType;
public:
	Information();
	Information(char* lexem);
	virtual ~Information();
	void setLexem(char* lexem);
	char* getLexem();

	bool matches(const char* other);

	int getCheckType();
	void setCheckType(int checkType);

	bool isNumber();
	bool isIdentifier();
	bool isIf();
	bool isWhile();
	bool isElse();
	bool isWrite();
	bool isRead();
	bool isIntKeyword();
	bool isKlammerAuf();

	void setAdditionalShitType(int addshitType);
};

