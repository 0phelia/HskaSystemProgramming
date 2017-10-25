/*
 * Syntax.h
 *
 *  Created on: Nov 18, 2015
 *      Author: arty
 */

#ifndef AUTOMAT_INCLUDES_SYNTAX_H_
#define AUTOMAT_INCLUDES_SYNTAX_H_
#ifndef SIGN_ARRAY_SZ
#define SIGN_ARRAY_SZ 14
#endif
#define STATETABLE_WIDTH 18
#define STATETABLE_HEIGHT 10
#define KEYWORD_NUMBER 6
#define STATES_NUMBER STATETABLE_WIDTH +1 + STATETABLE_HEIGHT + 1 + 1

class Syntax {
	//  STRT_Z, IDEN_Z, INTG_Z,   COLN_Z, EQLS_Z, ASGN_Z, LCLN_Z, LCLL_Z, ASSG_Z, AND1_Z, AND2_Z,
	int stateTable[STATETABLE_HEIGHT][STATETABLE_WIDTH] = {
					/*          						  STRT 1   ID 2    INT 3     : 4      = 5   <ANY>6	  =: 7	 =:= 8	 := 9     & 10   && 11   Eof 12   WSP 13  * 14    :* 15 <comment>  *:    PROH_Z */
					/* a-Z */	{IDEN_Z, IDEN_Z, STRT_Z,   STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z,  EOF_Z,  STRT_Z, STRT_Z, OPNC_Z, OPNC_Z, STRT_Z, STRT_Z},
					/* 0-9 */	{INTG_Z, IDEN_Z, INTG_Z,   STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z,  EOF_Z,  STRT_Z, STRT_Z, OPNC_Z, OPNC_Z, STRT_Z, STRT_Z},
					/*  *  */	{MULT_Z, STRT_Z, STRT_Z,   OPNC_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z,  EOF_Z,  STRT_Z, STRT_Z, COMM_Z, COMM_Z, STRT_Z, STRT_Z},
					/*  :  */ 	{COLN_Z, STRT_Z, STRT_Z,   STRT_Z, LCLN_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z,  EOF_Z,  STRT_Z, STRT_Z, OPNC_Z, CLSC_Z, STRT_Z, STRT_Z},
					/*  =  */ 	{EQLS_Z, STRT_Z, STRT_Z,   ASSG_Z, STRT_Z, STRT_Z, LCLL_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z,  EOF_Z,  STRT_Z, STRT_Z, OPNC_Z, OPNC_Z, STRT_Z, STRT_Z},
		/*  added new	&  */   {AND1_Z, STRT_Z, STRT_Z,   STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, AND2_Z, STRT_Z,  EOF_Z,  STRT_Z, STRT_Z, OPNC_Z, OPNC_Z, STRT_Z, STRT_Z},
					/* RST */	{ASGN_Z, STRT_Z, STRT_Z,   STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z,  EOF_Z,  STRT_Z, STRT_Z, OPNC_Z, OPNC_Z, STRT_Z, STRT_Z},
					/* EOF */	{EOF_Z,  STRT_Z, STRT_Z,   STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z,  EOF_Z,  STRT_Z, STRT_Z, OPNC_Z, OPNC_Z, STRT_Z, STRT_Z},
					/* WSP */	{WSP_Z,  STRT_Z, STRT_Z,   STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z,  STRT_Z, STRT_Z, STRT_Z, OPNC_Z, OPNC_Z, STRT_Z, STRT_Z},
					/* PRH */	{PROH_Z, STRT_Z, STRT_Z,   STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z,  EOF_Z,  STRT_Z, STRT_Z, OPNC_Z, OPNC_Z, STRT_Z, STRT_Z}
		};
	char *ttypeString[STATES_NUMBER + KEYWORD_NUMBER + 2] = {
						  	 "Start     ", "Identifier", "Integer   ", "Colon     ", //  0- 3
							 "Equals    ", "Any       ", "=:        ", "=:=       ", //  4- 7
							 "Assignment", "SglAndTok ", "DblAndTok ", "Eof       ", //  8-11
							 "Whitespace", "Multiplic ", "--:*--    ", "COMMENT   ", // 12-15
							 "--*:--    ", "PROHIBITED", "MinusToken", "PlusToken ", // 16-19
							 "MinusToken", "NotToken  ", "SemicolTok", "LessToken ", // 20-23  replace '&' with SglAndTok and replace '&&' with DblAndTok
							 "GreatToken", "Paranth ( ", "Paranth ) ", "Braces {  ", // 24-27 all tokens starting from this line have incremented index from now on
							 "Braces }  ", "Brackets [", "Bracket ] ", "IF-Token  ", // 28-31
							 "WHILE-Toke", "ELSE-Token", "INT-Token ", "WRITE-Tokn", // 32-35		// 32-35
							 "READ-Token"
	};
	 char signArray[SIGN_ARRAY_SZ] = {'+', '-', '!', ';', '<', '>', '(', ')','{', '}', '[', ']'}; // remove '&' since its got replaced by '&&' , add '<' and '>'

	 char *keywordsArray[KEYWORD_NUMBER * 2 - 3] = {"if", "IF", "while", "WHILE", "else", "ELSE", "int", "write", "read"};

public:
	int keywordNumber;
	enum States {
		STRT_Z, IDEN_Z, INTG_Z, COLN_Z, 		// 0..3
		EQLS_Z, ASGN_Z, LCLN_Z, LCLL_Z,		// 4..7
		ASSG_Z, AND1_Z, AND2_Z, EOF_Z,		// 8..11
		WSP_Z, MULT_Z, OPNC_Z, COMM_Z,		// 12..15
		CLSC_Z, PROH_Z, NULL_STATE, PLUS_Z,		// 16..19
		MIN_Z, NOT_Z, AND_Z, SEMI_Z,		// 20..23
		PARO_Z, PARC_Z, BRACO_Z, BRACC_Z,		// 24..27
		BRACKO_Z, BRACKC_Z, IF_Z, WHILE_Z,		// 28..31
		INTKEY_Z, WRITE_Z, ELSE_Z, READ_Z		// 32..35
	};
	enum Symbols {
		ANY_LETTER, ANY_DIGIT, MULT_SYMB, COLON_SYMB, EQUALS_SYMB, AND_SYMB, REST_SYMB,
		EOF_SYMB, WHITESPACE_SYMB, PROH_SYMB
	};

	Syntax();

	virtual ~Syntax();

	const char *getTokenTypeAsChar(int num);

	int getState(int i, int j);

	int isPacked(char sign);

	int ifKeyword(const char *lexem);

	bool matches(const char *one, const char *another);
};

#endif /* AUTOMAT_INCLUDES_SYNTAX_H_ */
