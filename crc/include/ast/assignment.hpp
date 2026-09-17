#pragma once

#include "inode.hpp"

namespace ast {
    class Assignment final : public INode {
        node_ptr_t target_;
        node_ptr_t value_;

    public:
        explicit Assignment(node_ptr_t target, node_ptr_t value);

        const node_ptr_t& getTarget() const noexcept;

        const node_ptr_t& getValue() const noexcept;

        NodeKind getNodeKind() const noexcept override;

#ifdef AST_PRINT_
        void print(std::size_t indent) const override;
#endif
    };

    node_ptr_t makeAssignment(node_ptr_t target, node_ptr_t value);
}  // namespace ast
