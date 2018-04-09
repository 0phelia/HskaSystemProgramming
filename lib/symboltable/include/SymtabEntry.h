/*
 * SymtabEntry.h
 *
 *  Created on: Nov 12, 2015
 *      Author: arty
 */
#pragma once

#include "../../scanner/include/Information.h"

class SymtabEntry {
	Information* information;
	SymtabEntry* next;
public:
	SymtabEntry(SymtabEntry* next);
	SymtabEntry(Information* info);
	SymtabEntry();
	void setInfo(Information* info);
	Information* getInfo();
	SymtabEntry* getNext();
	virtual ~SymtabEntry();

};
