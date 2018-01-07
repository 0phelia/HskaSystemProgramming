/*
 * Parser.cpp
 *
 *  Created on: 16.01.2016
 *      Author: work
 */

#include <cstring>
#include "../includes/Parser.h"

Parser::Parser(Scanner* s, char* output) {
	scanner = s;
	token = new Token(1,1,1); // dummy values since we dont have an empty constructor
							  // original: Token(spalte = 1; zeile = 1; tokentype = State::Undefined)
	token = scanner->nextToken();
	std::cout << "Parser::Parser() calls:  nextToken() " << token->getType() << std::endl;
	code.open(output);

	if (code.is_open()) {
		std::cout << "the output file was open" << std::endl;
	}

	labelcounter = 0;
}

Parser::~Parser() {
	code.close();
}

Node* Parser::parse() {
	return parseProg();
}

Node* Parser::parseProg() {
	auto prog = createNode(NodeType::PROG);
	// if (token->getLine() == -1) {
	// 	return;
	// }
	auto decls = parseDecls();
	prog->addNode(decls);
	auto statements = parseStatements();
	prog->addNode(statements);
	return prog;
}

Node* Parser::parseDecls() {
	auto decls = createNode(NodeType::DECLS);
	//if (token->getLine() == -1) {
	//	return;
	//}
	//auto info = token->getInformation();
	if (token->getType() == StateUpdated::KeywordInt) {
		decls->addNode(parseDecl());
		decls->addNode(match(StateUpdated::Semikolon));
		decls->addNode(parseDecls());
	}
	return decls;
}

Node* Parser::parseDecl() {
	auto decl = createNode(NodeType::DECL);
	//if (token->getLine() == -1) {
	//	return;
	//}
	decl->addNode(match(StateUpdated::KeywordInt));
	decl->addNode(parseArray());
	decl->addNode(match(StateUpdated::IdentifierU));
	return decl;
}

Node* Parser::parseArray() {

	auto array = createNode(NodeType::ARRAY);
	//auto info = token->getInformation();
	//if (token->getLine() == -1) {
	//	return;
	//}
	//std::cout<< "ARRRRRRAY: tokentype=" << info->getType() << std::endl;
	if (token->getType() == StateUpdated::EckigeKlammerAuf) {
		array->addNode(match(StateUpdated::EckigeKlammerAuf));
		array->addNode(match(StateUpdated::Number));
		array->addNode(match(StateUpdated::EckigeKlammerZu));
	}
	return array;
}

Node* Parser::parseStatements() {
	auto statements = createNode(NodeType::STATEMENTS);
	//auto infoType = token->getInformation()->getType();
	auto tokenType = token->getType();
	//if (token->getLine() == -1) {
	//	return;
	//}
	if (tokenType == StateUpdated::IdentifierU || tokenType == StateUpdated::KeywordWrite
			|| tokenType == StateUpdated::KeywordRead
			|| tokenType == StateUpdated::GeschweifteKlammerAuf
			|| tokenType == StateUpdated::KeywordIf || tokenType == StateUpdated::KeywordWhile) {
		std::cout << "got inside parseStatements() tokenType: " << tokenType << std::endl;
		statements->addNode(parseStatement());
		statements->addNode(match(StateUpdated::Semikolon));
		statements->addNode(parseStatements());
	}
	return statements;
}

