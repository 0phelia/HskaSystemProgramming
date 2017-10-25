/*
 * TestParser.cpp
 *
 *  Created on: Jan 22, 2016
 *      Author: arty
 */
#include "../includes/Parser.h"

int main(int argc, char* argv[]) {

	if (argc < 2) return EXIT_FAILURE;
	Symboltable* st = new Symboltable();
	Scanner* scanner = new Scanner(argv[1], st);


	std::cout << "TestParser is being executed\n";
	
	auto parser = new Parser(scanner, argv[2]);
	printf("parsing ...\n");
	auto root = parser->parse();
	printf("type checking ...\n");
	parser->typeCheck(root);
	printf("generating code ...\n");
	parser->makeCode(root);

	return EXIT_SUCCESS;
}
