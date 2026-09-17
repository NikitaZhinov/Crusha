#pragma once

#include "inode.hpp"

namespace ast {
    class Return final : public INode {
        node_ptr_t value_;

    public:
        explicit Return(node_ptr_t value);

        const node_ptr_t& getValue() const noexcept;

        NodeKind getNodeKind() const noexcept override;

#ifdef AST_PRINT_
        void print(std::size_t indent) const override;
#endif
    };

    node_ptr_t makeReturn(node_ptr_t value);
}  // namespace ast
