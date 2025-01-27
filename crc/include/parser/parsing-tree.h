#pragma once

#include "../lexer/lexer.h"

namespace crc {
    class ParsingTree {
        struct Node {
            std::list<Node*> children;
            Lexer::token_t token;
        };

        Node* _root;
        std::vector<Lexer::token_t> _token_line;
        std::vector<Lexer::token_t> _polish_token_line;
        bool _is_full;

        Node* _add(Node* node, const Lexer::token_t& token);
        void _create(const std::vector<std::wstring>& function_names);

        void _clear(Node* node);

    public:
        ParsingTree();
        ~ParsingTree();

        void setTokenLine(const std::vector<Lexer::token_t> &token_line);
        void setTokenLine(const Lexer::token_line_t &token_line);
        void setTokenLine(std::vector<Lexer::token_t> &&token_line);
        void setTokenLine(Lexer::token_line_t &&token_line);

        std::vector<Lexer::token_t> getTokenLine() const;
        bool isFull() const;

        void addToken(const Lexer::token_t &token, const std::vector<std::wstring>& function_names);
    };
}  // namespace crc
