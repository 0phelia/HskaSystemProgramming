/*
 * StringTab.h
 *
 *  Created on: Oct 28, 2015
 *      Author: arty
 */

#pragma once

#define INITIAL_SIZE 16
#define INITIAL_ALGN 4096

#include <stdio.h>  // perror()
#include <stdlib.h> // exit()
#include <errno.h>  // errors' list
#include <string.h> // memcpy()

class StringTab {
	char *string;
	char *freeP;
	int overallSpace;
	int freeSpace;
public:
	StringTab();
	virtual ~StringTab();
	char* insert(const char *lexem, int size);
	void resize(int moreSpace);
	char* copy(char * freepointer, const char *lexem, int size);
	void resize(char * stringItself, int size);
	int getFS();
	int getOS();
};
