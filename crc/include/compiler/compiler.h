#pragma once

#include <error-manager/error-manager.h>
#include <lexer/lexer.h>

#include <string>

namespace crc {
    void analyseTokens(const std::vector<lexer::TokenLine>& tokens);

    void compile(error::ErrorManager& error_manager, const char* file_name);
}  // namespace crc
