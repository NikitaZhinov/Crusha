#include <compiler/compiler.h>

std::expected<std::vector<lexer::TokenLine>, std::string>
crc::Compiler::_runLexer(const char* file_name) {
    try {
        return _lexer.createTokens(file_name);
    } catch (const std::runtime_error& ex) {
        return std::unexpected(std::format("File '{}' is not found!", file_name));
    }
}

std::expected<crc::AST, std::string>
crc::Compiler::_buildAST(const std::vector<lexer::TokenLine>& tokens) {
    return std::expected<AST, std::string>();
}

crc::Compiler::Compiler() :
    SPECIAL_ALPHABETS {
        L"+-/*=<>!"
},
    INDIVIDUAL_CHARS(L"&?;$#@^:\"'|.,(){}[]\n"),
    COMBINING_TOKENS {
        lexer::CombiningTokens { lexer::Token(L"\""), lexer::Token(L"\"") },
        lexer::CombiningTokens { lexer::Token(L"//"), lexer::Token(L"\n") },
        lexer::CombiningTokens { lexer::Token(L"/*"), lexer::Token(L"*/") }
    },
    SEPARATORS(L" \t"),
    _lexer(SPECIAL_ALPHABETS, INDIVIDUAL_CHARS, COMBINING_TOKENS, SEPARATORS) {}

std::optional<std::string> crc::Compiler::compile(const char* file_name) {
    auto lexer_result = _runLexer(file_name);
    if (!lexer_result) {
        return lexer_result.error();
    }

    auto build_ast_result = _buildAST(*lexer_result);

    return std::nullopt;
}
