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

#endif /* PARSER_SRC_PARSER_H_ */
