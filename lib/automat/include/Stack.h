/*
 * Stack.h
 *
 *  Created on: Nov 12, 2015
 *      Author: arty
 */

#pragma once

#define MAX_TOKEN_SIZE 4095
#define STACK_OVERFLOW_ERR "Error: stack can't handle such a long word (>4095). Only the last N characters will be saved"
#define MEM_ALLOC_ERR "Couldn't allocate memory for stack. Exiting..."


class Stack {
	char *stack;
	int stackHead;
public:
	Stack();
	virtual ~Stack();
	void push(char c);
    void trim(int back);
    void flush();
    char* get();
};
