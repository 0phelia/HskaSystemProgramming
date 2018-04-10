#include <iostream>
#include <catch.hpp>
#include "StringTab.h"

TEST_CASE("Stringtab works", "[stringtab]") {
	StringTab * st = new StringTab();
	char * c1 = "reallyreal";
	int c1len = 10;
	char * c2 = "a";
	int c2len = 1;
	char * c3 = "b";
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


	char *s1 = st->insert(c1, c1len);
	char *s2 = st->insert(c2, c2len);
	char *s3 = st->insert(c3, c3len);
	char *s4 = st->insert(c4, c4len);
	char *s5 = st->insert(c5, c5len);
	char *s6 = st->insert(c6, c6len);
	char *s7 = st->insert(c7, c7len);
	char *s8 = st->insert(c8, c8len);
	char *s9 = st->insert(c9, c9len);
	char *s10 = st->insert(c10, c10len);

	INFO(s1);
	INFO(s2);
	INFO(s3);
	INFO(s4);
	INFO(s5);
	INFO(s6);
	INFO(s7);
	INFO(s8);
	INFO(s9);
	INFO(s10);
	REQUIRE(true);
}