Node* Parser::parseStatement() {
	auto statement = createNode(NodeType::STATEMENT);
	//auto infoType = token->getInformation()->getType();
	auto tokenType = token->getType();
	//if (token->getLine() == -1) {
	//	return;
	//}
	std::cout << "got inside parseStatement() tokenType: " << tokenType << std::endl;

	if (tokenType == StateUpdated::IdentifierU) {
		statement->addNode(match(StateUpdated::IdentifierU));
		statement->addNode(parseIndex());
		statement->addNode(match(StateUpdated::DoppelpunktIstGleich));
		statement->addNode(parseExp());
	} else if (tokenType == StateUpdated::KeywordWrite) {
		statement->addNode(match(StateUpdated::KeywordWrite));
		statement->addNode(match(StateUpdated::RundeKlammerAuf));
		statement->addNode(parseExp());
		statement->addNode(match(StateUpdated::RundeKlammerZu));
	} else if (tokenType == StateUpdated::KeywordRead) {
		statement->addNode(match(StateUpdated::KeywordRead));
		statement->addNode(match(StateUpdated::RundeKlammerAuf));
		statement->addNode(match(StateUpdated::IdentifierU));
		statement->addNode(parseIndex());
		statement->addNode(match(StateUpdated::RundeKlammerZu));
	} else if (tokenType == StateUpdated::GeschweifteKlammerAuf) {
		statement->addNode(match(StateUpdated::GeschweifteKlammerAuf));
		statement->addNode(parseStatements());
		statement->addNode(match(StateUpdated::GeschweifteKlammerZu));
	} else if (tokenType == StateUpdated::KeywordIf) {
		statement->addNode(match(StateUpdated::KeywordIf));
		statement->addNode(match(StateUpdated::RundeKlammerAuf));
		statement->addNode(parseExp());
		statement->addNode(match(StateUpdated::RundeKlammerZu));
		statement->addNode(parseStatement());
		statement->addNode(match(StateUpdated::KeywordElse));
		statement->addNode(parseStatement());
	} else if (tokenType == StateUpdated::KeywordWhile) {
		statement->addNode(match(StateUpdated::KeywordWhile));
		statement->addNode(match(StateUpdated::RundeKlammerAuf));
		statement->addNode(parseExp());
		statement->addNode(match(StateUpdated::RundeKlammerZu));
		statement->addNode(parseStatement());
	} else {
		std::cout << "error in parseStatement()" << std::endl;
		error();
	}
	return statement;
}

Node* Parser::parseExp() {
	auto exp = createNode(NodeType::EXP);
	//if (token->getLine() == -1) {
	//	return;
	//}

	exp->addNode(parseExp2());
	exp->addNode(parseOpExp());
	return exp;
}

Node* Parser::parseExp2() {
	auto exp2 = createNode(NodeType::EXP2);
	//auto infoType = token->getInformation()->getType();
	auto tokenType = token->getType();
	//if (token->getLine() == -1) {
	//	return;
	//}
	std::cout << "got inside parseExp2() tokenTyoe: " << tokenType << std::endl;
	if (tokenType == StateUpdated::RundeKlammerAuf) {
		exp2->addNode(match(StateUpdated::RundeKlammerAuf));
		exp2->addNode(parseExp());
		exp2->addNode(match(StateUpdated::RundeKlammerZu));
	} else if (tokenType == StateUpdated::IdentifierU) {
		exp2->addNode(match(StateUpdated::IdentifierU));
		exp2->addNode(parseIndex());
	} else if (tokenType == StateUpdated::Number) {
		exp2->addNode(match(StateUpdated::Number));
	} else if (tokenType == StateUpdated::Minus) {
		exp2->addNode(match(StateUpdated::Minus));
		exp2->addNode(parseExp2());
	} else if (tokenType == StateUpdated::Ausrufezeichen) {
		exp2->addNode(match(StateUpdated::Ausrufezeichen));
		exp2->addNode(parseExp2());
	} else {
		std::cout << "error in parseExp2()" << std::endl;
		error();
	}
	return exp2;
}

Node* Parser::parseIndex() {
	auto index = createNode(NodeType::INDEX);
	//if (token->getLine() == -1) {
//		return;
	//}
	std::cout << "got inside parseIndex() tokenType: " << token->getType() << std::endl;

	if (token->getType() == StateUpdated::EckigeKlammerAuf) {
		index->addNode(match(StateUpdated::EckigeKlammerAuf));
		index->addNode(parseExp());
		index->addNode(match(StateUpdated::EckigeKlammerZu));
	}
	return index;
}

Node* Parser::parseOpExp() {
	auto op_exp = createNode(NodeType::OP_EXP);
	auto tokenType = token->getType();
	//if (token->getLine() == -1) {
	//	return;
	//}
	if (tokenType == StateUpdated::Plus || tokenType == StateUpdated::Minus
			|| tokenType == StateUpdated::Stern
			|| tokenType == StateUpdated::VorwaertsSchraegstrich
			|| tokenType == StateUpdated::KleinerAls || tokenType == StateUpdated::GroesserAls
			|| tokenType == StateUpdated::kleinerDoppelpunktGroesser
			|| tokenType == StateUpdated::IstGleichZeichen
			|| tokenType == StateUpdated::UndZeichen) {
		op_exp->addNode(parseOp());
		op_exp->addNode(parseExp());
	}
	return op_exp;
}

