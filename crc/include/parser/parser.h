#pragma once

#include "../lexer/lexer.h"
#include "function.h"

namespace crc {
    class Parser : private Lexer {
        token_list_t _token_list;
        std::list<Function> _functions;

        void _newFunction(const token_t &token);

        bool _isNameExistInFuncions(const token_t &token);

        void _setNameFuntion(const token_t &token);

        void _setStartArgsFunction(const token_t &token);
        void _setArgsFunction(const token_t &token);
        void _setNewArgFunction(const token_t &token);
        void _setArgNameFunction(const token_t &token);
        void _setEndArgsFunction(const token_t &token);

        void _setReturnTypeOperatorFunction(const token_t &token);
        void _setReturnTypeFunction(const token_t &token);

        void _setStartBlockFunction(const token_t &token);
        void _setBlockFunction(const token_t &token);

        void _tokenSyntacticAnalysis(const token_t &token);
        void _lineSyntacticAnalysis(const token_line_t &line);
        void _syntacticAnalysis();

    public:
        Parser() = default;
        Parser(const std::string &file_name);
        Parser(const token_list_t &token_list);
        Parser(token_list_t &&token_list);
    };
}  // namespace crc
