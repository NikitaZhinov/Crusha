#include <compiler/compiler.h>

#include <lexer/lexer.h>

void crc::analyseTokens(const std::vector<lexer::TokenLine>& tokens) {}

void crc::compile(error::ErrorManager& error_manager, const char* file_name) {
    std::vector<lexer::CombiningTokens> combining_tokens = {
        lexer::CombiningTokens { lexer::Token(L"\""), lexer::Token(L"\"") },
        lexer::CombiningTokens { lexer::Token(L"//"), lexer::Token(L"\n") },
        lexer::CombiningTokens { lexer::Token(L"/*"), lexer::Token(L"*/") }
    };
    lexer::Lexer lexer({ L"+-/*=<>!" }, L"&?;$#@^:\"'|.,(){}[]\n", combining_tokens,
                       L" \t");

    try {
        auto tokens = lexer.createTokens(file_name);
    } catch (const std::runtime_error& ex) {
        error_manager.callError(1, std::format("File '{}' is not found!", file_name));
    }
}
