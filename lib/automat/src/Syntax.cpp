#include <Syntax.h>

/*
 * Syntax.cpp
 *
 *  Created on: Nov 18, 2015
 *      Author: arty
 */


Syntax::Syntax() {
	keywordNumber = KEYWORD_NUMBER;

	

}

Syntax::~Syntax() {
	
}

const char* Syntax::getTokenTypeAsChar(int num) {
	return ttypeString[num];
}

int Syntax::getState(int i, int j) {
	return stateTable[i][j];
}

/*
 * finds a state for a given "packed" character
 * returns -1 if the char does NOT belong to a group
 *     of "packed" chars
 * @return corresponding state for a char
 */
int Syntax::isPacked(char sign) {
	for (int i = 0; i < SIGN_ARRAY_SZ; i++) {
		if (sign == signArray[i]) return i + STATETABLE_WIDTH + 1;
	}
	return -1;
}

/*
 * checks whether the given lexem is a keyword
 * returns -1 if not
 * @return corresponding token type for keyword
 */
int Syntax::ifKeyword(const char* lexem) {
	//int tType = 0;
	for (int i = 0; i < KEYWORD_NUMBER * 2 - 3; i++) {
		if (matches(lexem, keywordsArray[i]))
			if (i < 6) {
				return (STATES_NUMBER + i / 2);
			} else {
				return (STATES_NUMBER + i - 3);
			}

	}
	return -1;
}

bool Syntax::matches(const char* one, const char* another) {
	const char* tmp1 = one;
	const char* tmp2 = another;
	while (tmp1[0] != '\0' || tmp2[0] != '\0') {
		if (tmp1++[0] != tmp2++[0]) {
			return false;
		}
	}
	return true;
}


