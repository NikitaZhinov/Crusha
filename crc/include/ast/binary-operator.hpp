#pragma once

#include "inode.hpp"

namespace ast {
    class BinaryOperator final : public INode {
        BinaryOpationKind op_;
        node_ptr_t left_;
        node_ptr_t right_;

    public:
        explicit BinaryOperator(BinaryOpationKind op, node_ptr_t left, node_ptr_t right);

        BinaryOpationKind getOperator() const noexcept;

        const node_ptr_t& getLeft() const noexcept;

        const node_ptr_t& getRight() const noexcept;

        NodeKind getNodeKind() const noexcept override;

#ifdef AST_PRINT_
        void print(std::size_t indent) const override;
#endif
    };

    node_ptr_t makeBinaryOperator(BinaryOpationKind op, node_ptr_t left, node_ptr_t right);
}  // namespace ast
