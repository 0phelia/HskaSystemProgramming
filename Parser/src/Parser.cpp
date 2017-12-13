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
	auto decls = parseDecls();
	prog->addNode(decls);
	auto statements = parseStatements();
	prog->addNode(statements);
	return prog;
}

Node* Parser::parseDecls() {
	auto decls = createNode(NodeType::DECLS);
	auto info = token->getInformation();
	if (info->getType() == CheckableType::inttyp) {
		decls->addNode(parseDecl());
		decls->addNode(match(State::Semikolon));
		decls->addNode(parseDecls());
	}
	return decls;
}

Node* Parser::parseDecl() {
	auto decl = createNode(NodeType::DECL);
	decl->addNode(match(CheckableType::inttyp));
	decl->addNode(parseArray());
	decl->addNode(match(CheckableType::Identifier));
	return decl;
}

Node* Parser::parseArray() {

	auto array = createNode(NodeType::ARRAY);
	auto info = token->getInformation();

	std::cout<< "ARRRRRRAY: tokentype=" << info->getType() << std::endl;
	if (info->getType() == State::EckigeKlammerAuf) {
		array->addNode(match(State::EckigeKlammerAuf));
		array->addNode(match(State::Number));
		array->addNode(match(State::EckigeKlammerZu));
	}
	return array;
}

Node* Parser::parseStatements() {
	auto statements = createNode(NodeType::STATEMENTS);
	auto infoType = token->getInformation()->getType();
	auto tokenType = token->getType();
	if (infoType == CheckableType::Identifier || infoType == CheckableType::writetyp
			|| infoType == CheckableType::readtyp
			|| tokenType == State::GeschweifteKlammerAuf
			|| infoType == CheckableType::iftyp || infoType == CheckableType::whiletyp) {
		statements->addNode(parseStatement());
		statements->addNode(match(State::Semikolon));
		statements->addNode(parseStatements());
	}
	return statements;
}

Node* Parser::parseStatement() {
	auto statement = createNode(NodeType::STATEMENT);
	auto infoType = token->getInformation()->getType();
	std::cout << "parseStatement______ infoType: " << infoType << std::endl;
	auto tokenType = token->getType();
	if (infoType == CheckableType::Identifier) {
		statement->addNode(match(CheckableType::Identifier));
		statement->addNode(parseIndex());
		statement->addNode(match(State::DoppelpunktIstGleich));
		statement->addNode(parseExp());
	} else if (infoType == CheckableType::writetyp) {
		statement->addNode(match(CheckableType::writetyp));
		statement->addNode(match(State::RundeKlammerAuf));
		statement->addNode(parseExp());
		statement->addNode(match(State::RundeKlammerZu));
	} else if (infoType == CheckableType::readtyp) {
		statement->addNode(match(CheckableType::readtyp));
		statement->addNode(match(State::RundeKlammerAuf));
		statement->addNode(match(CheckableType::Identifier));
		statement->addNode(parseIndex());
		statement->addNode(match(State::RundeKlammerZu));
	} else if (tokenType == State::GeschweifteKlammerAuf) {
		statement->addNode(match(State::GeschweifteKlammerAuf));
		statement->addNode(parseStatements());
		statement->addNode(match(State::GeschweifteKlammerZu));
	} else if (infoType == CheckableType::iftyp) {
		statement->addNode(match(CheckableType::iftyp));
		statement->addNode(match(State::RundeKlammerAuf));
		statement->addNode(parseExp());
		statement->addNode(match(State::RundeKlammerZu));
		statement->addNode(parseStatement());
		statement->addNode(match(CheckableType::elsetyp));
		statement->addNode(parseStatement());
	} else if (infoType == CheckableType::whiletyp) {
		statement->addNode(match(CheckableType::whiletyp));
		statement->addNode(match(State::RundeKlammerAuf));
		statement->addNode(parseExp());
		statement->addNode(match(State::RundeKlammerZu));
		statement->addNode(parseStatement());
	} else {
		std::cout << "snappppp1" << std::endl;
		error();
	}
	return statement;
}

Node* Parser::parseExp() {
	auto exp = createNode(NodeType::EXP);
	exp->addNode(parseExp2());
	exp->addNode(parseOpExp());
	return exp;
}

Node* Parser::parseExp2() {
	auto exp2 = createNode(NodeType::EXP2);
	auto infoType = token->getInformation()->getType();
	auto tokenType = token->getType();
	if (tokenType == State::RundeKlammerAuf) {
		exp2->addNode(match(State::RundeKlammerAuf));
		exp2->addNode(parseExp());
		exp2->addNode(match(State::RundeKlammerZu));
	} else if (infoType == CheckableType::Identifier) {
		exp2->addNode(match(CheckableType::Identifier));
		exp2->addNode(parseIndex());
	} else if (infoType == CheckableType::Integer) {
		exp2->addNode(match(CheckableType::Integer));
	} else if (tokenType == State::Minus) {
		exp2->addNode(match(State::Minus));
		exp2->addNode(parseExp2());
	} else if (tokenType == State::Ausrufezeichen) {
		exp2->addNode(match(State::Ausrufezeichen));
		exp2->addNode(parseExp2());
	} else {
		std::cout << "snappppp2" << std::endl;
		error();
	}
	return exp2;
}

