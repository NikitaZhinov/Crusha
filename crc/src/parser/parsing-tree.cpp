#include "../../include/parser/parsing-tree.h"

#include "../../include/parser/dictionary.h"

#include <stack>

namespace crc {
    ParsingTree::Node* ParsingTree::_add(Node* node, const Lexer::token_t& token) {
        if (node == nullptr) {
            _root = new Node;
            _root->token = token;
            return _root;
        } else {
            Node* new_node = new Node;
            new_node->token = token;
            node->children.push_back(new_node);
            return node->children.back();
        }
    }

    void ParsingTree::_create(const std::vector<std::wstring>& function_names) {
        _is_full = true;
        std::stack<Lexer::token_t> token_stack;

        _polish_token_line.reserve(_token_line.size());
        auto isFunctionName = [&](const Lexer::token_t& token) {
            for (const std::wstring& name : function_names) {
                if (name == token) {
                    return true;
                }
            }
            return false;
        };

        for (std::size_t i = 0; i < _token_line.size(); ++i) {
            const Lexer::token_t& token = _token_line[i];
            if (token == L",") {
            } else if (Dictionary::isOperator(token)) {
                std::size_t priority = Dictionary::getOperators().find(token)->priority;
                while (!token_stack.empty() && Dictionary::isOperator(token_stack.top()) &&
                       Dictionary::getOperators().find(token_stack.top())->priority < priority) {
                    _polish_token_line.push_back(token_stack.top());
                    token_stack.pop();
                }
                token_stack.push(token);

                //} else if (Dictionary::isType(token)) {
            } else if (token == L"(" || isFunctionName(token)) {
                token_stack.push(token);
            } else if (token == L")") {
                while (!token_stack.empty() && token_stack.top() != L"(") {
                    _polish_token_line.push_back(token_stack.top());
                    token_stack.pop();
                }
                if (!token_stack.empty()) {
                    token_stack.pop();
                }
            } else {
                _polish_token_line.push_back(token);
            }
        }
        while (!token_stack.empty()) {
            _polish_token_line.push_back(token_stack.top());
            token_stack.pop();
        }
    }

    void ParsingTree::_clear(Node* node) {
        if (node != nullptr) {
            for (Node* child : node->children) {
                _clear(child);
            }
            delete node;
        }
    }

    ParsingTree::ParsingTree() : _root(nullptr), _is_full(false) {}

    ParsingTree::~ParsingTree() {
        _clear(_root);
    }

    void ParsingTree::setTokenLine(const std::vector<Lexer::token_t>& token_line) {
        _token_line = token_line;
    }

    void ParsingTree::setTokenLine(const Lexer::token_line_t& token_line) {
        _token_line = token_line.second;
    }

    void ParsingTree::setTokenLine(std::vector<Lexer::token_t>&& token_line) {
        _token_line = std::move(token_line);
    }

    void ParsingTree::setTokenLine(Lexer::token_line_t&& token_line) {
        _token_line = std::move(token_line.second);
    }

    std::vector<Lexer::token_t> ParsingTree::getTokenLine() const {
        return _token_line;
    }

    bool ParsingTree::isFull() const {
        return _is_full;
    }

    void ParsingTree::addToken(const Lexer::token_t& token, const std::vector<std::wstring>& function_names) {
        if (token == L";") {
            _create(function_names);
        } else {
            _token_line.push_back(token);
        }
    }
}  // namespace crc
