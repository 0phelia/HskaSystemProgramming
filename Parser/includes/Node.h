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


#ifndef SHITHOLE
#define SHITHOLE
enum class CheckType {
	emptyType,  	// 0	
	noType, 		// 1
	intType, 		// 2
	intArrayType, 	// 3
	arrayType, 		// 4
	errorType, 		// 5
	opPlus, 		// 6
	opMinus, 		// 7
	opMult, 		// 8
	opDiv, 			// 9
	opLess, 		// 10
	opGreater, 		// 11
	opEqual, 		// 12
	opUnequal, 		// 13
	opAnd 			// 14
};
#endif 

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
