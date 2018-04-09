/*
 * TestParser.cpp
 *
 *  Created on: Jan 22, 2016
 *      Author: arty
 */
#include <catch.hpp>
#include "../lib/parser/include/Parser.h"

TEST_CASE("Parser throws no exceptions", "[parser]") {
    std::string buf(TEST_ROOT_DIR);
    buf.append("/data/test1/parser3.txt");
    INFO(buf);

    std::string buf2(TEST_ROOT_DIR);
    buf2.append("/parser_out.txt");
    INFO(buf2);


    char *input = const_cast<char *>(buf.c_str());
    char *output = const_cast<char *>(buf2.c_str());


    Symboltable *st = new Symboltable();
    Scanner *scanner = new Scanner(input, st);

    auto parser = new Parser(scanner, output);
    INFO("parsing ...\n");
    auto root = parser->parse();
    INFO("type checking ...\n");
    REQUIRE_NOTHROW(parser->typeCheck(root));
    INFO("generating code ...\n");
    REQUIRE_NOTHROW(parser->makeCode(root));

}