Node* Parser::parseIndex() {
	auto index = createNode(NodeType::INDEX);
	if (token->getType() == State::EckigeKlammerAuf) {
		index->addNode(match(State::EckigeKlammerAuf));
		index->addNode(parseExp());
		index->addNode(match(State::EckigeKlammerZu));
	}
	return index;
}

Node* Parser::parseOpExp() {
	auto op_exp = createNode(NodeType::OP_EXP);
	auto tokenType = token->getType();
	if (tokenType == State::Plus || tokenType == State::Minus
			|| tokenType == State::Stern
			|| tokenType == State::VorwaertsSchraegstrich
			|| tokenType == State::KleinerAls || tokenType == State::GroesserAls
			|| tokenType == State::kleinerDoppelpunktGroesser
			|| tokenType == State::IstGleichZeichen
			|| tokenType == State::UndZeichen) {
		op_exp->addNode(parseOp());
		op_exp->addNode(parseExp());
	}
	return op_exp;
}

Node* Parser::parseOp() {
	auto op = createNode(NodeType::OP);
	auto tokenType = token->getType();
	if (tokenType == State::Plus) {
		op->addNode(match(State::Plus));
	} else if (tokenType == State::Minus) {
		op->addNode(match(State::Minus));
	} else if (tokenType == State::Stern) {
		op->addNode(match(State::Stern));
	} else if (tokenType == State::VorwaertsSchraegstrich) {
		op->addNode(match(State::VorwaertsSchraegstrich));
	} else if (tokenType == State::KleinerAls) {
		op->addNode(match(State::KleinerAls));
	} else if (tokenType == State::GroesserAls) {
		op->addNode(match(State::GroesserAls));
	} else if (tokenType == State::IstGleichZeichen) {
		op->addNode(match(State::IstGleichZeichen));
	} else if (tokenType == State::kleinerDoppelpunktGroesser) {
		op->addNode(match(State::kleinerDoppelpunktGroesser));
	} else if (tokenType == State::UndZeichen) {
		op->addNode(match(State::UndZeichen));
	} else {
		std::cout << "snappppp3" << std::endl;
		error();
	}
	return op;
}

void Parser::nextToken() {
	token = scanner->nextToken();
	std::cout << "Parser::nextToken() calls:  nextToken() " << token->getType() << " at "<< token->getLine() << ":" << token->getColumn() << std::endl;

}

Node* Parser::match(State typ) {
	std::cout << "In match 1: tokenType = " << token->getInformation()->getType() << ";  actual = " << typ << " ";
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
}

Node* Parser::match(CheckableType typ) {
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
}

