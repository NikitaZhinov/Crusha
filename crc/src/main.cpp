#include <print>
#include <string_view>
#include <stdexcept>
#include <fstream>

#include "lexer.hpp"
#include "driver.hpp"

import options;

int yyFlexLexer::yywrap() {
    return 1;
}

static void printOptionError(const std::string_view& text, const char* arg) {
    std::println("{}: {}", text, arg);
}

static void optionError(options::ErrorPos error_pos, const char* argv[]) {
    const char* arg = argv[error_pos.pos];

    switch (error_pos.error) {
        case options::EmptyOption:
            printOptionError("Empty option", arg);
            break;

        case options::EmptyValue:
            printOptionError("Empty value", arg);
            break;

        case options::UndefinedOption:
            printOptionError("Undefined option", arg);
            break;

        case options::ExtraValue:
            printOptionError("Extra value", arg);
            break;

        default:
            throw std::runtime_error("unreleased option error");
    }
}

static void compile(const std::string_view& file_name) {
    std::ifstream ifs(file_name.data());

    if (!ifs.is_open()) {
        throw std::runtime_error("сan't open file");
    }

    Lexer lexer(ifs);

    Driver driver(&lexer, file_name);

    if (driver.parse()) {
#ifdef AST_PRINT_
        driver.ast()->print(0);
#endif
    }
}

int main(int argc, const char* argv[]) {
    options::OptionsParser options_parser;

    auto options_parser_res = options_parser.parse(argc, argv);

    if (options_parser_res.error) {
        optionError(options_parser_res, argv);
        return 1;
    }

    try {
        for (int i = 1; i < argc; ++i) {
            if (argv[i][0] != '-') {
                compile(argv[i]);
            }
        }
    } catch (const std::exception& ex) {
        std::println("Error: ", ex.what());
        return 2;
    }
}
