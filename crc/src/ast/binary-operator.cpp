#include "ast/binary-operator.hpp"

ast::BinaryOperator::BinaryOperator(BinaryOpationKind op, node_ptr_t left, node_ptr_t right) :
    op_(op),
    left_(left),
    right_(right) {}

ast::BinaryOpationKind ast::BinaryOperator::getOperator() const noexcept {
    return op_;
}

const ast::node_ptr_t& ast::BinaryOperator::getLeft() const noexcept {
    return left_;
}

const ast::node_ptr_t& ast::BinaryOperator::getRight() const noexcept {
    return right_;
}

ast::NodeKind ast::BinaryOperator::getNodeKind() const noexcept {
    return NodeKind::BINARY_OPERATOR;
}

ast::node_ptr_t ast::makeBinaryOperator(BinaryOpationKind op, node_ptr_t left, node_ptr_t right) {
    return std::make_unique<BinaryOperator>(op, left, right);
}

#ifdef AST_PRINT_

void ast::BinaryOperator::print(std::size_t indent) const {
    printTab(indent);
    std::println("BinaryOperator: operator='{}'", static_cast<int>(op_));

    printTab(indent);
    std::println("Left:");
    if (left_) {
        left_->print(indent + 1);
    }

    printTab(indent);
    std::println("Right:");
    if (right_) {
        right_->print(indent + 1);
    }
}

#endif