Node* Parser::parseOp() {
	auto op = createNode(NodeType::OP);
	auto tokenType = token->getType();
	//if (token->getLine() == -1) {
	//	return;
	//}
	if (tokenType == StateUpdated::Plus) {
		op->addNode(match(StateUpdated::Plus));
	} else if (tokenType == StateUpdated::Minus) {
		op->addNode(match(StateUpdated::Minus));
	} else if (tokenType == StateUpdated::Stern) {
		op->addNode(match(StateUpdated::Stern));
	} else if (tokenType == StateUpdated::VorwaertsSchraegstrich) {
		op->addNode(match(StateUpdated::VorwaertsSchraegstrich));
	} else if (tokenType == StateUpdated::KleinerAls) {
		op->addNode(match(StateUpdated::KleinerAls));
	} else if (tokenType == StateUpdated::GroesserAls) {
		op->addNode(match(StateUpdated::GroesserAls));
	} else if (tokenType == StateUpdated::IstGleichZeichen) {
		op->addNode(match(StateUpdated::IstGleichZeichen));
	} else if (tokenType == StateUpdated::kleinerDoppelpunktGroesser) {
		op->addNode(match(StateUpdated::kleinerDoppelpunktGroesser));
	} else if (tokenType == StateUpdated::UndZeichen) {
		op->addNode(match(StateUpdated::UndZeichen));
	} else {
		std::cout << "error on parseOp()" << std::endl;
		error();
	}
	return op;
}

void Parser::nextToken() {
	token = scanner->nextToken();
	//std::cout << "Parser::Parser() calls:  nextToken() " << token->getType() << std::endl;
	//std::cout << "Parser::nextToken() calls:  nextToken() " << token->getType() << " at "<< token->getLine() << ":" << token->getColumn() << std::endl;
}

Node* Parser::match(StateUpdated typ) {
	//std::cout << "In MATCH: actual tokenType = " << token->getType() << ";  desired = " << typ << " ";
	if (token->getType() != typ) {
		error();
	} else {
		auto leaf = createNode(NodeType::LEAF);
		leaf->setToken(token);
		nextToken();
		return leaf;
	}
	
}

/*Node* Parser::match(CheckableType typ) {
	std::cout << "In match 2: tokenType = " << token->getInformation()->getType() << ";  actual = "<< typ << " ";
	if (token->getInformation()->getType() != typ) {
		error();
	} else {
		std::cout << "TYPES MATCHED " << std::endl;
	}
	auto leaf = createNode(NodeType::LEAF);
	leaf->setToken(token);
	//leaf->setKey(token->getKey(), token->getValue());
	nextToken();
	return leaf;
}*/

void Parser::error() {
	std::cout << "unexpected token of type " << token->getType() << " at "<<
		token->getLine() << ":"<< token->getColumn() << std::endl;
	//fprintf(stderr, "unexpected token '%s' at line '%d', column '%d'\n",
	//		token->getValue(), token->getLine(), token->getColumn());
	std::cout << ("stop") << std::endl;
	exit(1);
}

Node* Parser::createNode(NodeType ntype) {
	return new Node(ntype);
}

void Parser::errorTypeCheck(const char* message, Token* token) {
	fprintf(stderr, "error Line: %i Column: %i %s \n", token->getLine(),
			token->getColumn(), message);
	printf("stop\n");
	exit(1);
}

CheckType Parser::getCheckTypeOfIdentifier(Node* node) {
	char* lexem = node->getToken()->getLexem();
	return (CheckType) scanner->getInfo(lexem)->getCheckType();
}

void Parser::setCheckTypeOfIdentifier(Node* node, CheckType checkType) {
	char* lexem = node->getToken()->getLexem();
	scanner->getInfo(lexem)->setCheckType((int) checkType);
}

//
// 1. Information test isWhile isIf isElse etc.
// 2. Scanner should save all info types (incl. { [ etc)
// 3. Information should operate on CheckType from Node.h, and not on int types NOT FEASIBLE
// 


