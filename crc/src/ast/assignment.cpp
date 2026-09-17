#include "ast/assignment.hpp"

ast::Assignment::Assignment(node_ptr_t target, node_ptr_t value) : target_(target), value_(value) {}

const ast::node_ptr_t& ast::Assignment::getTarget() const noexcept {
    return target_;
}

const ast::node_ptr_t& ast::Assignment::getValue() const noexcept {
    return value_;
}

ast::NodeKind ast::Assignment::getNodeKind() const noexcept {
    return NodeKind::ASSIGNMENT;
}

ast::node_ptr_t ast::makeAssignment(node_ptr_t target, node_ptr_t value) {
    return std::make_unique<Assignment>(target, value);
}

#ifdef AST_PRINT_

void ast::Assignment::print(std::size_t indent) const {
    printTab(indent);
    std::println("Assignment");

    printTab(indent);
    std::println("Target:");
    if (target_) {
        target_->print(indent + 1);
    }

    printTab(indent);
    std::println("Value:");
    if (value_) {
        value_->print(indent + 1);
    }
}

#endif
