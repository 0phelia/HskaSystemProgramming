/*
 * Parser.h
 *
 *  Created on: 16.01.2016
 *      Author: work
 */
#pragma once

#include "../../scanner/include/Scanner.h"
#include "../../scanner/include/Token.h"
#include "../../scanner/include/Information.h"

#include <stdio.h>
#include "Node.h"
#include <iostream>
#include <fstream>

typedef enum {
	NichtDefiniert,		// 0 
	IdentifierU, 		// 1   "abc"
	Number, 			// 2	7239
	VorwaertsSchraegstrich,	// 3   	:
	IstGleichZeichen, 	// 4 	=
	NichtDefinier2, 	// 5
	NichtDefinier3, 	// 6
	kleinerDoppelpunktGroesser, // 7   =:=
	DoppelpunktIstGleich,//8 :=
	NichtDefinier4, 	// 9
	UndZeichen, 		// 10   &&
	NichtDefinier5, 	// 11
	NichtDefinier6, 	// 12
	Stern, 				// 13   *
	NichtDefinier7, 	// 14
	NichtDefinier8, 	// 15
	NichtDefinier9, 	// 16
	NichtDefinier10, 	// 17
	NichtDefinier11, 	// 18
	Plus, 				// 19	+
	Minus, 				// 20   -
	Ausrufezeichen, 	// 21	!
	Semikolon, 			// 22   ;
	KleinerAls,			// 23	<
	GroesserAls,		// 24	>
	RundeKlammerAuf,	// 25	(
	RundeKlammerZu,		// 26	)
	GeschweifteKlammerAuf,// 27 {
	GeschweifteKlammerZu,// 28  }
	EckigeKlammerAuf,	// 29	[
	EckigeKlammerZu,	// 30	]
	KeywordIf,			// 31
	KeywordWhile,		// 32	
	KeywordElse,		// 33
	KeywordInt,			// 34
	KeywordWrite,		// 35
	KeywordRead			// 36
} StateUpdated;



class Parser {
public:
	Parser(Scanner* s, char* output);
	virtual ~Parser();
	Node* parse();
	Node* match(StateUpdated typ);
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

	CheckType getCheckTypeOfIdentifier(Node* node);
	
	void setCheckTypeOfIdentifier(Node* node, CheckType checkType);
private:
	Scanner* scanner;
	Token* token;
	std::ofstream code;
	uint16_t labelcounter;
};