void Parser::typeCheck(Node* node) {
	if (node->getType() == NodeType::PROG) {
		typeCheck(node->getNode(0));
		typeCheck(node->getNode(1));
		node->setCheckType(CheckType::noType);


	} else if (node->getType() == NodeType::DECLS) {
		if (node->getSubnodesCount() > 0) {
			typeCheck(node->getNode(0));
			typeCheck(node->getNode(2));
		}
		node->setCheckType(CheckType::noType);


	} else if (node->getType() == NodeType::DECL) {
		typeCheck(node->getNode(1));
		
		if ( getCheckTypeOfIdentifier(node->getNode(2)) != CheckType::noType) {
			errorTypeCheck("identifier already defined", node->getNode(2)->getToken());
			node->setCheckType(CheckType::errorType);
		} else if (node->getNode(1)->getCheckType() == CheckType::errorType) {
			node->setCheckType(CheckType::errorType);
		} else {
			node->setCheckType(CheckType::noType);
			if (node->getNode(1)->getCheckType() == CheckType::arrayType) {
				setCheckTypeOfIdentifier (node->getNode(2), CheckType::intArrayType);
			} else {
				setCheckTypeOfIdentifier (node->getNode(2), CheckType::intType);
			}
		}

/*
	getCheckTypeOfIdentifier(Node)

	setCheckTypeOfIdentifier(Node , CheckType::intType)

	node->setCheckType(CheckType::noType);

	node->getCheckType()

*/
	} else if (node->getType() == NodeType::ARRAY) {
		if (node->getSubnodesCount() == 0) {
			node->setCheckType(CheckType::noType);
		} else {
			if (node->getNode(1)->getToken()->getValue() > 0 ) {
				node->setCheckType(CheckType::arrayType);
			} else {
				errorTypeCheck("no valid dimension",
						node->getNode(1)->getToken());
				node->setCheckType(CheckType::errorType);
			}
		}
	} else if (node->getType() == NodeType::STATEMENTS) {
		if (node->getSubnodesCount() > 0) {
			typeCheck(node->getNode(0));
			typeCheck(node->getNode(2));
		}
		node->setCheckType(CheckType::noType);
	} else if (node->getType() == NodeType::STATEMENT) {


		//std::cout << "node->getNode(0)->getToken()  " << node->getNode(0)->getToken()->getType() << std::endl;
		
		//CheckableType infotype;
		//if (node->getNode(0)->getToken()->getType() == 27) {
		//	infotype == CheckableType::Sign;
		//} else {
		//	infotype = getCheckTypeOfIdentifier(node->getNode(0));
		//}
		Information* info;
		if ( node->getNode(0)->getToken()->getType() == 27) {
			//info = nullptr;
		} else {
			
		}
		info = node->getNode(0)->getToken()->getInformation();
		//std::cout << " info is not null " << std::endl;
		if (info->isKlammerAuf()) {
			typeCheck(node->getNode(1));
			node->setCheckType(CheckType::noType);
		} else if (info->isWrite()) {
			typeCheck(node->getNode(2));
			node->setCheckType(CheckType::noType);
		} else if (info->isRead()) {
			typeCheck(node->getNode(3)); // INDEX
			auto identCheckType = getCheckTypeOfIdentifier(node->getNode(2));
			auto indexCheckType = node->getNode(3)->getCheckType();
			if (identCheckType == CheckType::noType) {
				errorTypeCheck("identifier not defined",
						node->getNode(2)->getToken());
				node->setCheckType(CheckType::errorType);
			} else if ((identCheckType == CheckType::intType
					&& indexCheckType == CheckType::noType)
					|| (identCheckType == CheckType::intArrayType
							&& indexCheckType == CheckType::arrayType)) {
				node->setCheckType(CheckType::noType);
			} else {
				errorTypeCheck("incompatible types",
						node->getNode(2)->getToken());
				node->setCheckType(CheckType::errorType);
			}
		} else if (info->isIf()) { // IF
			typeCheck(node->getNode(2)); // exp
			typeCheck(node->getNode(4)); // statement
			typeCheck(node->getNode(6)); // statement
			if (node->getNode(2)->getCheckType() == CheckType::errorType) {
				node->setCheckType(CheckType::errorType);
			} else {
				node->setCheckType(CheckType::noType);
			}
		} else if (info->isWhile()) { // WHILE
			typeCheck(node->getNode(2)); // exp
			typeCheck(node->getNode(4)); // statement
			if (node->getNode(2)->getCheckType() == CheckType::errorType) {
				node->setCheckType(CheckType::errorType);
			} else {
				node->setCheckType(CheckType::noType);
			}
		} else if (info->isIdentifier()) { // IDENTIFIER
			typeCheck(node->getNode(1)); // index
			typeCheck(node->getNode(3)); // exp
			auto identCheckType = getCheckTypeOfIdentifier(node->getNode(0));

			if (identCheckType == CheckType::noType) {
				errorTypeCheck("identifier not defined",
						node->getNode(0)->getToken());
				node->setCheckType(CheckType::errorType);
			} else if (node->getNode(3)->getCheckType() == CheckType::intType
					&& ((identCheckType == CheckType::intType && node->getNode(1)->getCheckType() == CheckType::noType)
							|| (identCheckType == CheckType::intArrayType && node->getNode(1)->getCheckType() == CheckType::arrayType))) {
				node->setCheckType(CheckType::noType);
			} else {
				errorTypeCheck("incompatible types",
						node->getNode(0)->getToken());
				node->setCheckType(CheckType::errorType);
			}
		}
	} else if (node->getType() == NodeType::INDEX) {
		if (node->getSubnodesCount() == 0) {
			node->setCheckType(CheckType::noType);
		} else {
			typeCheck(node->getNode(1)); // index
			if (node->getNode(1)->getCheckType() == CheckType::errorType) {
				node->setCheckType(CheckType::errorType);
			} else {
				node->setCheckType(CheckType::arrayType);
			}
		}
	} else if (node->getType() == NodeType::EXP) {
		typeCheck(node->getNode(0)); // EXP2
		typeCheck(node->getNode(1)); // OP_EXP
		if (node->getNode(1)->getCheckType() == CheckType::noType) {
			node->setCheckType(node->getNode(0)->getCheckType());
		} else if (node->getNode(0)->getCheckType()
				!= node->getNode(1)->getCheckType()) {
			node->setCheckType(CheckType::errorType);
		} else {
			node->setCheckType(node->getNode(0)->getCheckType());
		}
	} else if (node->getType() == NodeType::EXP2) {
		// crash 2
		

		auto firstNode = scanner->getInfo(node->getNode(0)->getToken()->getLexem());
		if (strcmp(firstNode->getLexem(), "(") == 0
				|| strcmp(firstNode->getLexem(), "-") == 0) {
			typeCheck(node->getNode(1));
			node->setCheckType(node->getNode(1)->getCheckType());
		} else if (strcmp(firstNode->getLexem(), "!") == 0) {
			typeCheck(node->getNode(1));
			if (node->getNode(1)->getCheckType() != CheckType::intType) {
				node->setCheckType(CheckType::errorType);
			} else {
				node->setCheckType(CheckType::intType);
			}
		} else if (node->getNode(0)->getToken()->getValue() != -666) { // NUMBER
			//std::cout << "it recognised the number ! " << std::endl;
			node->setCheckType(CheckType::intType);
			//firstNode->setType(CheckableType::Integer);
		} else if (firstNode->isIdentifier()) {
			typeCheck(node->getNode(1));
			auto identInfo = scanner->getInfo(node->getNode(0)->getToken()->getLexem());
			if ((CheckType)identInfo->getCheckType() == CheckType::noType) {
				errorTypeCheck("identifier not defined",
						node->getNode(0)->getToken());
				node->setCheckType(CheckType::errorType);
			} else if ((CheckType)identInfo->getCheckType() == CheckType::intType
					&& node->getNode(1)->getCheckType() == CheckType::noType) {
				node->setCheckType((CheckType)identInfo->getCheckType());
			} else if ((CheckType)identInfo->getCheckType() == CheckType::intArrayType
					&& node->getNode(1)->getCheckType()
							== CheckType::arrayType) {
				node->setCheckType(CheckType::intType);
			} else {
				errorTypeCheck("no primitive Type",
						node->getNode(0)->getToken());
				node->setCheckType(CheckType::errorType);
			}
		}
	} else if (node->getType() == NodeType::OP_EXP) {
		if (node->getSubnodesCount() == 0) {
			node->setCheckType(CheckType::noType);
		} else {
			typeCheck(node->getNode(0)); //OP
			typeCheck(node->getNode(1)); //EXP
			node->setCheckType(node->getNode(1)->getCheckType());
		}
	} else if (node->getType() == NodeType::OP) {
		auto lexem = scanner->getInfo(node->getNode(0)->getToken()->getLexem())->getLexem();
		if (strcmp(lexem, "+") == 0) {
			node->setCheckType(CheckType::opPlus);
		} else if (strcmp(lexem, "-") == 0) {
			node->setCheckType(CheckType::opMinus);
		} else if (strcmp(lexem, "*") == 0) {
			node->setCheckType(CheckType::opMult);
		} else if (strcmp(lexem, "/") == 0) { // from / to :
			node->setCheckType(CheckType::opDiv);
		} else if (strcmp(lexem, "<") == 0) {
			node->setCheckType(CheckType::opLess);
		} else if (strcmp(lexem, ">") == 0) {
			node->setCheckType(CheckType::opGreater);
		} else if (strcmp(lexem, "=") == 0) {
			node->setCheckType(CheckType::opEqual);
		} else if (strcmp(lexem, "<:>") == 0) { // from <:> to =:=
			node->setCheckType(CheckType::opUnequal);
		} else if (strcmp(lexem, "&") == 0) { // from & to &&
			node->setCheckType(CheckType::opAnd);
		}
	}
}

