#include <iostream>
#include <catch.hpp>
#include "../lib/symboltable/include/Symboltable.h"
#include "../lib/scanner/include/Information.h"

TEST_CASE("symboltable works", "[symboltable]") {

	char* checkFile = "data/scanner0.txt";


	Symboltable* symboltable = new Symboltable();

	char * c1 = "reallyreal";
	int c1len = 10;
	char * c2 = "a";
	int c2len = 1;
	char * c3 = "c";
	int c3len = 1;
	char * c4 = "c";
	int c4len = 1;
	char * c5 = "d";
	int c5len = 1;
	char * c6 = "mio moi mio";
	int c6len = 11;
	char * c7 = "RACINGTEAM";
	int c7len = 10;
	char * c8 = "trytohandleths";
	int c8len = 14;
	char * c9 = "not impressed at all";
	int c9len = 20;
	char * c10 = "reallyreallyreallyreallyreallyreallyreallyreallyreallyreallyString";
	int c10len = 67;


	SymtabEntry *s1 = symboltable->insert(c1, c1len);
	SymtabEntry *s2 = symboltable->insert(c2, c2len);
	SymtabEntry *s3 = symboltable->insert(c3, c3len);
	SymtabEntry *s4 = symboltable->insert(c4, c4len);
	SymtabEntry *s5 = symboltable->insert(c5, c5len);
	SymtabEntry *s6 = symboltable->insert(c6, c6len);
	SymtabEntry *s7 = symboltable->insert(c7, c7len);
	SymtabEntry *s8 = symboltable->insert(c8, c8len);
	SymtabEntry *s9 = symboltable->insert(c9, c9len);
	SymtabEntry *s10 = symboltable->insert(c10, c10len);

	c1 = ";";
	c2 = ";";
	c3 = "d";
	c9 = ";";
	c10 = ";";
	c8 = "d";

	INFO(s1->getInfo()->getLexem());
	INFO(s2->getInfo()->getLexem());
	INFO(s3->getInfo()->getLexem());
	INFO(s4->getInfo()->getLexem());
	INFO(s5->getInfo()->getLexem());
	INFO(s6->getInfo()->getLexem());
	INFO(s7->getInfo()->getLexem());
	INFO(s8->getInfo()->getLexem());
	INFO(s9->getInfo()->getLexem());
	INFO(s10->getInfo()->getLexem());

	REQUIRE(true);


		Information* info = symboltable->lookup(checkFile);
		REQUIRE_FALSE (info == nullptr);
}
