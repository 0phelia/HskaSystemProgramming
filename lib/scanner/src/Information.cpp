/*
 * Information.cpp
 *
 *  Created on: Nov 18, 2015
 *      Author: arty
 */



#include <iostream>
#include <Information.h>

Information::Information() {
	this->checkType = 0; // noType from Node.h
	this->lexem = '\0';
	this->additionalShitType = -1;
}

Information::Information(char* lexem) {
	this->checkType = 1; // noType from Node.h
	setLexem(lexem);
	this->additionalShitType = -1;

}

Information::~Information() {

}

void Information::setLexem(char* lexem) {
	this->lexem = lexem;
}

char* Information::getLexem() {
	return lexem;
}

bool Information::matches(const char* other) {
	if (this->lexem == nullptr) {
		std::cout << "its fucking nullpt  "<< std::endl;
	}
	if (other == nullptr) {
		std::cout << "the second is too"<< std::endl;
	}
	const char* tmp1 = this->lexem;
	const char* tmp2 = other;
	
	while (tmp1[0] != '\0' || tmp2[0] != '\0') {
		if (tmp1++[0] != tmp2++[0]) {
			return false;
		}
	}
	return true;
}
void Information::setAdditionalShitType(int shittype) {
	this->additionalShitType = shittype;
}
// CheckableType Information::getType() {
// 	return this->type;
// }

// void Information::setType(CheckableType type) {
// 	this->type = type;
// }

int Information::getCheckType() {
	return checkType;
}

void Information::setCheckType(int checkType) {
	this->checkType = checkType;
	//std::cout << "Tried to set CheckType to " << checkType << " for " << lexem << std::endl;
}

bool Information::isNumber() {
	int i = 0;
	while (getLexem()[i] != '\0') {
		if ( ! (getLexem()[i] >= '0' && getLexem()[i] <= '9' )) {
			return false;
		}
		i++;
	}
	return true;
}

bool Information::isIdentifier() {
	return !isIf() && !isWhile() && !isElse() && !isWrite() && !isRead()
		&& !isIntKeyword() && !isKlammerAuf();
}

bool Information::isIf() {

	return (matches("if") || matches("IF"));
}

bool Information::isWhile() {
	return (matches("while") || matches("WHILE"));
}

bool Information::isElse() {
	return (matches("else") || matches("ELSE"));
}

bool Information::isWrite() {
	return matches("write");
}
bool Information::isRead() {
	return matches("read");
}

bool Information::isIntKeyword() {
	return matches("int");
}


bool Information::isKlammerAuf() {

	return matches("{");
}
