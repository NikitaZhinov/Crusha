#pragma once

#include "ast.h"

#include <lexer/lexer.h>

#include <format>
#include <optional>
#include <expected>

namespace crc {
    class Compiler {
        const std::vector<std::wstring> SPECIAL_ALPHABETS;
        const std::wstring INDIVIDUAL_CHARS;
        const std::vector<lexer::CombiningTokens> COMBINING_TOKENS;
        const std::wstring SEPARATORS;

        lexer::Lexer _lexer;

        std::expected<std::vector<lexer::TokenLine>, std::string>
        _runLexer(const char* file_name);

        std::expected<AST, std::string>
        _buildAST(const std::vector<lexer::TokenLine>& tokens);

    public:
        Compiler();

        std::optional<std::string> compile(const char* file_name);
    };
}  // namespace crc
