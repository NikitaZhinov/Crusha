#include "ast/return.hpp"

ast::Return::Return(node_ptr_t value) : value_(value) {}

const ast::node_ptr_t& ast::Return::getValue() const noexcept {
    return value_;
}

ast::NodeKind ast::Return::getNodeKind() const noexcept {
    return NodeKind::RETURN;
}

ast::node_ptr_t ast::makeReturn(node_ptr_t value) {
    return std::make_unique<Return>(value);
}

#ifdef AST_PRINT_

void ast::Return::print(std::size_t indent) const {
    printTab(indent);
    std::println("Return");

    printTab(indent);
    std::println("Value:");
    if (value_) {
        value_->print(indent + 1);
    }
}

#endif
