/*
 * Node.h
 *
 *  Created on: Dec 2, 2015
 *      Author: marvin
 */

#ifndef PARSER_SRC_NODE_H_
#define PARSER_SRC_NODE_H_

#include <stdint.h>
#include <stdio.h>
#include "../../Scanner/includes/Token.h"
enum class CheckType {
	emptyType,
	intType,
	intArrayType,
	arrayType,
	noType,
	errorType,
	opPlus,
	opMinus,
	opMult,
	opDiv,
	opLess,
	opGreater,
	opEqual,
	opUnequal,
	opAnd
};

enum class NodeType {
	PROG,
	DECLS,
	DECL,
	ARRAY,
	STATEMENT,
	STATEMENTS,
	EXP,
	EXP2,
	INDEX,
	OP_EXP,
	OP,
	LEAF
};

class Node {
public:
	Node(NodeType type);
	virtual ~Node();
	void addNode(Node* node);
	void setKey(int key, char* lexem);
	void print(int level);
	NodeType getType();
	Node* getNode(int index);
	CheckType getCheckType() const;
	void setCheckType(CheckType checkType);
	int getSubnodesCount() const;
	int getKey() const;
	Token* getToken();
	void setToken(Token* token);

private:
	NodeType type;
	int infoKey;
	int subnodes_count;
	Node* subnodes[7];
	char* infoLexem;
	CheckType checkType;
	Token* token;
};

#endif /* PARSER_SRC_NODE_H_ */
