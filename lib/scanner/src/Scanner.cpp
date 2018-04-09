/*
 * Scanner.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */


#include "../include/Scanner.h"

#define CONV_ERR "error: cannot convert given CHAR* to LONG INT"
#define CONV_ERR_OVERFLOW "error: given integer is too big to be converted to LONG INT"

Scanner::Scanner(char *filename) {
	buffer = new Buffer(filename);
	automat = new Automat();
	syntax = new Syntax();
	stab = nullptr;
}

Scanner::Scanner(char *filename, Symboltable* st) {
	stab = st;
	buffer = new Buffer(filename);
	automat = new Automat();
	syntax = new Syntax();
}

Scanner::~Scanner() {
	delete buffer;
	delete automat;
	delete syntax;
}

Information* Scanner::getInfo(char* lexem) {
	return stab->lookup(lexem);
}

/*
 * feeds characters to the Automat, untill the new lexem is found.
 * Then tries to attribute it to some token.
 * @return current token
 */
Token *Scanner::nextToken() {
	//std::cout << "debuging *** Scanner::nextToken STRT" << std::endl;

	char currentChar;
	int finalState = 0;

	//std::cout << "debuging *** Scanner::nextToken DO-STRT" << std::endl;
	/* run Automat and feed it char by char, till any lexem is found */
	if(buffer->isEnd())
		return new Token(22,-1,-1);
	do {
		currentChar = buffer->getChar();
		int back_steps = automat->read(currentChar);
		finalState = automat->getFinalState();
		buffer->ungetChar(back_steps);
		if (automat->isLexemReady() && (finalState == Syntax::WSP_Z || finalState == Syntax::CLSC_Z)) {
			automat->reset();
		}
	}while (!buffer->isEnd() && currentChar != '\0' &&  !automat->isLexemReady());
	//std::cout << "debuging *** Scanner::nextToken DO-NED" << std::endl;

	/* save all information about the lexem */
	const char* lexem = automat->getLexem();
	int lexemLength = automat->getLexemLength();
	int line = automat->getLine();
	int col = automat->getColumn();
	int tokenType = mapStateToType(finalState, lexem);

	/* create Token */
	Token* t = new Token(tokenType, line, col);

	/* add additional information to the token */
	Information* info;
	if ( tokenType == Syntax::IDEN_Z || (tokenType >= 30 && tokenType < 37) 
		|| tokenType == 19 // +
		|| tokenType == 20 // -
		|| tokenType == 13 // *
		|| tokenType == 3 // : colon

		|| tokenType == 23 // <
		|| tokenType == 24 // >
		|| tokenType == 4 // =
		|| tokenType == 7 // =:=
		|| tokenType == 10 // &&

		|| tokenType == 25 // (
		|| tokenType == 26 // )
		|| tokenType == 27 // {
		|| tokenType == 28 // }
		|| tokenType == 21 // )
		|| tokenType == 2 // some number
		) {
		//std::cout << "INFO >>> " << lexem << std::endl;

		info = stab->lookup(lexem);

		if (info == nullptr) {
			SymtabEntry* entry = stab->insert(lexem, lexemLength);
			info = entry->getInfo();
			//
			//
			//mapRightCheckableTypeToInfo(info, tokenType);
			//
			//
		}
		t->setInformation(info);
	} else if (tokenType == Syntax::AND1_Z || tokenType == Syntax::PROH_Z) {
		t->setType(Syntax::PROH_Z);
		t->setErrorMessage("unknown token");
		t->setSymbol(lexem[0]);


		t->setInformation(new Information());
	} else {
		t->setInformation(new Information());
	}
	//std::cout << "INFO >>> " << t->getInformation()->getLexem() << std::endl;

	 if (tokenType == Syntax::INTG_Z) {
		getNumberToken(lexem, t);
	}

	// this was added as a part of new parser integration

	//t->getInformation()->setAdditionalShitType(tokenType);
	switch (tokenType) {
		//case 19:
		//	t->getInformation()->setAdditionalShitType(19);
		//	break;
		//case 1:
		//	t->getInformation()->setType(CheckableType::Identifier);
		//	break;
		//case 35:
		//	t->getInformation()->setType(CheckableType::writetyp);
		//	break;
		//case 36:
		//	t->getInformation()->setType(CheckableType::readtyp);
		//	break;
  		//case 31:
		//	t->getInformation()->setType(CheckableType::iftyp);
		//	break;
		//case 32:
		//	t->getInformation()->setType(CheckableType::whiletyp);
		//	break;
		//case 33:
		//	t->getInformation()->setType(CheckableType::elsetyp);
		//	break;
		// case 22:
		// 	t->getInformation()->setType(CheckableType::Identifier); // 1 == State::Semikolon
		// 	break;
		// case 29:
		// 	t->getInformation()->setType(CheckableType::writetyp); // 2 == State::EckigeKlammerAuf
		// 	break;
		// case 30:
		// 	t->getInformation()->setType(CheckableType::readtyp); // 3 == State::EckigeKlammerZu
		// 	break;
		// case 2:
		// 	t->getInformation()->setType(CheckableType::Integer); // 0 == State::Number
		// 	break;
		// case 25:
		// 	t->getInformation()->setType(CheckableType::elsetyp); // 0 == State::RundeKlammerAuf
		// 	break;
		// case 26:
		// 	t->getInformation()->setType(CheckableType::Sign); // 0 == State::RundeKlammerAuf
		// 	break;
   		//default :
		////	t->getInformation()->setType(CheckableType::Sign);
		//	break;
	}
	
	/* now we can reset Automat */
	automat->reset();
	//std::cout << "debuging *** Scanner::nextToken END" << std::endl;

	/* if we need to finish already*/
	if (currentChar == '\0') {
		return new Token(22,-1,-1);
	} else {
		return t;
	}
}

/*
 * determine the current token type relying on STATE and LEXEM
 * @return token's type
 */
int Scanner::mapStateToType(int state, const char* lexem) {
	char symbol = lexem[0];
	int tType = state;
	if (state == Syntax::ASGN_Z) {
		tType = syntax->isPacked(symbol);
	} else if (state == Syntax::IDEN_Z) {
		int tmp = syntax->ifKeyword(lexem);
		if (tmp > 0) tType = tmp; // 30..35
	}
	return tType;
}

/*
 * converts a lexem to a its decimal value if it's possible
 * @return the value of a lexem if any
 */
void Scanner::getNumberToken(const char* lexem, Token* t) {
	errno = 0;
	long int value = strtol(lexem, 0, 10);
	if (errno == ERANGE) {
		t->setType(Syntax::PROH_Z);
		t->setErrorMessage("error: given integer is too big to be converted to LONG INT");
		t->setSymbol(NULL);

		errno = 0;
	} else {
		t->setValue(value);
	}

}


void Scanner::mapRightCheckableTypeToInfo(Information* info, int tokenType) {


}