void Parser::error() {
	std::cout << "unexpected token of type " << token->getInformation()->getType() << " at "<<
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
		auto nummb = node->getNode(2)->getToken()->getLexem();
		//std::cout << "CHECK TYPE: "<< scanner->getInfo(node->getNode(2)->getToken()->getLexem())->setCheckType((CheckType)4) << std::endl;

		if ((CheckType)scanner->getInfo(node->getNode(2)->getToken()->getLexem())->getCheckType()
				!= CheckType::noType) {
			errorTypeCheck("identifier already defined",
					node->getNode(2)->getToken());
			node->setCheckType(CheckType::errorType);
		} else if (node->getNode(1)->getCheckType() == CheckType::errorType) {
			node->setCheckType(CheckType::errorType);
		} else {
			node->setCheckType(CheckType::noType);
			if (node->getNode(1)->getCheckType() == CheckType::arrayType) {
				scanner->getInfo(node->getNode(2)->getToken()->getLexem())->setCheckType(
						(int)CheckType::intArrayType);
			} else {
				scanner->getInfo(node->getNode(2)->getToken()->getLexem())->setCheckType(
						(int)CheckType::intType);
			}
		}
	} else if (node->getType() == NodeType::ARRAY) {
		if (node->getSubnodesCount() == 0) {
			node->setCheckType(CheckType::noType);
		} else {
			if (node->getNode(1)->getToken()->getValue() > 0 && node->getNode(1)->getToken()->getValue() != -666) {

			//if (scanner->getInfo(node->getNode(1)->getToken()->getLexem())->getValue() > 0) {
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
		auto infotype = scanner->getInfo(node->getNode(0)->getToken()->getLexem())->getType();
		if (infotype == CheckableType::writetyp) {
			typeCheck(node->getNode(2));
			node->setCheckType(CheckType::noType);
		} else if (infotype == CheckableType::readtyp) {
			typeCheck(node->getNode(3)); // INDEX
			auto identCheckType = (CheckType)
					scanner->getInfo(node->getNode(2)->getToken()->getLexem())->getCheckType();
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
		} else if (infotype == CheckableType::Sign) { // Geschweifte Klammer auf
			typeCheck(node->getNode(1));
			node->setCheckType(CheckType::noType);
		} else if (infotype == CheckableType::iftyp) {
			typeCheck(node->getNode(2)); // exp
			typeCheck(node->getNode(4)); // statement
			typeCheck(node->getNode(6)); // statement
			if (node->getNode(2)->getCheckType() == CheckType::errorType) {
				node->setCheckType(CheckType::errorType);
			} else {
				node->setCheckType(CheckType::noType);
			}
		} else if (infotype == CheckableType::whiletyp) {
			typeCheck(node->getNode(2)); // exp
			typeCheck(node->getNode(4)); // statement
			if (node->getNode(2)->getCheckType() == CheckType::errorType) {
				node->setCheckType(CheckType::errorType);
			} else {
				node->setCheckType(CheckType::noType);
			}
		} else if (infotype == CheckableType::Identifier) {
			typeCheck(node->getNode(1)); // index
			typeCheck(node->getNode(3)); // exp
			auto identCheckType =
					(CheckType)scanner->getInfo(node->getNode(0)->getToken()->getLexem())->getCheckType();
			if (identCheckType == CheckType::noType) {
				errorTypeCheck("identifier not defined",
						node->getNode(0)->getToken());
				node->setCheckType(CheckType::errorType);
			} else if (node->getNode(3)->getCheckType() == CheckType::intType
					&& ((identCheckType == CheckType::intType
							&& node->getNode(1)->getCheckType()
									== CheckType::noType)
							|| (identCheckType == CheckType::intArrayType
									&& node->getNode(1)->getCheckType()
											== CheckType::arrayType))) {
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
		} else if (firstNode->getType() == CheckableType::Integer) {
			node->setCheckType(CheckType::intType);
		} else if (firstNode->getType() == CheckableType::Identifier) {
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
		} else if (strcmp(lexem, "/") == 0) {
			node->setCheckType(CheckType::opDiv);
		} else if (strcmp(lexem, "<") == 0) {
			node->setCheckType(CheckType::opLess);
		} else if (strcmp(lexem, ">") == 0) {
			node->setCheckType(CheckType::opGreater);
		} else if (strcmp(lexem, "=") == 0) {
			node->setCheckType(CheckType::opEqual);
		} else if (strcmp(lexem, "<:>") == 0) {
			node->setCheckType(CheckType::opUnequal);
		} else if (strcmp(lexem, "&") == 0) {
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
		auto firstNodeInfo = scanner->getInfo(node->getNode(0)->getToken()->getLexem());
		if (firstNodeInfo->getType() == CheckableType::Identifier) {
			makeCode(node->getNode(3)); // EXP
			code << "LA $" << firstNodeInfo->getLexem() << endl;
			makeCode(node->getNode(1)); // INDEX
			code << "STR " << endl;
		} else if (firstNodeInfo->getType() == CheckableType::writetyp) {
			makeCode(node->getNode(2)); // EXP
			code << "PRI " << endl;
		} else if (firstNodeInfo->getType() == CheckableType::readtyp) {
			code << "REA " << endl;
			code << "LA $"
					<< scanner->getInfo(node->getNode(2)->getToken()->getLexem())->getLexem() << endl;
			makeCode(node->getNode(3)); // INDEX
			code << "STR " << endl;
		} else if (firstNodeInfo->getType() == CheckableType::Sign) {
			makeCode(node->getNode(1)); // STATEMENTS
		} else if (firstNodeInfo->getType() == CheckableType::iftyp) {

			makeCode(node->getNode(2)); // EXP
			int thisLabel = labelcounter;
			labelcounter++;
			code << "JIN #m" << thisLabel << endl;
			makeCode(node->getNode(4)); // STATEMENT
			code << "JMP #n" << thisLabel << endl;
			code << "#m" << thisLabel << " NOP " << endl;
			makeCode(node->getNode(6)); // STEATEMENT
			code << "#n" << thisLabel << " NOP " << endl;

		} else if (firstNodeInfo->getType() == CheckableType::whiletyp) {
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
		} else if (firstNodeInfo->getType() == CheckableType::Identifier) {
			code << "LA $" << firstNodeInfo->getLexem() << endl;
			makeCode(node->getNode(1)); // INDEX
			code << "LV " << endl;
		} else if (firstNodeInfo->getType() == CheckableType::Integer) {
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
		} else if (strcmp(lexem, "/") == 0) {
			code << "DIV" << endl;
		} else if (strcmp(lexem, "<") == 0) {
			code << "LES" << endl;
		} else if (strcmp(lexem, ">") == 0) {
		} else if (strcmp(lexem, "=") == 0) {
			code << "EQU" << endl;
		} else if (strcmp(lexem, "<:>") == 0) {
			code << "EQU" << endl;
		} else if (strcmp(lexem, "&") == 0) {
			code << "AND" << endl;
		}
	}
}
