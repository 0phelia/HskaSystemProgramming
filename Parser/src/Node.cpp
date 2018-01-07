#include "../includes/Node.h"
#include "../../Scanner/includes/Token.h"
#include <iostream>
/*
 * Node.cpp
 *
 *  Created on: Dec 2, 2015
 *      Author: marvin
 */


Node::Node(NodeType type) :
		infoKey(0), subnodes_count(0), infoLexem(), token() {
	this->type = type;
	this->checkType = CheckType::emptyType;
}

Node::~Node() {
}

void Node::addNode(Node* node) {
	//std::cout << "Parent node type: " << (int) type << "    added #" << subnodes_count << "  of type " << (int) node->getType() << std::endl;
	subnodes[subnodes_count] = node;
	subnodes_count++;
}

void Node::setKey(int key, char* lexem) {
	infoKey = key;
	infoLexem = lexem;
}

void Node::print(int level) {
	for (int i = 0; i < level; i++) {
		printf("-");
	}
	printf("%i", type);
	if (infoKey != 0) {
		printf("\t %s", infoLexem);
	}
	printf(" - CheckType: %i\n", checkType);
	for (int i = 0; i < subnodes_count; i++) {
		subnodes[i]->print(level + 1);
	}
}

NodeType Node::getType() {
	return this->type;
}

Node* Node::getNode(int index) {
	return subnodes[index];
}

CheckType Node::getCheckType() const {
	return checkType;
}

void Node::setCheckType(CheckType checkType) {
	this->checkType = checkType;
}

int Node::getSubnodesCount() const {
	return subnodes_count;
}

int Node::getKey() const {
	return infoKey;
}

Token* Node::getToken() {
	return token;
}

void Node::setToken(Token* token) {
	this->token = token;
}