void Parser::makeCode(Node* node) {
	if (node->getType() == NodeType::PROG) {
		makeCode(node->getNode(0)); // DECLS
		makeCode(node->getNode(1)); // STATEMENTS
		code << "STP " << endl;
	} else if (node->getType() == NodeType::DECLS) {
		if (node->getSubnodesCount() > 0) {
			makeCode(node->getNode(0)); // DECL
			makeCode(node->getNode(2)); // DECLS
		}
	} else if (node->getType() == NodeType::DECL) {
		code << "DS " << "$"
				<< scanner->getInfo(node->getNode(2)->getToken()->getLexem())->getLexem();
		makeCode(node->getNode(1)); // ARRAY
	} else if (node->getType() == NodeType::ARRAY) {
		if (node->getSubnodesCount() > 0) {
			code << " "
					<< node->getNode(1)->getToken()->getValue()
					<< endl;
		} else {
			code << " 1" << endl;
		}
	} else if (node->getType() == NodeType::STATEMENTS) {
		if (node->getSubnodesCount() > 0) {
			makeCode(node->getNode(0)); // STATEMENT
			makeCode(node->getNode(2)); // STATEMENTS
		} else {
			code << "NOP " << endl;
		}
	} else if (node->getType() == NodeType::STATEMENT) {
		// new CRASH exactly like the one during parsing phase

		//std::cout << "damn TYPE: " << node->getNode(0)->getToken()->getType() << std::endl;
		Information* firstNodeInfo;
		if (node->getNode(0)->getToken()->getType() != 27) {
			// firstNodeInfo = node->getNode(0)->getToken()->getInformation();
		} else {
			//firstNodeInfo = new Information();
			//firstNodeInfo->setType(CheckableType::Sign); TODO we just commented it out, need to clean the consequences up

		}

		firstNodeInfo = node->getNode(0)->getToken()->getInformation();
		
		if (firstNodeInfo->isIdentifier()) {
			makeCode(node->getNode(3)); // EXP
			code << "LA $" << firstNodeInfo->getLexem() << endl;
			makeCode(node->getNode(1)); // INDEX
			code << "STR " << endl;
		} else if (firstNodeInfo->isWrite()) {
			makeCode(node->getNode(2)); // EXP
			code << "PRI " << endl;
		} else if (firstNodeInfo->isRead()) {
			code << "REA " << endl;
			code << "LA $"
					<< scanner->getInfo(node->getNode(2)->getToken()->getLexem())->getLexem() << endl;
			makeCode(node->getNode(3)); // INDEX
			code << "STR " << endl;
		} else if (firstNodeInfo->isKlammerAuf()) { // TODO here we actually compared it with CheckableType::Sign
			makeCode(node->getNode(1)); // STATEMENTS
		} else if (firstNodeInfo->isIf()) {

			makeCode(node->getNode(2)); // EXP
			int thisLabel = labelcounter;
			labelcounter++;
			code << "JIN #m" << thisLabel << endl;
			makeCode(node->getNode(4)); // STATEMENT
			code << "JMP #n" << thisLabel << endl;
			code << "#m" << thisLabel << " NOP " << endl;
			makeCode(node->getNode(6)); // STEATEMENT
			code << "#n" << thisLabel << " NOP " << endl;

		} else if (firstNodeInfo->isWhile()) {
			int thisLabel = labelcounter;
			labelcounter++;
			code << "#m" << thisLabel << " NOP " << endl;
			makeCode(node->getNode(2)); // EXP
			code << "JIN #n" << thisLabel << endl;
			makeCode(node->getNode(4)); // STATEMENT
			code << "JMP #m" << thisLabel << endl;
			code << "#n" << thisLabel << " NOP " << endl;
		}
	} else if (node->getType() == NodeType::EXP) {


		if (node->getNode(1)->getCheckType() == CheckType::noType) {
			makeCode(node->getNode(0)); // EXP2
		} else if (node->getNode(1)->getNode(0)->getCheckType()
				== CheckType::opGreater) {
			makeCode(node->getNode(1)); // OP_EXP
			makeCode(node->getNode(0)); // EXP2
			code << "LES" << endl;
		} else if (node->getNode(1)->getNode(0)->getCheckType()
				== CheckType::opUnequal) {
			makeCode(node->getNode(0)); // EXP2
			makeCode(node->getNode(1)); // OP_EXP
			code << "NOT" << endl;
		} else {
			makeCode(node->getNode(0)); // EXP2
			makeCode(node->getNode(1)); // OP_EXP
		}
	} else if (node->getType() == NodeType::INDEX) {
		if (node->getSubnodesCount() > 0) {
			makeCode(node->getNode(1)); // EXP
			code << "ADD " << endl;
		}
	} else if (node->getType() == NodeType::EXP2) {
		auto firstNodeInfo = scanner->getInfo(node->getNode(0)->getToken()->getLexem());
		int vvvalue = node->getNode(0)->getToken()->getValue();
		if (strcmp(firstNodeInfo->getLexem(), "(") == 0) {
			makeCode(node->getNode(1)); // EXP
		} else if (firstNodeInfo->isIdentifier()   &&   node->getNode(0)->getToken()->getValue() == -666) {
			code << "LA $" << firstNodeInfo->getLexem() << endl;
			makeCode(node->getNode(1)); // INDEX
			code << "LV " << endl;
		} else if (node->getNode(0)->getToken()->getValue() != -666) {
			code << "LC " << vvvalue << endl;
		} else if (strcmp(firstNodeInfo->getLexem(), "-") == 0) {
			code << "LC 0" << endl;
			makeCode(node->getNode(1)); // EXP2
			code << "SUB " << endl;
		} else if (strcmp(firstNodeInfo->getLexem(), "!") == 0) {
			makeCode(node->getNode(1)); // EXP2
			code << "NOT " << endl;
		}
	} else if (node->getType() == NodeType::OP_EXP) {
		if (node->getSubnodesCount() > 0) {
			makeCode(node->getNode(1)); // EXP
			makeCode(node->getNode(0)); // OP
		}
	} else if (node->getType() == NodeType::OP) {
		auto lexem = scanner->getInfo(node->getNode(0)->getToken()->getLexem())->getLexem();
		if (strcmp(lexem, "+") == 0) {
			code << "ADD" << endl;
		} else if (strcmp(lexem, "-") == 0) {
			code << "SUB" << endl;
		} else if (strcmp(lexem, "*") == 0) {
			code << "MUL" << endl;
		} else if (strcmp(lexem, ":") == 0) {
			code << "DIV" << endl;
		} else if (strcmp(lexem, "<") == 0) {
			code << "LES" << endl;
		} else if (strcmp(lexem, ">") == 0) {
		} else if (strcmp(lexem, "=") == 0) {
			code << "EQU" << endl;
		} else if (strcmp(lexem, "=:=") == 0) {
			code << "EQU" << endl;
		} else if (strcmp(lexem, "&&") == 0) {
			code << "AND" << endl;
		}
	}
}
