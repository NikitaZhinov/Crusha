#include "ast/scope.hpp"

ast::Scope::Scope(const node_list_t& statements) : statements_(statements) {}

const ast::node_list_t& ast::Scope::getStatemets() const noexcept {
    return statements_;
}

ast::NodeKind ast::Scope::getNodeKind() const noexcept {
    return NodeKind::SCOPE;
}

ast::node_ptr_t ast::makeScope(const node_list_t& statements) {
    return std::make_unique<Scope>(statements);
}

#ifdef AST_PRINT_

void ast::Scope::print(std::size_t indent) const {
    printTab(indent);
    std::println("Scope");

    printTab(indent);
    std::println("Statemets:");

    for (const auto& stmt : statements_) {
        if (stmt) {
            stmt->print(indent + 1);
        }
    }
}

#endif
