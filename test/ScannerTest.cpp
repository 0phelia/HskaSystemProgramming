#include <iostream>
#include <sys/time.h>
#include <fstream>
#include <catch.hpp>
#include "../lib/symboltable/include/Symboltable.h"
#include "../lib/scanner/include/Scanner.h"

/* copypasted piece of code for time measurements */
typedef unsigned long long timestamp_t;

static timestamp_t
get_timestamp() {
    struct timeval now{};
    gettimeofday(&now, nullptr);
    return now.tv_usec + (timestamp_t) now.tv_sec * 1000000;
}


TEST_CASE("scanner works", "[scanner]") {
    std::string buf(TEST_ROOT_DIR);
    buf.append("/data/test.txt");
    INFO(buf);

    std::string buf2(TEST_ROOT_DIR);
    buf2.append("/scanner_out.txt");
    INFO(buf2);

    char *input = const_cast<char *>(buf.c_str());
    char *output = const_cast<char *>(buf2.c_str());


    timestamp_t t0 = get_timestamp();
    Symboltable *st = new Symboltable();
    Scanner *s = new Scanner(input, st);
    Token *t;
    Syntax *syntax = new Syntax();
    std::cout << "processing..." << std::endl;

    /* check if all arguments are given */

    std::ofstream output_file;
    output_file.open(output);
    if (output_file.is_open()) {
        while ((t = s->nextToken())) {
            /* console output */
            if (t->getType() == Syntax::PROH_Z) {
                std::cout << t->getErrorMessage()
                          << " Line: " << t->getLine()
                          << " Column: " << t->getColumn();
                if (t->getSymbol() != NULL) {
                    std::cout << " Symbol: " << t->getSymbol();
                }
                std::cout << std::endl;
                /* print everything else to the output file */
            } else if (t->getType() != Syntax::WSP_Z) {
                output_file
                        << syntax->getTokenTypeAsChar(t->getType())
                        << " State: " << t->getType()
                        << " Line: " << t->getLine()
                        << " Column: " << t->getColumn();
                if (t->getType() == Syntax::IDEN_Z) {
                    output_file << " Lexem: " << t->getLexem();
                } else if (t->getType() == Syntax::INTG_Z) {
                    output_file << " Value: " << t->getValue();
                }
                output_file << std::endl;
            }
        }
        std::cout << "stop" << std::endl
                  << "Exec time: " << ((get_timestamp() - t0) / 1000000.0L) << std::endl;
        output_file.close();
    } else {
        std::cout << "Error: couldn't open output file. Exiting..." << std::endl;
    }


    REQUIRE(true);
}

