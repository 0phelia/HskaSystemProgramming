/*
 * Parser.h
 *
 *  Created on: 16.01.2016
 *      Author: work
 */
#include "../../Scanner/includes/Scanner.h"
#include "../../Scanner/includes/Token.h"
#include "../../Scanner/includes/Information.h"

#include <stdio.h>
#include "../includes/Node.h"
#include <iostream>
#include <fstream>
using namespace std;

#ifndef PARSER_SRC_PARSER_H_
#define PARSER_SRC_PARSER_H_

typedef enum {
	Number,
	Semikolon,
	EckigeKlammerAuf,
	EckigeKlammerZu,
	GeschweifteKlammerAuf,
	GeschweifteKlammerZu,
	RundeKlammerAuf,
	RundeKlammerZu,
	DoppelpunktIstGleich,
	Minus,
	Plus,
	Ausrufezeichen, 
	Stern,
	VorwaertsSchraegstrich,
	KleinerAls,
	GroesserAls,
	kleinerDoppelpunktGroesser,
	IstGleichZeichen,
	UndZeichen
	//uncheckedType,
	//intType,
	//intArrayType,
	//arrayType,
	//noType,
	//errorType
} State;

class Parser {
public:
	Parser(Scanner* s, char* output);
	virtual ~Parser();
	Node* parse();
	Node* match(CheckableType typ);
	Node* match(State typ);
	void nextToken();
	void error();
	Node* parseProg();
	Node* parseDecls();
	Node* parseDecl();
	Node* parseArray();
	Node* parseStatements();
	Node* parseStatement();
	Node* parseExp();
	Node* parseExp2();
	Node* parseIndex();
	Node* parseOpExp();
	Node* parseOp();
	Node* createNode(NodeType ntype);
	void typeCheck(Node* node);
	void makeCode(Node* node);
	void errorTypeCheck(const char* message, Token* token);
private:
	Scanner* scanner;
	Token* token;
	std::ofstream code;
	uint16_t labelcounter;
};

#endif /* PARSER_SRC_PARSER_H_ */
